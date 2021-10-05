list(APPEND CMAKE_MESSAGE_CONTEXT api_ut)
file(GLOB_RECURSE SOURCES "*.cc")
foreach(file ${SOURCES})
  string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cc)" "\\2" test_name ${file})
  # unit test
  set(testname ut_${test_name})
  string(TOLOWER ${testname} testname)
  add_executable(${testname} ${file})
  target_link_libraries(${testname} GTest::gmock_main ${PROJECT_NAME}::api)
  target_code_coverage(${testname} AUTO ALL)
  gtest_discover_tests(${testname} PROPERTIES LABELS "ApiUnitTest"
                                              DISCOVERY_TIMEOUT 240)
  message("Discovered ${testname}")
endforeach()
