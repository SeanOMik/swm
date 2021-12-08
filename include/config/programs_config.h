#pragma once

#include <toml.hpp>
#include <toml/parser.hpp>
#include <toml/value.hpp>

class ProgramsConfig {
public:
    std::string terminal;
    std::string launcher;

    /* ProgramsConfig(const std::string& config_path) : ProgramsConfig(toml::parse(config_path)) {

    } */

    ProgramsConfig() = default;

    ProgramsConfig(toml::value& toml_config) {
        terminal = toml_config["terminal"].as_string();
        launcher = toml_config["launcher"].as_string();
    }
};