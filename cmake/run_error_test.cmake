execute_process(
  COMMAND ${ASSEMBLE} -t ${ARCH} -f octal ${INPUT}
  OUTPUT_FILE output.tmp
  OUTPUT_VARIABLE res_out
  RESULT_VARIABLE res
)

if(NOT res EQUAL 1)
  message(FATAL_ERROR "Error test failed on assembly for ${INPUT}:\n\n${res_out}")
endif()
