#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

// status code and reason phrase
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

struct HttpRequest *HttpRequest_create(enum MethodType method,
                                       enum HttpVersion version,
                                       char *uri)
{
  struct HttpRequest *request = malloc(sizeof(struct HttpRequest));
  assert(request != NULL);

  request->method = method;
  request->version = version;
  request->uri = strdup(uri);
  request->date = NULL;
  request->pragma = NULL;
  request->if_modified_since = NULL;
  request->user_agent = NULL;
  request->allow = NULL;
  request->content_encoding = NULL;
  request->content_length = 0;
  request->content_type = NULL;
  request->expires = NULL;
  request->last_modified = NULL;
  request->body = NULL;

  return request;
}

void HttpRequest_destroy(struct HttpRequest *request)
{
  assert(request != NULL);

  free(request->uri);
  free(request);
}

struct HttpResponse *HttpReesponse_create(enum HttpVersion version,
                                          enum StatusCode status)
{
  struct HttpResponse *response = malloc(sizeof(struct HttpResponse));
  assert(response != NULL);

  response->version = version;
  response->status = status;
  response->date = NULL;
  response->pragma = NULL;
  response->location = NULL;
  response->server = NULL;
  response->www_authenticate = NULL;
  response->allow = NULL;
  response->content_encoding = NULL;
  response->content_length = 0;
  response->content_type = NULL;
  response->expires = NULL;
  response->last_modified = NULL;
  response->body = NULL;

  return response;
}

void HttpResponse_destroy(struct HttpResponse *response)
{
  assert(response != NULL);
  
  free(response);
}
