#include <iostream>
#include "Window.cpp"

int main()
{
    std::cout << "Creating Window\n";

    Window *pWindow = new Window();

    bool running = true;

    while (running)
    {
        running = pWindow->ProcessMessages();

        if (GetAsyncKeyState(VK_ESCAPE))
            running = false;
    }

    delete pWindow;

    return 0;
}
