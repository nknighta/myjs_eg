#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "html_parser.h"
#include "window.h"
#include <windows.h>
#include "js_engine.h"

// Helper function to convert std::string to std::wstring
std::wstring s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (__argc < 2) {
        MessageBox(NULL, L"HTMLファイルを指定してください。", L"エラー", MB_OK | MB_ICONERROR);
        return 1;
    }

    std::string filename = __argv[1];
    if (filename.substr(filename.find_last_of(".") + 1) != "html") {
        MessageBox(NULL, L"HTMLファイルを指定してください。", L"エラー", MB_OK | MB_ICONERROR);
        return 1;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::string error_message_str = "ファイルを開けませんでした: " + filename;
        std::wstring error_message_wstr = s2ws(error_message_str);
        MessageBox(NULL, error_message_wstr.c_str(), L"エラー", MB_OK | MB_ICONERROR);
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    HTMLParser html_parser(content);
    std::vector<std::string> scripts = html_parser.get_scripts();
    std::vector<std::string> paragraphs = html_parser.get_paragraphs();
    
    SimpleJSEngine engine;
    for (const auto& script : scripts) {
        engine.execute(script);
    }

    HWND hWnd = CreateBrowserWindow(hInstance, nCmdShow, paragraphs);

    if (!hWnd) {
        return 1;
    }

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}