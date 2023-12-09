#pragma once

#include "cpp-dump/dump.hpp"
struct cpp_dump_options {
  cpp_dump_options() {
    cpp_dump::es_style = cpp_dump::es_style_t::no_es;
    cpp_dump::log_label_func = cpp_dump::log_label::filename();
  }
};
cpp_dump_options __dummyOptions;
#define dbg cpp_dump