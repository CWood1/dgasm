cmake_minimum_required(VERSION 3.10)
include(GNUInstallDirs)

project(dgasm VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED)

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
    COMMAND valgrind
        --leak-check=full
        --error-exitcode=1
	$<TARGET_FILE:dgasm>
	-t eclipse_s140 -f octal
	${sourcefile}
  )

  set_tests_properties(memcheck_${name} PROPERTIES LABELS "memcheck")
endfunction()

add_memcheck_test(hello ${CMAKE_SOURCE_DIR}/tests/hello.s)

add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS dgasm)
