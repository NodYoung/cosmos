
#include <glog/logging.h>
#include "abstract_widget.h"


AbstractWidget::AbstractWidget() : QWidget(nullptr) {
}

AbstractWidget::~AbstractWidget() {
    LOG(INFO) << "[Destructor] " << typeid(this).name();
}