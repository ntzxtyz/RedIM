#include "Connection.hpp"
#include <QString>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection *c = new Connection("139.198.169.248:5678");
    c->verify("huangrui20041012");
    return a.exec();
}
