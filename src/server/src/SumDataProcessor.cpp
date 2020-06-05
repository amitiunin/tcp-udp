#include <src/server/SumDataProcessor.h>

#include <algorithm>
#include <numeric>
#include <regex>
#include <sstream>
#include <vector>

bool isNumber(const std::string &input)
{
  static std::regex re{"(\\d)+"};
  return std::regex_match(input, re);
}

std::vector<std::string> split(const std::string &data, const std::vector<char> &delimiters)
{
  std::vector<std::string> tokens;
  std::string token;
  for (const auto &ch : data)
  {
    if (std::find(std::begin(delimiters), std::end(delimiters), ch) != std::end(delimiters))
    {
      if(!token.empty())
        tokens.push_back(token);
      token.clear();
    }
    else
    {
      token.push_back(ch);
    }
  }
  if(!token.empty())
    tokens.push_back(token);
  return tokens;
}

template <typename NumType = uint64_t>  // можно доработать под большие числа
std::vector<NumType> extractNumbers(const std::string &data)
{
  const auto tokens = split(data, {' '});
  std::vector<NumType> result;
  for (const auto &token: tokens)
    if(isNumber(token))
      result.emplace_back(std::stoll(token));
  return result;
}

std::string SumDataProcessor::process(const std::string &data)
{
  auto numbers = extractNumbers(data);

  std::sort(std::begin(numbers), std::end(numbers));
  const auto sum = std::accumulate(std::begin(numbers), std::end(numbers), decltype(numbers)::value_type{});

  std::ostringstream ss;
  for (size_t i = 0; i < numbers.size(); ++i)
  {
    ss << numbers[i];
    if(i != numbers.size() - 1)
      ss << " ";
  }
  ss << "\n" << sum;
  return ss.str();
}

