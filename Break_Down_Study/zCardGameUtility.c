#include <memory.h> //memset
#include <stdlib.h> //malloc
#include "zCardGameUtility.h"

// only used in zGame.c

void *mallocz(size_t size) {
  void *ptr;
  ptr = malloc(size);
  if (!ptr)
    return NULL;
  memset(ptr, 0, size);
  return ptr;
}