#include "abstract_object.h"
#include <glog/logging.h>

AbstractObject::AbstractObject() {
}

AbstractObject::~AbstractObject() {
    LOG(INFO) << "Destructor " << typeid(this).name();
}

void AbstractObject::clearAttachedObject() {
}