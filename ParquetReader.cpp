#include "ParquetReader.h"

#include "ParquetReader.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Used for creating a ParquetReader object, by calling ParquetReader::open(filepath);
 * Optional, for if opening the file didn't work
 */
std::optional<ParquetReader> ParquetReader::open(const std::string& path) {
    const int fd = ::open(path.c_str(), O_RDONLY);
    struct stat sb{};
    if (fd == -1 || fstat(fd, &sb) == -1) {
        if (fd != -1) ::close(fd);
        return std::nullopt;
    }

    void* addr = mmap(nullptr, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        ::close(fd);
        return std::nullopt;
    }
        return ParquetReader(fd, sb.st_size, static_cast<const uint8_t*>(addr));
}

// Deconstructor
ParquetReader::~ParquetReader() {
    if (fd_ != -1) {
        munmap(const_cast<uint8_t*>(data_), size_);
        ::close(fd_);
    }
}

// Weird copying thing
ParquetReader::ParquetReader(ParquetReader&& other) noexcept : fd_(other.fd_), size_(other.size_), data_(other.data_) {
    other.fd_ = -1;
}

// Move constructor, makes the old value no longer have access to the file descriptor
ParquetReader& ParquetReader::operator=(ParquetReader&& o) noexcept {
    if (this != &o) {
        this->~ParquetReader();
        fd_ = o.fd_; size_ = o.size_; data_ = o.data_;
        o.fd_ = -1;
    }
    return *this;
}

std::span<const uint8_t> ParquetReader::getParquetBytes(size_t offset, size_t length) {
    if (offset + length > size_) {
        return {};
    }
    return {data_ + offset, length};
}
