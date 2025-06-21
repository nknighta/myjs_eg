#include "http_client.h"
#include <windows.h>
#include <wininet.h>
#include <stdexcept>

#pragma comment(lib, "wininet.lib")

std::string fetch_url(const std::wstring& url) {
    HINTERNET hInternet = InternetOpenW(L"MiniBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        throw std::runtime_error("InternetOpen failed");
    }

    HINTERNET hConnect = InternetOpenUrlW(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        throw std::runtime_error("InternetOpenUrl failed");
    }

    std::string result;
    char buffer[4096];
    DWORD bytesRead;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        result.append(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return result;
}
