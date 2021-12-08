#include <iostream>

#include "config/config.h"

int main() {
    Config config("config.toml");

    std::cout << "Terminal: \"" << config.programs.terminal << "\" - Launcher: \"" << config.programs.launcher << "\"" << std::endl;
    
    return 0;
}