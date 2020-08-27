

#include <framework/src/global_object_factory.h>
#include <QtWidgets/QFileDialog>
#include <framework/src/file_finder.h>
#include <framework/src/botsys_logger.h>
#include <glog/logging.h>
#include "SimpleWidgetViewer.h"
#include <QSysInfo>

SimpleWidgetViewer::SimpleWidgetViewer() {
    ui.setupUi(this);
    m_closer = new WidgetCloser(this);

    connect(ui.btnCreate, &QPushButton::released, this, &SimpleWidgetViewer::actionCreateWidget);
    connect(ui.btnCreateNoJson, &QPushButton::released, this, &SimpleWidgetViewer::actionCreateWidgetNoJson);
    connect(ui.btnClear, &QPushButton::released, this, &SimpleWidgetViewer::actionClear);
    connect(m_closer, &WidgetCloser::widgetClosed, this, &SimpleWidgetViewer::resetCurObj);

    createTextLogUi();
}

SimpleWidgetViewer::~SimpleWidgetViewer() {
    BOT_LOG.clrFilter(this);
    LOG(INFO) << "[Destructor] " << typeid(this).name();
}

bool SimpleWidgetViewer::setup(const QString& configFilePath) {
    refreshWidgetList();
    return true;
}

void SimpleWidgetViewer::refreshWidgetList() {
    if (!GlobalObjectFactory::instance()) return;

    ui.comboBox->clear();
    auto factory_names = GlobalObjectFactory::instance()->getFactoryNames();
    for (auto& name : factory_names) {
        auto types = GlobalObjectFactory::instance()->getFactorySupportedNames(name);

        for (auto& type : types) {
            auto obj = GlobalObjectFactory::instance()->createObject(name, type);
            auto widget = std::dynamic_pointer_cast<QWidget>(obj);
            if (widget) {
                QStringList data;
                QString text;
                text = QString("%1 - %2").arg(name.c_str()).arg(type.c_str());
                data << name.c_str();
                data << type.c_str();
                ui.comboBox->addItem(text, data);
            }
        }
		//Sail for fast select.
		int index = ui.comboBox->findText("SimpleUiFactory, Ver 1.0 - RobotXyzWidget");
		if (index > 0) {
			ui.comboBox->setCurrentIndex(index);
		}
    }
    BOT_LOG.addFilter(this, [=](const std::string& m) { appendText(m); });
}

void SimpleWidgetViewer::actionCreateWidget() {
    if (!GlobalObjectFactory::instance()) return;
    if (ui.comboBox->count() == 0)
        return;

    QString robotConfig = QFileDialog::getOpenFileName(this,
        tr("Get Widget Config JSON file ..."),
        QString(FileFinder::getPreDefPath().c_str()),
        tr("JSON files (*.JSON *.json)"));

    QStringList obj_info = ui.comboBox->currentData().toStringList();
    QString factory = obj_info.at(0);
    QString typen = obj_info.at(1);

    m_pWidget = GlobalObjectFactory::instance()->createObject(factory, typen);
    auto widget = std::dynamic_pointer_cast<QWidget>(m_pWidget);
    if (widget) {
        widget->installEventFilter(m_closer);
        if (robotConfig.isEmpty()) {
            widget->show();
        } else {
            if (m_pWidget->setup(robotConfig)) {
                widget->show();
            }
        }
    }
}

void SimpleWidgetViewer::resetCurObj() {
    auto widget = std::dynamic_pointer_cast<QWidget>(m_pWidget);
    if (widget) {
        widget->removeEventFilter(m_closer);
    }
    //m_pWidget = nullptr;
}

void SimpleWidgetViewer::updateTextToUI() {
    if (m_cachedMessage.size()) {
        m_textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        m_textCursor.insertText(m_cachedMessage);

        ui.plainTextEdit->setTextCursor(m_textCursor);
        m_cachedMessage.clear();
    }
}

void SimpleWidgetViewer::appendText(const std::string& message) {
    static QRegularExpression reg("^\\[\\s*([-A-Za-z_0-9]*)\\s*\\](.*)");

    QString final_message = QString::fromLocal8Bit(message.c_str());
    m_cachedMessage += final_message;
}

void SimpleWidgetViewer::createTextLogUi() {
    QFont font = getMonospaceFont();
//    ui.plainTextEdit->setReadOnly(true);
//    ui.plainTextEdit->setFont(font);
//    ui.plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
//
//    m_textCursor = ui.plainTextEdit->textCursor();
//
//    cobotsys::gui::LoggerHighlighter::highlightEditorWithDefaultStyle(ui.plainTextEdit->document());
//
//    m_editUpdateTimer = new QTimer(this);
//    m_editUpdateTimer->setInterval(1000 / 30); // 30Hz
//    connect(m_editUpdateTimer, &QTimer::timeout, this, &SimpleWidgetViewer::updateTextToUI);
//    m_editUpdateTimer->start();
}

void SimpleWidgetViewer::actionClear() {
    ui.plainTextEdit->clear();
}

void SimpleWidgetViewer::actionCreateWidgetNoJson() {
    if (!GlobalObjectFactory::instance()) return;
    if (ui.comboBox->count() == 0)
        return;

    QStringList obj_info = ui.comboBox->currentData().toStringList();
    QString factory = obj_info.at(0);
    QString typen = obj_info.at(1);

    m_pWidget = GlobalObjectFactory::instance()->createObject(factory, typen);
    auto widget = std::dynamic_pointer_cast<QWidget>(m_pWidget);
    if (widget) {
        m_pWidget->setup("");
        widget->installEventFilter(m_closer);
        widget->show();
    }
}
