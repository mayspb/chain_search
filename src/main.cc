#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

int main(int argc, char *argv[]) {
  std::string input, output;
  std::getline(std::cin, input);
  std::regex regex("\\s*\\+?\\d+(\\s+(([+-]?\\d+(\\.\\d*([eE][+-]?\\d*)?)?)|([+-]?\\d*[eE]\\d+))?)*(\\\\n)?");
  if (std::regex_match(input, regex)) {
    //std::cout << "input valid" << std::endl;
    output = std::regex_replace(input, std::regex("\\s{2,}"), " ");
    output = std::regex_replace(output, std::regex("\\\\n"), "");
    //output = std::regex_replace(output, std::regex("^\\s"), "");
    //output = std::regex_replace(output, std::regex("\\s$"), "");
  } else {
    std::cout << "[error]";
    return 0;
  }
  std::vector<std::string> input_values;
  std::stringstream s(output);
  std::string value;
  while (s >> value)
    input_values.push_back(value);
  value = std::regex_replace(input_values[0], std::regex("\\+"), "");
  int length = std::stoi(value);
  if ((input_values.size() - 1) < length || length < 2) {
    std::cout << "[error]";
    return 0;
  }
  std::vector<long double> source_chain;
  for (int i = 1; i < input_values.size(); i++) {
    source_chain.push_back(std::stold(input_values[i]));
  }

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

  //std::cout << output << std::endl;
  if (subchain_length == source_chain.size() || subchain_length > subchain_length_prev) {
    subchain_length_prev = subchain_length;
    place_prev = place;
  }
  if (subchain_length_prev != 1) {
    std::cout << subchain_length_prev << " " << place_prev;
  } else {
    std::cout << "0";
  }
  return 0;
}