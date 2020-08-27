//
// Created by liyanan on 6/11/19.
//

#ifndef HELLOQT_HELLOWIDGET_H
#define HELLOQT_HELLOWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class HelloWidget : public QWidget
{
Q_OBJECT

public:
    explicit HelloWidget(QWidget *parent = 0);
    ~HelloWidget();
    //label
    QLabel *m_labelInfo;
};


#endif //HELLOQT_HELLOWIDGET_H
