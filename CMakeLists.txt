cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

project(dgasm VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED)
option(ENABLE_COVERAGE OFF)

if(ENABLE_COVERAGE)
  add_compile_options(--coverage)
  add_link_options(--coverage)
endif()

# Create a config.h file from a template (or just define it)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

string(TIMESTAMP CURRENT_DATE "%B %Y")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/dgasm.1.in"
  "${CMAKE_CURRENT_BINARY_DIR}/dgasm.1"
  @ONLY
)

FIND_PACKAGE(BISON REQUIRED)
BISON_TARGET(DGAsmParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h
COMPILE_FLAGS "-Wcounterexamples")

FIND_PACKAGE(FLEX REQUIRED)
FLEX_TARGET(DGAsmLexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.h)

ADD_FLEX_BISON_DEPENDENCY(DGAsmLexer DGAsmParser)

add_executable(dgasm main.c symbol_tbl.c assembler.c opcode.c eval.c error.c ${BISON_DGAsmParser_OUTPUTS} ${FLEX_DGAsmLexer_OUTPUTS})

target_compile_options(dgasm PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(
  dgasm PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}
)

install(TARGETS dgasm RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES dgasm.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

# Testing

enable_testing()

function(add_memcheck_test name sourcefile)
  add_test(
    NAME memcheck_${name}
    COMMAND valgrind --leak-check=full --error-exitcode=1
    $<TARGET_FILE:dgasm> -t eclipse_s140 -f octal ${sourcefile}
  )

  set_tests_properties(memcheck_${name} PROPERTIES LABELS "memcheck")
endfunction()

function(add_golden_test name input expected)
  add_test(
    NAME golden_${name}
    COMMAND ${CMAKE_COMMAND} -DINPUT=${input} -DEXPECTED=${expected} -DASSEMBLE=$<TARGET_FILE:dgasm> -P ${CMAKE_SOURCE_DIR}/cmake/run_golden_test.cmake
  )

  set_tests_properties(golden_${name} PROPERTIES LABELS "golden")
endfunction()

function(add_fuzz_regression_tests)
  file(GLOB FUZZ_TESTS
    "${CMAKE_SOURCE_DIR}/tests/fuzzregression/crash_*.s"
  )

  foreach(testfile ${FUZZ_TESTS})
    get_filename_component(testname ${testfile} NAME_WE)

    add_test(
      NAME fuzz_${testname}
      COMMAND ${CMAKE_COMMAND}
        -DINPUT=${testfile}
        -DASSEMBLER=$<TARGET_FILE:dgasm>
        -P ${CMAKE_SOURCE_DIR}/cmake/run_fuzz_regression_test.cmake
    )

    set_tests_properties(fuzz_${testname} PROPERTIES LABELS "golden")
  endforeach()
endfunction()

add_memcheck_test(hello ${CMAKE_SOURCE_DIR}/tests/hello.s)
add_golden_test(lef ${CMAKE_SOURCE_DIR}/tests/golden/lef.s ${CMAKE_SOURCE_DIR}/tests/golden/lef.octal)
add_golden_test(lda ${CMAKE_SOURCE_DIR}/tests/golden/lda.s ${CMAKE_SOURCE_DIR}/tests/golden/lda.octal)
add_golden_test(sta ${CMAKE_SOURCE_DIR}/tests/golden/sta.s ${CMAKE_SOURCE_DIR}/tests/golden/sta.octal)
add_golden_test(nio ${CMAKE_SOURCE_DIR}/tests/golden/nio.s ${CMAKE_SOURCE_DIR}/tests/golden/nio.octal)
add_golden_test(skp ${CMAKE_SOURCE_DIR}/tests/golden/skp.s ${CMAKE_SOURCE_DIR}/tests/golden/skp.octal)
add_golden_test(dido ${CMAKE_SOURCE_DIR}/tests/golden/dido.s ${CMAKE_SOURCE_DIR}/tests/golden/dido.octal)
add_golden_test(jmp ${CMAKE_SOURCE_DIR}/tests/golden/jmp.s ${CMAKE_SOURCE_DIR}/tests/golden/jmp.octal)
add_golden_test(jsr ${CMAKE_SOURCE_DIR}/tests/golden/jsr.s ${CMAKE_SOURCE_DIR}/tests/golden/jsr.octal)
add_golden_test(isz ${CMAKE_SOURCE_DIR}/tests/golden/isz.s ${CMAKE_SOURCE_DIR}/tests/golden/isz.octal)
add_golden_test(dsz ${CMAKE_SOURCE_DIR}/tests/golden/dsz.s ${CMAKE_SOURCE_DIR}/tests/golden/dsz.octal)
add_golden_test(adc ${CMAKE_SOURCE_DIR}/tests/golden/adc.s ${CMAKE_SOURCE_DIR}/tests/golden/adc.octal)

add_golden_test(eval ${CMAKE_SOURCE_DIR}/tests/golden/eval.s ${CMAKE_SOURCE_DIR}/tests/golden/eval.octal)
add_golden_test(strings ${CMAKE_SOURCE_DIR}/tests/golden/strings.s ${CMAKE_SOURCE_DIR}/tests/golden/strings.octal)
add_golden_test(directives ${CMAKE_SOURCE_DIR}/tests/golden/directives.s ${CMAKE_SOURCE_DIR}/tests/golden/directives.octal)
add_golden_test(consts ${CMAKE_SOURCE_DIR}/tests/golden/constinstrs.s ${CMAKE_SOURCE_DIR}/tests/golden/constinstrs.octal)

add_fuzz_regression_tests()

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS dgasm)
