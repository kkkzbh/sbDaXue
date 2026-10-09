

#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Hello World";
    QCoreApplication::quit();
    return 0;
}