//
// Created by marks on 15.07.2026.
//

#ifndef PRODUCTIONCPPROADMAP_FILEHANDLE_H
#define PRODUCTIONCPPROADMAP_FILEHANDLE_H

#include <filesystem>


class FileHandle final {
public:
    explicit FileHandle(
        const std::string& path,
        const char* mode
    );

    ~FileHandle() noexcept;

    FileHandle(const FileHandle&) = delete;
    FileHandle(FileHandle&& other) noexcept;

    FileHandle& operator=(const FileHandle&) = delete;
    FileHandle& operator=(FileHandle&& other) noexcept;

    [[nodiscard]] bool IsOpen() const noexcept;
    [[nodiscard]] std::FILE* Get() const noexcept;

private:
    void Close() noexcept;

    std::FILE* file_{nullptr};
};


#endif //PRODUCTIONCPPROADMAP_FILEHANDLE_H
