#include <glog/logging.h>
#include <framework/src/botsys.h>
#include <framework/src/global_object_factory.h>
#include <framework/src/abstract_camera.h>
#include <QApplication>
#include <QFileDialog>

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  // 初始化botsys内部的变量
  init_library(argc, argv);
  // cobotsys的对象工厂
  GlobalObjectFactory globalObjectFactory;
  // 加载默认路径下的所有插件
  globalObjectFactory.loadLibrarys();
  auto pObject = globalObjectFactory.createObject("OpenCVCameraFactory, Ver 1.0", "OpenCVCamera");

  auto pRobot = std::dynamic_pointer_cast<AbstractCamera>(pObject);
  if (pRobot) {
    if (pObject->setup("CONFIG/UrRobotConfig/ur_sim_config.json")) {
      LOG(INFO) << "hello";
//      pRobot->setTargetJointFilter(std::dynamic_pointer_cast<cobotsys::ArmRobotJointTargetFilter>(pFilter));
//      pRobot->start();
      return a.exec();
    }
  }


  return 0;
}