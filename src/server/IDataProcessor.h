#ifndef TEST_ASSIGNMENT_IDATAPROCESSOR_H
#define TEST_ASSIGNMENT_IDATAPROCESSOR_H

#include <string>

class IDataProcessor
{
public:
  virtual ~IDataProcessor() = default;

  /**
   * Обработка строки.
   * @param data Входная строка
   * @return Результат обработки
   */
  virtual std::string process(const std::string &data) = 0;
};

#endif //TEST_ASSIGNMENT_IDATAPROCESSOR_H
