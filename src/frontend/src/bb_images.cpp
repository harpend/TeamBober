#include "bb_images.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <memory>

namespace bb_utils
{
  bool load_from_memory(const void *data, size_t size, uint32_t *out_TexRID, int *out_width, int *out_height)
  {
    int width = 0;
    int height = 0;

    uint8_t* img_data = stbi_load_from_memory((uint8_t*) data, (int) size, &width, &height, NULL, 4);
    if (img_data == nullptr)
    {
      return false;
    }

    uint32_t tex_rid;
    glGenTextures(1, &tex_rid);
    glBindTexture(GL_TEXTURE_2D, tex_rid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);

    stbi_image_free(img_data);

    *out_TexRID = tex_rid;
    *out_width = width;
    *out_height = height;

    return true;
  }

  bool load_from_file(const char *path, uint32_t *out_TexRID, int *out_width, int *out_height)
  {
    FILE* f = fopen(path, "rb");
    if (f == nullptr)
    {
      return false;
    }

    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t) ftell(f);
    if (file_size == -1)
    {
      return false;
    }

    fseek(f, 0, SEEK_SET);

    void* file_data = malloc(file_size);
    fread(file_data, 1, file_size, f);

    bool ret = load_from_memory(file_data, file_size, out_TexRID, out_width, out_height);
    free(file_data);

    return ret;
    
  }
}
