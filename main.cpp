#include "TikTok.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTikTok w;
    w.show();
    return a.exec();
}
