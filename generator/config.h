#pragma once

#include <string>
#include <vector>

#include "er/attributes.h"

// keeps parsed UTF-8 strings even on Windows
ER_REFLECT()
struct Config {
  std::string compdb_dir;

  struct Templates {
    std::string header;
    ER_ALIAS("enum")
    std::string for_enum;
    std::string object;
  } templates;

  std::vector<std::string> input;
  std::string output_dir;
};