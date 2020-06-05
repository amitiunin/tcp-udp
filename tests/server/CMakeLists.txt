add_executable(sum_data_processor_test SumDataProcessorTest.cpp ${PROJECT_SOURCE_DIR}/src/server/src/SumDataProcessor.cpp)
target_link_libraries(sum_data_processor_test ${GTEST_BOTH_LIBRARIES} Threads::Threads)
add_test(sum_data_processor_test sum_data_processor_test)
