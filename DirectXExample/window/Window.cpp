#include "headers/Window.h"

#include <tchar.h>

const int width = 800;
const int height = 600;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        SetWindowText(hWnd, _T("mouse pressed"));
        break;
    case WM_LBUTTONUP:
        SetWindowText(hWnd, _T("mouse released"));
        break;
    case WM_MOUSEMOVE:
        SetWindowText(hWnd, _T("mouse is moving"));
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
    : m_hinstance(GetModuleHandle(NULL)), m_width(width), m_height(height)
{

    LPCTSTR CLASS_NAME = _T("WindowClass");

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hinstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_SYSMENU;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        _T("Title"),
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hinstance,
        NULL);

    ShowWindow(m_hwnd, SW_SHOW);
}

Window::~Window()
{
    LPCTSTR CLASS_NAME = _T("WindowClass");

    UnregisterClass(CLASS_NAME, m_hinstance);
}

bool Window::ProcessMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

HWND Window::GetHWND() const
{
    return m_hwnd;
}

int Window::GetWidth() const
{
    return m_width;
}

int Window::GetHeight() const
{
    return m_height;
}