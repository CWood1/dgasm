execute_process(
  COMMAND ${ASSEMBLE} -t ${ARCH} -f octal ${INPUT}
  OUTPUT_FILE output.tmp
  OUTPUT_VARIABLE res_out
  RESULT_VARIABLE res
)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "Golden test failed on assembly for ${INPUT}:\n\n${res_out}")
endif()

execute_process(
  COMMAND diff -u ${EXPECTED} output.tmp
  RESULT_VARIABLE diff_res
  OUTPUT_VARIABLE diff_out
  ERROR_VARIABLE diff_err
)

if(NOT diff_res EQUAL 0)
  message(FATAL_ERROR "Golden test failed for ${INPUT}:\n\n${diff_out}")
endif()
