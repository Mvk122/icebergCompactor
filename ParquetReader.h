#ifndef ICEBERGCOMPACTOR_PARQUETREADER_H
#define ICEBERGCOMPACTOR_PARQUETREADER_H

#include <string>
#include <optional>
#include <span>


class ParquetReader {
public:
    static std::optional<ParquetReader> open(const std::string& path);
    std::span<const uint8_t> getParquetBytes(size_t offset, size_t length);
    ~ParquetReader();

    // Disable Copying
    ParquetReader(const ParquetReader&) = delete;
    ParquetReader& operator=(const ParquetReader&) = delete;

    // Enable Moving
    ParquetReader(ParquetReader&& other) noexcept;
    ParquetReader& operator=(ParquetReader&& other) noexcept;

    [[nodiscard]] const uint8_t* data() const { return data_; }
    [[nodiscard]] size_t size() const { return size_; }

private:
    ParquetReader(const int fd, const size_t size, const uint8_t* data)
        : fd_(fd), size_(size), data_(data) {}

    int fd_;
    size_t size_;
    const uint8_t* data_;
};

#endif //ICEBERGCOMPACTOR_PARQUETREADER_H