#include <stdlib.h>
#include <stdio.h>
#include "base_types.h"

function char* IO_ReadFile(const char* path, B8 readBytes)
{
  char* buffer;
  FILE* file;
  I64 length;

  if (readBytes)
    fopen_s(&file, path, "rb");
  else
    fopen_s(&file, path, "r");

  if (!file)
    return NULL;

  fseek (file, 0, SEEK_END);
  length = ftell(file);
  fseek (file, 0, SEEK_SET);

  buffer = (char*)calloc(1, (U64)length);
  fread (buffer, 1, length, file);

  fclose (file);

  if (buffer)
    return buffer;
  return NULL;
}