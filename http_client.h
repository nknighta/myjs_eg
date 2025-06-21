#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

// Fetches the content of a given URL.
std::string fetch_url(const std::wstring& url);

#endif // HTTP_CLIENT_H
