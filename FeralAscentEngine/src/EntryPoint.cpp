#include <iostream>
#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
    fa::Application* app = GetApplication();
    if (!app) {
        std::cerr << "Failed to create application instance." << std::endl;
        return -1;
    }
    app->Run();
    delete app;
    return 0;
}