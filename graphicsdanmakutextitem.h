#ifndef GRAPHICSDANMAKUTEXTITEM_H
#define GRAPHICSDANMAKUTEXTITEM_H
#include<QGraphicsTextItem>


class GraphicsDanmakuTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    GraphicsDanmakuTextItem();
    void timerEvent(QTimerEvent *);
};
#endif // GRAPHICSDANMAKUTEXTITEM_H
