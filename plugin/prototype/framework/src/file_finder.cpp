#include "file_finder.h"
#include <QDir>
#include <QtCore/QCoreApplication>
#include <glog/logging.h>


#ifdef WIN32
std::string path_slash = "\\";
#else
std::string path_slash = "/";
#endif

std::vector<std::string> FileFinder::base_paths;
std::map<FileFinder::PreDefPath, std::string> FileFinder::pre_def_path;

std::string FileFinder::find(const std::string& base_name) {
    if (isFileExist(base_name))
        return realPathOf(base_name);

    std::string path;
    for (const auto& base : base_paths) {
        if (base[0] == '.')
            path = "." + path_slash + base + path_slash + base_name;
        else
            path = base + path_slash + base_name;
        if (isFileExist(path))
            return realPathOf(path);
    }

    return std::string();
}

void FileFinder::loadDataPaths() {
    std::string app_path = QCoreApplication::applicationDirPath().toLocal8Bit().constData();
    addSearchPath(app_path + "/../data", Data);
    addSearchPath(app_path + "/../plugins", Plugin);
#ifndef WIN32
    addSearchPath("../../data", Data);
#endif

    LOG(INFO) << "File Finder" << "Current Path: " << realPathOf(".");
}

bool FileFinder::isFileExist(const std::string& filePath) {
    struct stat stFileInfo;
    int intStat;

    // Attempt to get the file attributes
    intStat = stat(filePath.c_str(), &stFileInfo);
    if (intStat == 0) {
        return true;
    } else {
        return false;
    }
}

std::string FileFinder::realPathOf(const std::string& path) {
    std::vector<char> ch_buf(1024);
#ifdef WIN32
    auto pfull = _fullpath(&ch_buf[0], path.c_str(), ch_buf.size());
#else
    auto pfull = realpath(path.c_str(), &ch_buf[0]);
#endif
    if (pfull) {
        std::string rpath = pfull;
        bool isExist = isFileExist(rpath);
        if (isExist) {
            return rpath;
        }
    }
    return std::string();
}

void FileFinder::storSearchPath(const std::string& path_to_find, PreDefPath pathType) {

    for (auto& iter : base_paths) {
        if (iter == path_to_find) {
            return;
        }
    }

    if (pathType != AppRuntimeDir) {
        base_paths.erase(std::remove_if(base_paths.begin(), base_paths.end(),
                                        [=](const std::string& s) { return s == pre_def_path[pathType]; }),
                         base_paths.end());
    }

    base_paths.push_back(path_to_find);
    pre_def_path[pathType] = path_to_find;
}

std::string realPath2(const std::string& path_to_find) {
    QDir dir(QDir::currentPath());
    dir.setPath(QString::fromLocal8Bit(path_to_find.c_str()));
    if (dir.exists()) {
        return dir.absolutePath().toLocal8Bit().constData();
    }
    return std::string();
}

void FileFinder::addSearchPath(const std::string& path_to_find, FileFinder::PreDefPath pathType) {
    auto rpath = realPath2(path_to_find);
    if (rpath.size()) {
        storSearchPath(rpath, pathType);
    } else {
        for (const auto& path : base_paths) {
            auto tmp_path = path + path_slash + path_to_find;
            rpath = realPath2(tmp_path);
            if (rpath.size()) {
                storSearchPath(rpath, pathType);
                break;
            }
        }
    }
}

std::string FileFinder::getPreDefPath(PreDefPath pathType) {
    return pre_def_path[pathType];
}

void FileFinder::dumpAvailablePath() {
    for (auto& path : base_paths) {
        LOG(INFO) << "File Finder" << "Path: " << path;
        for (auto& iter : pre_def_path) {
            if (iter.second == path) {
                if (iter.first == PreDefPath::Data) LOG(INFO) << ", Data";
                if (iter.first == PreDefPath::Plugin) LOG(INFO) << ", Plugin";
                if (iter.first == PreDefPath::Config) LOG(INFO) << ", Config";
                if (iter.first == PreDefPath::Bin) LOG(INFO) << ", Bin";
                if (iter.first == PreDefPath::Script) LOG(INFO) << ", Script";
            }
        }
    }
}

QString FileFinder::find(const QString& base_name) {
    std::string s = base_name.toLocal8Bit().constData();
    auto rs = find(s);
    return QString::fromLocal8Bit(rs.c_str());
}

std::string FileFinder::find(const char* base_name) {
    return find(std::string(base_name));
}
