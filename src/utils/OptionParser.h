#ifndef TEST_ASSIGNMENT_OPTIONPARSER_H
#define TEST_ASSIGNMENT_OPTIONPARSER_H

#include <functional>
#include <iostream>
#include <map>

#include <getopt.h>

/**
 * Выполняет разбор аргументов командной строки.
 */
class OptionsParser
{
public:
  void addOption(option &&op, std::function<void()> &&action)
  {
    opts.push_back(op);
    actions.emplace(op.val, action);
  }

  void parseOptions(int argc, char **argv)
  {
    const int option_count = argc - 1;
    for (int option_index = 0; option_index < option_count; ++option_index)
    {
      auto c = getopt_long(argc, argv, "", opts.data(), nullptr);
      if (c == -1)
        return;
      else if (c != '?')
        actions[c]();
    }
  }

private:
  std::vector<option> opts;
  std::map<int, std::function<void()>> actions;
};

#endif //TEST_ASSIGNMENT_OPTIONPARSER_H
