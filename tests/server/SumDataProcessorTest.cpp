#include <gtest/gtest.h>

#include <memory>

#include <src/server/SumDataProcessor.h>

class SumDataProcessorTest : public ::testing::Test
{
public:
  void SetUp() override
  {
    instance = std::make_unique<SumDataProcessor>();
  }

protected:
  std::unique_ptr<SumDataProcessor> instance;
};

#define TEST_PROCESS(name, input, exp)\
  TEST_F(SumDataProcessorTest, name)\
  {\
    const std::string data = input;\
    const std::string expected = exp;\
    ASSERT_EQ(expected, instance->process(data));\
  }

TEST_PROCESS(test_process_ok, "20 apples, 30 bananas, 15 peaches and 1 watermelon", "1 15 20 30\n66")
TEST_PROCESS(test_process_negative, "-20 apples, -30 bananas, 15 peaches and 1 watermelon", "1 15\n16")
TEST_PROCESS(test_process_no_number, "Hello World!", "\n0")
TEST_PROCESS(test_process_empty, "", "\n0")
TEST_PROCESS(test_process_lost_space, "20apples, 30 bananas, 15 peaches", "15 30\n45")
TEST_PROCESS(test_process_punctuation_mark, "1, 42 a, 43. b, 65536 5000000000", "42 65536 5000000000\n5000065578")
