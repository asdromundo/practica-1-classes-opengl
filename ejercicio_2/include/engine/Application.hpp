#pragma once
#include <string>

class Application
{
public:
    Application(int width, int height, const std::string &title);
    ~Application();

    int run();
};
