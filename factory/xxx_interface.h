//
// Created by liyanan on 8/26/20.
//

#ifndef FACTORY_XXX_INTERFACE_H
#define FACTORY_XXX_INTERFACE_H

#include "abstract_object.h"
#include "perception_macros.h"
#include "registerer.h"

class XxxInterface : public AbstractObject {
public:
  XxxInterface() = default;
  virtual ~XxxInterface() = default;
  virtual const std::string& name() const override;
  virtual int DoSomething() = 0;
private:
  const std::string name_ = "ObjectInterface";
  DISALLOW_COPY_AND_ASSIGN(XxxInterface);
};

REGISTER_REGISTERER(XxxInterface);
#define REGISTER_XXX_INTERFACE(name) REGISTER_CLASS(XxxInterface, name)

#endif //FACTORY_OBJECT_INTERFACE_H
