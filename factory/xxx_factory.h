//
// Created by liyanan on 8/26/20.
//

#ifndef FACTORY_XXX_FACTORY_H
#define FACTORY_XXX_FACTORY_H

#include "abstract_object_factory.h"
#include "perception_macros.h"
#include "xxx_interface.h"

class XxxFactory : public AbstractObjectFactory{
public:
  ~XxxFactory() = default;
  XxxInterface* create(const std::string& name);
private:
  DECLARE_PERCEPTION_SINGLETON(XxxFactory);
};


#endif //FACTORY_XXX_FACTORY_H
