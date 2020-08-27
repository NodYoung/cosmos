//
// Created by liyanan on 8/26/20.
//

#include "xxx_factory.h"

XxxFactory::XxxFactory() {

}

XxxInterface* XxxFactory::create(const std::string& name) {
  XxxInterface* p_xxx_interface = nullptr;
  p_xxx_interface = XxxInterfaceRegisterer::get_instance_by_name(name);
  return p_xxx_interface;
}
