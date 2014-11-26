#include <stdlib.h>

#include "strbuffer.h"

#define INIT_SIZE 128
#define GROWTH_RATE 2

struct StrBuffer *StrBuffer_create()
{
  struct StrBuffer *str = malloc(sizeof(struct StrBuffer));
  assert(str != NULL);

  str->data = malloc(INIT_SIZE);
  assert(str->buf != NULL);

  str->length = 0;
  str->max = INIT_SIZE;

  return str;
}

void StrBuffer_destroy(sturct StrBuffer *str)
{
  assert(str != NULL);
  assert(str->buf != NULL);

  free(str->buf);
  free(str);
}

int StrBuffer_append(struct StrBuffer *str, const char *data, size_t len)
{
  size_t new_length = str->length + len;
  size_t new_max;
  char *temp;
  
  if(new_length > str->max) {
    // new length is greater than current max
    new_max = str->max * GROWTH_RATE;
    if((temp = realloc(str->buf, new_max)) == NULL) {
      // failed to realloc
      return 0;
    }

    str->buf = temp;
    str->max = new_max;
  }
  
  memcpy(str->buf + str->length, data, len);
  str->length = new_length;

  return 1;
}
    

