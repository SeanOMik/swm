#pragma once

#include <toml.hpp>
#include <toml/parser.hpp>
#include <toml/value.hpp>

#include "programs_config.h"

class Config {
public:
    ProgramsConfig programs;

    Config(const std::string& config_path) {
        toml::value toml = toml::parse(config_path);

        programs = ProgramsConfig(toml["Programs"]);
    }
};