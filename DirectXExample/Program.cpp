#include "window/Window.cpp"
#include "render/Render.cpp"

#include <iostream>

int main()
{
    std::cout << "Creating Window\n";
    Window *pWindow = new Window();

    HWND hwnd = pWindow->GetHWND();
    int windowWidth = pWindow->GetWidth();
    int windowHeight = pWindow->GetHeight();

    Render renderer(hwnd, windowWidth, windowHeight);

    bool running = true;

    while (running)
    {
        running = pWindow->ProcessMessages();

        renderer.RenderFrame();
    }

    delete pWindow;
    std::cout << "Window Deleted\n";

    return 0;
}
