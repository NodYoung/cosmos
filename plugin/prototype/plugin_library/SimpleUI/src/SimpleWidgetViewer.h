

#ifndef SIMPLEUI_SIMPLEWIDGETVIEWER_H
#define SIMPLEUI_SIMPLEWIDGETVIEWER_H

#include "framework/src/botsys.h"
#include "framework/src/abstract_widget.h"
#include "ui_SimpleWidgetViewer.h"
#include "WidgetCloser.h"
#include <QStringList>
#include <QTimer>
#include <QTextCursor>


class SimpleWidgetViewer : public AbstractWidget {
Q_OBJECT
public:
    SimpleWidgetViewer();
    virtual ~SimpleWidgetViewer();

    virtual bool setup(const QString& configFilePath);

public:
    void actionCreateWidget();
    void actionClear();
    void actionCreateWidgetNoJson();

protected:
    void refreshWidgetList();
    void resetCurObj();

    void createTextLogUi();
    void updateTextToUI();
    void appendText(const std::string& message);

protected:
    Ui::SimpleWidgetViewer ui;
    std::shared_ptr<AbstractObject> m_pWidget;
    WidgetCloser* m_closer;


    QTimer* m_editUpdateTimer;
    QString m_cachedMessage;
    QTextCursor m_textCursor;
};


#endif
