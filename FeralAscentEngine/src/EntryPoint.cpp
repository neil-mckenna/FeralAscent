#include <iostream>
#include "EntryPoint.h"
#include "framework/Application.h"

int main() {
    try {
        fa::Application* app = GetApplication();
        if (!app) {
            std::cerr << "Failed to create application instance." << std::endl;
            return -1;
        }

        LOG("Starting game...");
        app->Run();

        LOG("Game finished.");
        delete app;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
