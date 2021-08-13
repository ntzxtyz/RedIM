//
// Created by yizhou on 2021/8/13.
//

#ifndef REDIM_CONNECTION_HPP
#define REDIM_CONNECTION_HPP
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <configor/json.hpp>

class Connection : public QObject {
    Q_OBJECT
public:
    Connection(QString addr){
        url = QString("http://") + addr;
        manager = new QNetworkAccessManager(this);
    }

    int verify(QString token){

        QNetworkRequest request = getRequest("/verify");

        configor::json Json;
        Json["verifyKey"] = token.toStdString();

        QNetworkReply *reply = manager->post(request, QByteArray::fromStdString(Json.dump()));
        while (!reply->isFinished())    QApplication::processEvents();

        configor::json ret = configor::json::parse(reply->readAll().toStdString().data());
        qDebug() << ret.dump(8, ' ').data();

        sessionKey = ret["session"];
        int code = (int)ret["code"];

        delete &ret;
        delete &Json;
        delete &request;
        reply->deleteLater();
        return code;
    }

private:
    QString sessionKey, url;
    QNetworkAccessManager *manager;
    QNetworkRequest getRequest(QString route){
        QNetworkRequest request;
        request.setUrl(url + route);
        request.setRawHeader("Content-Type", "application/json");
        return request;
    }
};


#endif //REDIM_CONNECTION_HPP
