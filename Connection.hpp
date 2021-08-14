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
#include <QJsonObject>
#include <QJsonDocument>

typedef QNetworkReply* Reply;
typedef configor::json Json;

class Connection : public QObject {
Q_OBJECT
public:
    Connection(QString addr, QString token) {
        url = QString("http://") + addr;
        manager = new QNetworkAccessManager(this);
    };

    Json sendFriendMessage(long target, Json MessageChain){
        Json info = {
                {"target", target},
                {"messageChain", MessageChain}
        };
        return getReply("/sendFriendMessage", info);
    };

    Json recall(int target){
        Json info = {
                {"target", target}
        };
        return getReply("/recall", info);
    };

    Json getFriendList() {
        return getReply("/friendList");
    };

    Json getGroupList() {
        return getReply("/groupList");
    };

    Json getMemberList(long target) {
        return getReply(("/memberList?target=" + std::to_string(target)).data());
    };

    Json getMyProfile() {
        return getReply("/botProfile");
    };

    Json getFriendProfile(long target){
        return getReply(("/friendProfile?target=" + std::to_string(target)).data());
    };

private:
    QString sessionKey, url;
    long long id;
    QNetworkAccessManager *manager;
    
    void async(Reply reply) {
        while (!reply->isFinished())
            QApplication::processEvents();
    };
    
    Json getReply(QString route, Json obj) {
        Reply reply = manager->post(getRequest(route), QByteArray::fromStdString(obj.dump()));
        async(reply);
        return configor::json::parse(reply->readAll().toStdString());
    };
    
    Json getReply(QString route) {
        Reply reply = manager->get(getRequest(route));
        async(reply);
        return configor::json::parse(reply->readAll().toStdString());
    };
    
    QNetworkRequest getRequest(QString route) {
        QNetworkRequest request;
        request.setUrl(url + route);
        request.setRawHeader("Content-Type", "application/json");
        return request;
    };
};

#endif //REDIM_CONNECTION_HPP