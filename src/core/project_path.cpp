#include "core/project_path.hpp"
#include <filesystem>
#include <windows.h>
#include <iostream>

namespace ProjectPaths {
    static std::filesystem::path projectRoot;

    void initialize(){
        char buffer[MAX_PATH];

        DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);

        if (length == 0){
            std::cerr << "Error obteniendo la ruta del ejecutable.\n";
            return;
        };

        std::filesystem::path exePath(buffer);
        std::filesystem::path exeFolder = exePath.parent_path();

        projectRoot = exeFolder.parent_path();
        projectRoot = std::filesystem::weakly_canonical(projectRoot);
    }

    const std::filesystem::path& getProjectRoot(){
        return projectRoot;
    }

    std::filesystem::path getAssetsFolder(){
        return projectRoot / "assets";
    }

    std::filesystem::path getAsset(const std::filesystem::path& relativePath){
        return getAssetsFolder() / relativePath;
    }
}