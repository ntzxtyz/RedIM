//
// Created by yizhou on 2021/8/13.
//

#ifndef REDIM_CONNECTION_HPP
#define REDIM_CONNECTION_HPP

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QApplication>
#include <QObject>
#include <configor/json.hpp>

class Connection : public QObject {
Q_OBJECT
public:
    Connection(QString addr) {
        url = QString("http://") + addr;
        manager = new QNetworkAccessManager(this);
    }

    bool verify(QString token) {
        QNetworkRequest request = getRequest("/verify");
        configor::json Json;
        Json["verifyKey"] = token.toStdString();
        QNetworkReply *reply = manager->post(request, QByteArray::fromStdString(Json.dump()));
        while (!reply->isFinished()) QApplication::processEvents();
        configor::json answer = configor::json::parse(reply->readAll().toStdString());
        if (static_cast<int>(answer["code"]) == 0) {
            sessionKey = answer["session"];
            return true;
        } else return false;
    }

    bool bind(QString qq) {
        id = qq;
        QNetworkRequest request = getRequest("/bind");
        configor::json Json;
        Json["sessionKey"] = sessionKey.toStdString();
        Json["qq"] = qq.toStdString();
        QNetworkReply *reply = manager->post(request, QByteArray::fromStdString(Json.dump()));
        while (!reply->isFinished())    QApplication::processEvents();
        configor::json answer = configor::json::parse(reply->readAll().toStdString());
        if (static_cast<int>(answer["code"]) == 0)
            return true;
        else return false;
    }

    bool release(){
        QNetworkRequest request = getRequest("/release");
        configor::json Json;
        Json["sessionKey"] = sessionKey.toStdString();
        Json["qq"] = id.toStdString();
        QNetworkReply *reply = manager->post(request, QByteArray::fromStdString(Json.dump()));
        while (!reply->isFinished())    QApplication::processEvents();
        configor::json answer = configor::json::parse(reply->readAll().toStdString());
        if (static_cast<int>(answer["code"]) == 0)
            return true;
        else return false;
    }

private:
    QString sessionKey, url, id;
    QNetworkAccessManager *manager;
    QNetworkRequest getRequest(QString route) {
        QNetworkRequest request;
        request.setUrl(url + route);
        request.setRawHeader("Content-Type", "application/json");
        return request;
    }
};

#endif //REDIM_CONNECTION_HPP
