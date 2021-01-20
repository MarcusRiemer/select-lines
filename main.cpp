#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cast.hpp"

typedef std::uint64_t line_index;

const int ERR_NUM_ARGS = 1;
const int ERR_FILE_OPEN = 2;

int main(int argc, char **argv) {
  auto args = std::vector<std::string>(argv + 1, argv + argc);
  if (args.size() != 3) {
    std::cout << "Usage: <filename> <first_line> <num_lines>" << std::endl;
    return ERR_NUM_ARGS;
  }

  const std::string filename = args[0];
  line_index start = lexical_cast<line_index>(args[1]);
  line_index count = lexical_cast<line_index>(args[2]);
  line_index end = start + count;

  line_index current_line_num = 1;
  std::string current_line;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Something went wrong when opening the file" << std::endl;
    return ERR_FILE_OPEN;
  }

  while (current_line_num < end && std::getline(file, current_line, '\n')) {
    if (current_line_num >= start && current_line_num < end) {
      std::cout << current_line << std::endl;
    }

    current_line_num++;
  }

  return 0;
}
