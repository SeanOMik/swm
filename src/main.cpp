#include <iostream>
#include <string>

#include "config/config.h"

#include "xdg.hpp"

int main() {

#ifndef __DEBUG__
    Config config("config.toml");
#else
    std::string path = xdg::ConfigHomeDir();
    path += "/swm/config.toml";
    Config config(path);
#endif

    std::cout << "Terminal: \"" << config.programs.terminal << "\" - Launcher: \"" << config.programs.launcher << "\"" << std::endl;

    return 0;
}