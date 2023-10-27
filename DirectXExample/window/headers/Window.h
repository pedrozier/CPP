#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
    Window();
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    ~Window();

    bool ProcessMessages();

    HWND GetHWND() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    HINSTANCE m_hinstance;
    HWND m_hwnd;
    int m_width;
    int m_height;
};