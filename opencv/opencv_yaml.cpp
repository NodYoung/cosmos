//
// Created by liyanan on 7/28/20.
//


#include <opencv2/opencv.hpp>
#include <vector>

int write() {
  std::string fileName = "datas.yaml";  //文件的名称
  //以写入的模式打开文件
  cv::FileStorage fwrite("datas.yaml", cv::FileStorage::WRITE);

  //存入矩阵Mat类型的数据
  cv::Mat mat = cv::Mat::eye(3, 3, CV_8U);
  fwrite.write("mat", mat);  //使用write()函数写入数据
  //存入浮点型数据，节点名称为x
  float x = 100;
  fwrite << "x" << x;
  //存入字符串型数据，节点名称为str
  std::string str = "Learn OpenCV 4";
  fwrite << "str" << str;
  //存入数组,节点名称为number_array
  fwrite << "number_array" << "[" <<4<<5<<6<< "]";
  //存入多node节点数据,主名称为multi_nodes
  fwrite << "multi_nodes" << "{" << "month" << 8 << "day" << 28 << "year"
         << 2019 << "time" << "[" << 0 << 1 << 2 << 3 << "]" << "}";
  //关闭文件
  fwrite.release();
  return 0;
}

int read() {
  //以读取的模式打开文件
  cv::FileStorage fread("datas.yaml", cv::FileStorage::READ);
  //判断是否成功打开文件
  if (!fread.isOpened()) {
    std::cout << "打开文件失败，请确认文件名称是否正确！" << std::endl;
    return -1;
  }
  //读取文件中的数据
  float xRead;
  fread["x"] >> xRead;  //读取浮点型数据
  std::cout << "x=" << xRead << std::endl;

  //读取字符串数据
  std::string strRead;
  fread["str"] >> strRead;
  std::cout << "str=" << strRead << std::endl;

  //读取含多个数据的number_array节点
  cv::FileNode fileNode = fread["number_array"];
  std::cout << "number_array=[";
  //循环遍历每个数据
  for (cv::FileNodeIterator i = fileNode.begin(); i != fileNode.end(); i++) {
    float a;
    *i >> a;
    std::cout << a<<" ";
  }
  std::cout << "]" << std::endl;

  //读取Mat类型数据
  cv::Mat matRead;
  fread["mat"] >> matRead;
  std::cout << "mat=" << matRead << std::endl;

  //读取含有多个子节点的节点数据，不使用FileNode和迭代器进行读取
  cv::FileNode fileNode1 = fread["multi_nodes"];
  int month = (int)fileNode1["month"];
  int day = (int)fileNode1["day"];
  int year = (int)fileNode1["year"];
  std::cout << "multi_nodes:" << std::endl << "  month=" << month << "  day=" << day << "  year=" << year;
  std::cout << "  time=[";
  for (int i = 0; i < 4; i++) {
    int a = (int)fileNode1["time"][i];
    std::cout << a << " ";
  }
  std::cout << "]" << std::endl;

  //关闭文件
  fread.release();
  return 0;
}

int write1() {
  cv::FileStorage file = cv::FileStorage("/home/liyanan/github/slambook2/ch13/config/default.yaml", cv::FileStorage::WRITE);
  file.write("dataset_dir", "/home/liyanan/github/slambook2/kitti/00");
  file.write("num_features", 150);
  file.write("num_features_init", 50);
  std::string strRead;
  file["dataset_dir"] >> strRead;
  std::cout << "dataset_dir=" << strRead << std::endl;
  file.release();

  return 0;
}

int read1() {
  cv::FileStorage file = cv::FileStorage("/home/liyanan/github/slambook2/ch13/config/default.yaml", cv::FileStorage::READ);
  if (!file.isOpened()) {
    std::cout << "打开文件失败，请确认文件名称是否正确！" << std::endl;
    return -1;
  }
  std::string strRead;
  file["dataset_dir"] >> strRead;
  std::cout << "dataset_dir=" << strRead << std::endl;
  file.release();

  return 0;
}

int main(int argc, char** argv) {
  read1();
  return 0;
}