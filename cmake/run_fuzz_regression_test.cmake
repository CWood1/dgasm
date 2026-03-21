execute_process(
  COMMAND ${ASSEMBLER} -t eclipse_s140 -f octal ${INPUT}
  RESULT_VARIABLE res
  OUTPUT_VARIABLE out
  ERROR_VARIABLE err
)

# Any non-zero exit is a failure
if(NOT res EQUAL 0 AND NOT res EQUAL 1)
  message(FATAL_ERROR
    "Fuzz regression failed for ${INPUT}\n\n"
    "Exit code: ${res}\n\n"
    "Output:\n${out}\n\n"
    "Error:\n${err}"
  )
endif()
