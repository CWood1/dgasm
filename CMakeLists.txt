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

function(add_golden_eclipse_s140_test name)
  add_test(
    NAME golden_eclipse_s140_${name}
    COMMAND ${CMAKE_COMMAND} -DINPUT=${CMAKE_SOURCE_DIR}/tests/golden/${name}.s -DEXPECTED=${CMAKE_SOURCE_DIR}/tests/golden/${name}.octal -DASSEMBLE=$<TARGET_FILE:dgasm> -DARCH=eclipse_s140 -P ${CMAKE_SOURCE_DIR}/cmake/run_golden_test.cmake
  )

  set_tests_properties(golden_eclipse_s140_${name} PROPERTIES LABELS "golden")
endfunction()

function(add_golden_nova1_test name)
  add_test(
    NAME golden_nova1_${name}
    COMMAND ${CMAKE_COMMAND} -DINPUT=${CMAKE_SOURCE_DIR}/tests/golden/${name}.s -DEXPECTED=${CMAKE_SOURCE_DIR}/tests/golden/${name}.octal -DASSEMBLE=$<TARGET_FILE:dgasm> -DARCH=nova1 -P ${CMAKE_SOURCE_DIR}/cmake/run_golden_test.cmake
  )

  set_tests_properties(golden_nova1_${name} PROPERTIES LABELS "golden")
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

add_golden_nova1_test(mov)
add_golden_nova1_test(add)
add_golden_nova1_test(and)
add_golden_nova1_test(com)
add_golden_nova1_test(lda)
add_golden_nova1_test(sta)
add_golden_nova1_test(isz)
add_golden_nova1_test(dsz)
add_golden_nova1_test(jmp)
add_golden_nova1_test(jsr)
add_golden_nova1_test(dido)
add_golden_nova1_test(nio)
add_golden_nova1_test(skp)

add_golden_eclipse_s140_test(lef)
add_golden_eclipse_s140_test(lda)
add_golden_eclipse_s140_test(sta)
add_golden_eclipse_s140_test(nio)
add_golden_eclipse_s140_test(skp)
add_golden_eclipse_s140_test(dido)
add_golden_eclipse_s140_test(jmp)
add_golden_eclipse_s140_test(ejmp)
add_golden_eclipse_s140_test(jsr)
add_golden_eclipse_s140_test(ejsr)
add_golden_eclipse_s140_test(isz)
add_golden_eclipse_s140_test(eisz)
add_golden_eclipse_s140_test(dsz)
add_golden_eclipse_s140_test(edsz)
add_golden_eclipse_s140_test(adc)
add_golden_eclipse_s140_test(add)
add_golden_eclipse_s140_test(and)
add_golden_eclipse_s140_test(com)
add_golden_eclipse_s140_test(inc)
add_golden_eclipse_s140_test(mov)
add_golden_eclipse_s140_test(neg)
add_golden_eclipse_s140_test(sub)
add_golden_eclipse_s140_test(elda)
add_golden_eclipse_s140_test(elef)
add_golden_eclipse_s140_test(esta)
add_golden_eclipse_s140_test(estb)
add_golden_eclipse_s140_test(eldb)
add_golden_eclipse_s140_test(dspa)
add_golden_eclipse_s140_test(save)
add_golden_eclipse_s140_test(anc)
add_golden_eclipse_s140_test(bto)
add_golden_eclipse_s140_test(btz)
add_golden_eclipse_s140_test(clm)
add_golden_eclipse_s140_test(cob)
add_golden_eclipse_s140_test(dad)
add_golden_eclipse_s140_test(dlsh)
add_golden_eclipse_s140_test(dsb)
add_golden_eclipse_s140_test(ior)
add_golden_eclipse_s140_test(ldb)
add_golden_eclipse_s140_test(lob)
add_golden_eclipse_s140_test(lrb)
add_golden_eclipse_s140_test(lsh)
add_golden_eclipse_s140_test(pop)
add_golden_eclipse_s140_test(psh)
add_golden_eclipse_s140_test(sge)
add_golden_eclipse_s140_test(sgt)
add_golden_eclipse_s140_test(snb)
add_golden_eclipse_s140_test(stb)
add_golden_eclipse_s140_test(syc)
add_golden_eclipse_s140_test(szb)
add_golden_eclipse_s140_test(szbo)
add_golden_eclipse_s140_test(xch)
add_golden_eclipse_s140_test(xor)
add_golden_eclipse_s140_test(fas)
add_golden_eclipse_s140_test(fcmp)
add_golden_eclipse_s140_test(fdd)
add_golden_eclipse_s140_test(fds)
add_golden_eclipse_s140_test(ffas)
add_golden_eclipse_s140_test(flas)
add_golden_eclipse_s140_test(fmd)
add_golden_eclipse_s140_test(fmov)
add_golden_eclipse_s140_test(fms)
add_golden_eclipse_s140_test(fsd)
add_golden_eclipse_s140_test(fss)
add_golden_eclipse_s140_test(msp)
add_golden_eclipse_s140_test(hlv)
add_golden_eclipse_s140_test(xct)
add_golden_eclipse_s140_test(fexp)
add_golden_eclipse_s140_test(fhlv)
add_golden_eclipse_s140_test(fint)
add_golden_eclipse_s140_test(fneg)
add_golden_eclipse_s140_test(fnom)
add_golden_eclipse_s140_test(frh)
add_golden_eclipse_s140_test(fscal)
add_golden_eclipse_s140_test(addi)
add_golden_eclipse_s140_test(andi)
add_golden_eclipse_s140_test(iori)
add_golden_eclipse_s140_test(xori)
add_golden_eclipse_s140_test(adi)
add_golden_eclipse_s140_test(dhxl)
add_golden_eclipse_s140_test(dhxr)
add_golden_eclipse_s140_test(hxl)
add_golden_eclipse_s140_test(hxr)
add_golden_eclipse_s140_test(sbi)
add_golden_eclipse_s140_test(famd)
add_golden_eclipse_s140_test(fams)
add_golden_eclipse_s140_test(fdmd)
add_golden_eclipse_s140_test(fdms)
add_golden_eclipse_s140_test(ffmd)
add_golden_eclipse_s140_test(fldd)
add_golden_eclipse_s140_test(flds)
add_golden_eclipse_s140_test(flmd)
add_golden_eclipse_s140_test(fmmd)
add_golden_eclipse_s140_test(fsmd)
add_golden_eclipse_s140_test(fsms)
add_golden_eclipse_s140_test(fstd)
add_golden_eclipse_s140_test(fsts)
add_golden_eclipse_s140_test(flst)
add_golden_eclipse_s140_test(fsst)
add_golden_eclipse_s140_test(pshj)
add_golden_eclipse_s140_test(xop)
add_golden_eclipse_s140_test(xop1)

add_golden_eclipse_s140_test(eval)
add_golden_eclipse_s140_test(strings)
add_golden_eclipse_s140_test(directives)
add_golden_eclipse_s140_test(constinstrs)
add_golden_eclipse_s140_test(floatconsts)

add_fuzz_regression_tests()

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS dgasm)
