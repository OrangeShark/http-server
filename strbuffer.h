#ifndef _strbuffer_h
#define _strbuffer_h

struct StrBuffer {
  char* buf;
  size_t length;
  size_t max;
};

struct StrSlice {
  struct StrBuffer *str;
  size_t pos;
  size_t length;
};

struct StrBuffer *StrBuffer_create();
void StrBuffer_destroy(struct StrBuffer *str);
int StrBuffer_append(struct StrBuffer *str, const char *data, size_t len);
struct StrSlice *StrBuffer_slice(struct StrBuffer *str, int start, int stop);

struct StrSlice *StrSlice_create(struct StrBuffer *str, int start, int stop);
void StrSlice_destroy(struct StrSlice *slice);
char StrSlice_get(struct StrSlice *slice, int index);
char *StrSlice_ncopy(struct StrSlice *slice, size_t n);
char *StrSlice_copy(struct StrSlice *slice);
#endif
