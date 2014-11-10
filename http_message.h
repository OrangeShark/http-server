#ifndef _http_message_h
#define _http_message_h

enum MethodType {
  GET,
  POST,
  HEAD
};

enum StatusCode {
  OK,
  CREATED,
  ACCEPTED,
  NO_CONTENT,
  MOVED_PERMANENTLY,
  MOVED_TEMPORARILY,
  NOT_MODIFIED,
  BAD_REQUEST,
  UNAUTHORIZED,
  FORBIDDEN,
  NOT_FOUND,
  INTERNAL_SERVER_ERROR,
  NOT_IMPLEMENTED,
  BAD_GATEWAY,
  SERVICE_UNAVAILABLE
};


enum HttpVersion {
  HTTP_0_9,    // HTTP/0.9
  HTTP_1_0    // HTTP/1.0
};

struct HttpRequest {
  // Request Line
  enum MethodType method;
  enum HttpVersion version;
  char *uri;
  // General Headers
  char *date;
  char *pragma;
  // Request Headers
  char *if_modified_since;
  char *user_agent;
  // Entity Headers
  char *allow;
  char *content_encoding;
  int content_length;
  char *content_type;
  char *expires;
  char *last_modified;
  // Entity Body
  char *body;
};

struct HttpResponse {
  // Status Line
  enum HttpVersion version;
  enum StatusCode status;
  // General Headers
  char *date;
  char *pragma;
  // Response Headers
  char *location;
  char *server;
  char *www_authenticate;
  // Entity Header
  char *allow;
  char *content_encoding;
  int content_length;
  char *content_type;
  char *expires;
  char *last_modified;
  // Entity Body
  char *body;
};

struct HttpRequest *HttpRequest_create(enum MethodType method,
                                       enum HttpVersion version,
                                       char *uri);
void HttpRequest_destroy(struct HttpRequest *request);

struct HttpResponse *HttpResponse_create(enum HttpVersion version,
                                         enum StatusCode status);
void HttpResponse_destroy(struct HttpResponse *response);

#endif
