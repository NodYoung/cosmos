//
// Created by liyanan on 8/26/20.
//

#ifndef FACTORY_XXX_CONCRETE_H
#define FACTORY_XXX_CONCRETE_H

#include "xxx_interface.h"

class XxxConcrete : public XxxInterface {
public:
  XxxConcrete() = default;
  virtual ~XxxConcrete() = default;
  virtual int DoSomething();
DISALLOW_COPY_AND_ASSIGN(XxxConcrete);
};


#endif //FACTORY_XXX_CONCRETE_H
