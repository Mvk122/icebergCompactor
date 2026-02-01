//
// Created by Madhav Khandhar on 01/02/2026.
//

#ifndef ICEBERGCOMPACTOR_ENVREADER_H
#define ICEBERGCOMPACTOR_ENVREADER_H
#include <unordered_map>
#include <string>

namespace EnvVars {
    inline constexpr std::string_view PARQUET_FILE_LOCATION = "PARQUET_FILE_LOCATION";
}

class EnvReader {
public:
    EnvReader();

    std::optional<std::string> getVariable(const std::string& key);


private:
    std::unordered_map<std::string, std::string> variables_;
    void parseLine(std::string line);
};


#endif //ICEBERGCOMPACTOR_ENVREADER_H