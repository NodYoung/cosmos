

#include <framework/src/abstract_object_factory.h>
//#include <extra2.h>
#include <glog/logging.h>
#include "framework/src/abstract_factory_macro.h"
#include "OpenCVCamera.h"

FACTORY_BEGIN(OpenCVCameraFactory)
        FACTORY_EXPORT(OpenCVCamera)
FACTORY_END(OpenCVCameraFactory, "1.0")