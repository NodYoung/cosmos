//
// Created by liyanan on 8/26/20.
//

#include "xxx_concrete.h"
#include "glog/logging.h"

int XxxConcrete::DoSomething() {
  LOG(INFO) << "DoSomething";
  return 0;
}

REGISTER_XXX_INTERFACE(XxxConcrete);