//
// Created by liyanan on 5/31/19.
//

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

bool FindFiles(const std::string& dir, const std::string& file_suffix, std::vector<std::string>& files, bool recursive=false) {
    path p(dir);
    if (!exists(p) || !is_directory(p)) {
        return false;
    }
    if (recursive) {
        recursive_directory_iterator end;
        for (recursive_directory_iterator pos(p); pos != end; ++pos) {
            if(!is_directory(*pos) && pos->path().filename().string().find_last_of('.') != std::string::npos) {
                auto const n = pos->path().filename().string().find_last_of('.');
                if (pos->path().filename().string().substr(n+1) == file_suffix) {
                    files.push_back(pos->path().filename().string().substr(0, n));
                }
            }
        }
    }
    else {
        directory_iterator end;
        for (directory_iterator pos(p); pos != end; ++pos) {
            if(!is_directory(*pos) && pos->path().filename().string().find_last_of('.') != std::string::npos) {
                auto const n = pos->path().filename().string().find_last_of('.');
                if (pos->path().filename().string().substr(n+1) == file_suffix) {
                    files.push_back(pos->path().filename().string().substr(0, n));
                }
            }
        }
    }
    return true;
}

int main() {
    std::vector<std::string> files;
    FindFiles("/home/liyanan/autogen_ws/autogen_abc/.config", "prototxt", files, true);
    for(const auto & v : files) {
        std::cout << v << std::endl;
    }
    std::cout << current_path() << std::endl;
    return 0;
}