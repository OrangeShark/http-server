

#include "http_message.h"

int is_tspecial(char c)
{
  switch c {
    case '\t':
    case ' ':
    case '"':
    case '(':
    case ')':
    case ',':
    case '/':
    case ':' ... '@':
    case '[' ... ']':
    case '{':
    case '}':
      return 1;
    default:
      return 0;
    }
}

int is_ctl(char c)
{
  if((c >= 0 && c <= 31) || c == 127)
    return 1;
  return 0;
}

struct HttpRequest *http_request_parse()
{

}
