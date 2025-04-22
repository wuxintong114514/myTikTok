#include "graphicsdanmakutextitem.h"

GraphicsDanmakuTextItem::GraphicsDanmakuTextItem()
{   
}

void GraphicsDanmakuTextItem::timerEvent(QTimerEvent *)
{
    if(this->x()>100)
    {
        this->setPos(this->x()-1,this->y());
    }else
    {
        this->setPos(500+qrand()%200,this->y());
    }

}

