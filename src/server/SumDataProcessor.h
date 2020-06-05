#ifndef TEST_ASSIGNMENT_SUMDATAPROCESSOR_H
#define TEST_ASSIGNMENT_SUMDATAPROCESSOR_H

#include <src/server/IDataProcessor.h>

#include <string>

class SumDataProcessor : public IDataProcessor
{
public:
  SumDataProcessor() : IDataProcessor() {}

  std::string process(const std::string &data) override;
};

#endif //TEST_ASSIGNMENT_SUMDATAPROCESSOR_H
