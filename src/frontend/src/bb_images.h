#pragma once
#include <glad/glad.h>
#include <cstdint>
#include <cstddef>

namespace bb_utils
{

  bool load_from_memory(const void* data, size_t size, uint32_t* out_TexRID, int* out_width, int* out_height);
  bool load_from_file(const char* path, uint32_t* out_TexRID, int* out_width, int* out_height);
  
}
