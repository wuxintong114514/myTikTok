#include "graphicsthread.h"
#include <QDebug>

GraphicsThread::GraphicsThread()
{
    qDebug() << "GraphicsThread created";
}

void GraphicsThread::run()
{
    qDebug() << "Thread about to start";
    emit trigger();
    qDebug() << "Thread started";
}
