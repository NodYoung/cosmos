//
// Created by liyanan on 8/26/20.
//

#ifndef FACTORY_ABSTRACT_OBJECT_H
#define FACTORY_ABSTRACT_OBJECT_H

#include <string>
#include "perception_macros.h"

class AbstractObject {
public:
  AbstractObject() = default;
  virtual ~AbstractObject() = default;
  virtual const std::string& name() const = 0;

private:
  DISALLOW_COPY_AND_ASSIGN(AbstractObject);
};


#endif //FACTORY_ABSTRACT_OBJECT_H
