#include <iostream>

#include "ParquetReader.h"
#include <span>

#include "EnvReader.h"

int main() {
    EnvReader envReader{};

    const std::string filePath = envReader.getVariable(EnvVars::PARQUET_FILE_LOCATION.data()).value();

    std::optional<ParquetReader> reader_opt = ParquetReader::open(filePath);
    if (!reader_opt.has_value()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }
    ParquetReader parquet_reader = std::move(reader_opt.value());

    for (const std::span<const uint8_t> header = parquet_reader.getParquetBytes(0, 4); const uint8_t byte : header) {
        std::cout << static_cast<char>(byte);
    }
    std::cout << std::endl;
    return 0;
}
