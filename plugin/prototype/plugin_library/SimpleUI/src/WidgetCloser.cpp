

#include "WidgetCloser.h"
#include <framework/src/abstract_object.h>

WidgetCloser::WidgetCloser(QObject* parent) :QObject(parent) {

}

bool WidgetCloser::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::Close) {
		auto aobj = dynamic_cast<cobotsys::AbstractObject*>(obj);
		if (aobj) {
			Q_EMIT widgetClosed();
		}
	}
	return QObject::eventFilter(obj, event);
}
