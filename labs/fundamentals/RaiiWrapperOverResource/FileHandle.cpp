//
// Created by marks on 15.07.2026.
//

#include <utility>
#include "FileHandle.h"


FileHandle::FileHandle(
            const std::string& path,
            const char* mode
        )
    : file_(std::fopen(path.c_str(), mode))
{
    if (file_ == nullptr)
        throw std::runtime_error("Failed to open file: " + path);
}


FileHandle::~FileHandle() {
    Close();
}


// Move constructor
// A move does not copy ownership. It transfers ownership to a new object.
FileHandle::FileHandle(FileHandle&& other) noexcept
        : file_(std::exchange(other.file_, nullptr)) // std::exchange performs two operations
                                                                 // file_ = other.file_;
                                                                 // other.file_ = nullptr;
{
}


// Move assignment operator
FileHandle & FileHandle::operator=(FileHandle &&other) noexcept {
    if (this == &other)
        return *this;

    Close();

    file_ = std::exchange(other.file_, nullptr);

    return *this;
}


bool FileHandle::IsOpen() const noexcept {
    return file_ != nullptr;
}

std::FILE * FileHandle::Get() const noexcept {
    return file_;
}

void FileHandle::Close() noexcept {
    if (file_ == nullptr)
        return;

    std::fclose(file_);
    file_ = nullptr;
}
