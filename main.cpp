#include "Connection.hpp"
#include <QString>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection *c = new Connection("127.0.0.1:7890");
    c->verify("qwerty");
    return a.exec();
}
