#pragma once

#include <iostream> // std::cout
#include <optional> // return obj or null
#include <filesystem> // fs
#include <windows.h> // get_executable_path()
#include <fstream> // file open

namespace fs = std::filesystem;

inline bool chechFileExist(const fs::path& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

inline bool checkFolderExist(const fs::path& path) {
    return fs::exists(path) && fs::is_directory(path);
}

fs::path get_executable_path() {
    WCHAR buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    return fs::path(buffer).parent_path();
}

size_t count_elements(const fs::path& dir) {
    size_t count = 0;
    for (auto it = fs::recursive_directory_iterator(dir); it != fs::recursive_directory_iterator(); ++it)
        ++count;
    return count;
}
