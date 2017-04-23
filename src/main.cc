#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

int main(int argc, char *argv[]) {
  // Input data and first mask check
  std::string input;
  std::getline(std::cin, input);
  std::regex regex("\\s*\\+?\\d+(\\s+(([+-]?\\d+(\\.\\d*([eE][+-]?\\d*)?)?)|([+-]?\\d*[eE]\\d+))?)*(\\\\n)?");
  if (std::regex_match(input, regex)) {
    input = std::regex_replace(input, std::regex("\\\\n"), "");
  } else {
    std::cout << "[error]";
    return 0;
  }

  // Prepare data for processing and check task conditions
  std::vector<std::string> input_values;
  std::stringstream s(input);
  std::string value;
  while (s >> value)
    input_values.push_back(value);
  int length;
  try {
    length = std::stoi(input_values[0]);
  } catch (...) {
    std::cout << "[error]";
    return 0;
  }
  if ((input_values.size() - 1) < length || length < 2) {
    std::cout << "[error]";
    return 0;
  }
  std::vector<long double> source_chain;
  for (int i = 1; i < input_values.size(); i++) {
    try {
      source_chain.push_back(std::stold(input_values[i]));
    } catch (...) {
      std::cout << "[error]";
      return 0;
    }
  }

  // Process: searching the chain
  long double prev = source_chain[0];
  bool place_flag = false;
  int place, place_prev;
  int subchain_length = 1, subchain_length_prev = 1;
  for (int i = 1; i < length; i++) {
    if (source_chain[i] >= prev) {
      if (!place_flag) {
        place = i;
        place_flag = true;
      }
      subchain_length++;
    } else {
      if (subchain_length > 1) {
        if (subchain_length > subchain_length_prev) {
          subchain_length_prev = subchain_length;
          place_prev = place;
        }
      }
      place_flag = false;
      subchain_length = 1;
    }
    prev = source_chain[i];
  }
  if (subchain_length == source_chain.size() || subchain_length > subchain_length_prev) {
    subchain_length_prev = subchain_length;
    place_prev = place;
  }

  // Final output
  if (subchain_length_prev != 1) {
    std::cout << subchain_length_prev << " " << place_prev;
  } else {
    std::cout << "0";
  }
  return 0;
}