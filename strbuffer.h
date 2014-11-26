#ifndef _strbuffer_h
#define _strbuffer_h

struct StrBuffer {
  char* buf;
  size_t length;
  size_t max;
};

struct StrBuffer *StrBuffer_create();
void StrBuffer_destroy(struct StrBuffer *str);
int StrBuffer_append(struct StrBuffer *str, const char *data, size_t len);

#endif
