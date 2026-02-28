#pragma once

#include <filesystem>

namespace ProjectPaths {
    void initialize();

    const std::filesystem::path& getProjectRoot();

    std::filesystem::path getAssetsFolder();

    std::filesystem::path getAsset(const std::filesystem::path& relativePath);
}

