#ifndef BOTSYS_H
#define BOTSYS_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <functional>
#include <memory>
#include <ostream>

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QImage>
#include <QFont>
#include <QFontInfo>
#include <QDebug>

#include <opencv2/opencv.hpp>

using std::make_shared;

void init_library(int argc, char** argv);

std::ostream& operator<<(std::ostream& oss, const QString& str);
std::ostream& operator<<(std::ostream& oss, const QJsonObject& obj);
QFont getMonospaceFont();

template<class T>
const T& smaller(const T& a, const T& b) {
    if (a < b)
        return a;
    return b;
}

#endif //PROJECT_COBOTSYS_H
