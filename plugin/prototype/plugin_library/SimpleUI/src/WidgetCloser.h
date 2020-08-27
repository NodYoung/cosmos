

#ifndef SIMPLEUI_WIDGETCLOSER_H
#define SIMPLEUI_WIDGETCLOSER_H

#include <QObject>
#include <QEvent>


class WidgetCloser : public QObject {
Q_OBJECT
public:
	WidgetCloser(QObject* parent);
Q_SIGNALS:
    void widgetClosed();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
};


#endif
