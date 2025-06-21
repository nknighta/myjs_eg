#pragma once

#include <windows.h>
#include <string>
#include <vector>

HWND CreateBrowserWindow(HINSTANCE hInstance, int nCmdShow, const std::vector<std::string>& paragraphs);
