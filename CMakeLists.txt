include(GNUInstallDirs)

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

install(TARGETS dgasm RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES dgasm.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
