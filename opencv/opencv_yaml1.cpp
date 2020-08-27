#include <opencv2/opencv.hpp>
#include <glog/logging.h>
#include <vector>

class Config {
private:
    static std::shared_ptr<Config> config_;
    cv::FileStorage file_;

    Config() {}  // private constructor makes a singleton
public:
    ~Config();  // close the file when deconstructing

    // set a new config file
    static bool SetParameterFile(const std::string &filename);

    // access the parameter values
    template <typename T>
    static T Get(const std::string &key) {
      return T(Config::config_->file_[key]);
    }
};

bool Config::SetParameterFile(const std::string &filename) {
  if (config_ == nullptr)
    config_ = std::shared_ptr<Config>(new Config);
  static cv::FileStorage file1( filename.c_str(), cv::FileStorage::READ);
  config_->file_ = file1;
//  config_->file_ = cv::FileStorage(filename.c_str(), cv::FileStorage::READ);
  if (config_->file_.isOpened() == false) {
    LOG(ERROR) << "parameter file " << filename << " does not exist.";
    config_->file_.release();
    return false;
  }
  std::string dir;
  config_->file_["dataset_dir"] >> dir;
  LOG(INFO) << dir;
  return true;
}

Config::~Config() {
  if (file_.isOpened())
    file_.release();
}

std::shared_ptr<Config> Config::config_ = nullptr;

int main(int argc, char** argv) {
  cv::Mat
  Config::SetParameterFile("/home/liyanan/github/slambook2/ch13/config/default.yaml");
  return 0;
}