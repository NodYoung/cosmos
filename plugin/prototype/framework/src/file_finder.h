
#ifndef FILE_FINDER_H
#define FILE_FINDER_H

#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <map>

#include <QString>


class FileFinder {

public:
    enum PreDefPath {
        Bin,
        Data,
        Config,
        Script,
        Plugin,
        AppRuntimeDir
    };
public:
    static bool isFileExist(const std::string& filePath);
    static std::string find(const std::string& base_name);
    static QString find(const QString& base_name);
    static std::string find(const char* base_name);
    static void addSearchPath(const std::string& path_to_find, PreDefPath pathType = AppRuntimeDir);
    static std::string realPathOf(const std::string& path);

    static void loadDataPaths();

    static std::string getPreDefPath(PreDefPath pathType = Data);

    static void dumpAvailablePath();
protected:
    static void storSearchPath(const std::string& path_to_find, PreDefPath pathType);
    static std::vector<std::string> base_paths;
    static std::map<PreDefPath, std::string> pre_def_path;
};

#endif
