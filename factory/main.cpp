//
// Created by liyanan on 8/26/20.
//
#include <glog/logging.h>
#include "xxx_factory.h"
#include "xxx_interface.h"

int main() {
  XxxInterface* p1 = XxxInterfaceRegisterer::get_instance_by_name("XxxConcrete");
  p1->DoSomething();
  LOG(INFO) << "hello";
  return 0;
}