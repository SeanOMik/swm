#pragma once

#include <toml.hpp>
#include <toml/parser.hpp>
#include <toml/value.hpp>

#include "programs_config.h"

class Config {
public:
    ProgramsConfig programs;
    std::string path;

    Config(const std::string& config_path) {
        this->path = config_path; 

        toml::value toml = toml::parse(path + "config.toml");
        programs = ProgramsConfig(toml["Programs"]);
    }
};