//
// Created by 潘绪洋 on 17-3-9.
// Copyright (c) 2017 Wuhan Collaborative Robot Technology Co.,Ltd. All rights reserved.
//


#include "abstract_object_factory.h"
#include <glog/logging.h>

AbstractObjectFactory::AbstractObjectFactory() {
}

AbstractObjectFactory::~AbstractObjectFactory() {
    LOG(INFO) << "Destructor " << typeid(this).name();
}