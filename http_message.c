
#include "http_message.h"

struct method_entry {
  char* str;
  enum MethodType type;
};

const struct method_entry method_type[] =
  {
    {"GET", GET},
    {"POST", POST},
    {"HEAD", HEAD}
  };

struct http_entry {
  char *str;
  enum HttpVersion version;
};

const struct http_entry http_version[] =
  {
    {"HTTP/0.9", HTTP_0_9},
    {"HTTP/1.0", HTTP_1_0}
  };

const char* status_text[] =
  {
    [OK] = "200 OK",
    [CREATED] = "201 Created",
    [ACCEPTED] = "202 Accepted",
    [NO_CONTENT] = "204 No Content",
    [MOVED_PERMANENTLY] = "301 Moved Permanently",
    [MOVED_TEMPORARILY] = "302 Moved Temporarily",
    [NOT_MODIFIED] = "304 Not Modified",
    [BAD_REQUEST] = "400 Bad Request",
    [UNAUTHORIZED] = "401 Unauthorized",
    [FORBIDDEN] = "403 Forbidden",
    [NOT_FOUND] = "404 Not Found",
    [INTERNAL_SERVER_ERROR] = "500 Internal Server Error",
    [NOT_IMPLEMENTED] = "501 Not Implemented",
    [BAD_GATEWAY] = "502 Bad Gateway",
    [SERVICE_UNAVAILABLE] = "503 Service Unavailable"
  };
