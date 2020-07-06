
#include "abstract_camera.h"
#include <glog/logging.h>


AbstractCamera::AbstractCamera() {
}

AbstractCamera::~AbstractCamera() {
    LOG(INFO) << "Destructor " << typeid(this).name();
}

CameraStreamObserver::CameraStreamObserver() {
}

CameraStreamObserver::~CameraStreamObserver() {
    LOG(INFO) << "Destructor " << typeid(this).name();
}
