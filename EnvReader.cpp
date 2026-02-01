#include "EnvReader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

EnvReader::EnvReader() {
    const std::filesystem::path envFile = std::filesystem::current_path() / ".env";
    std::ifstream envFileStream(envFile);
    if (!envFileStream.is_open()) {
        std::cerr << "Failed to open environment variable file at: " << envFile.string() << std::endl;
    }

    std::string line;
    while (std::getline(envFileStream, line)) {
        parseLine(line);
    }
}

std::optional<std::string> EnvReader::getVariable(const std::string& key) {
    return variables_.at(key);
}

void EnvReader::parseLine(std::string line) {
    if (line.empty() || line.at(0) == '#') {
        return;
    }
    const size_t pos = line.find('=');
    if (pos == std::string::npos) return;

    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    variables_.emplace(key, value);
}

