#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strbuffer.h"

#define INIT_SIZE 128
#define GROWTH_RATE 2

struct StrBuffer *StrBuffer_create()
{
  struct StrBuffer *str = malloc(sizeof(struct StrBuffer));
  assert(str != NULL);

  str->buf = malloc(INIT_SIZE);
  assert(str->buf != NULL);

  str->length = 0;
  str->max = INIT_SIZE;

  return str;
}

void StrBuffer_destroy(struct StrBuffer *str)
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

struct StrSlice *StrBuffer_slice(struct StrBuffer *str,
                                     int start, int stop)
{
  int length = stop - start;
  if(length <= 0 || stop >= str->length)
    return NULL;

  struct StrSlice *slice = malloc(sizeof(struct StrSlice));
  assert(slice != NULL);

  slice->str = str;
  slice->pos = start;
  slice->length = length;

  return slice;
}

struct StrSlice *StrSlice_create(struct StrBuffer *str, int start, int stop)
{
  return NULL;
}

void StrSlice_destroy(struct StrSlice *slice)
{
  assert(slice != NULL);

  free(slice);
}

char StrSlice_get(struct StrSlice *slice, int index)
{
  if(index >= slice->length)
    return EOF;

  return slice->str->buf[slice->pos + index];
}

char *StrSlice_ncopy(struct StrSlice *slice, size_t n)
{
  return NULL; //strndup(slice->str->buf[slice->pos], n);
}

char *StrSlice_copy(struct StrSlice *slice)
{
  return StrSlice_ncopy(slice, slice->length);
}
    

