#include "Connection.hpp"
#include <QString>
#include <QApplication>
#include <configor/json.hpp>
#include <fstream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection *c = new Connection("139.198.169.248:5678", "huangrui20041012");
    qDebug() << c->getFriendProfile(1508538331).dump(8, ' ').data();
    return a.exec();
}
