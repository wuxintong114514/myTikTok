#include "TikTok.h"
#include "ui_TikTok.h"
#include<QLayout>
#include<QSqlError>
#include<QMutex>
MyTikTok::MyTikTok(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyTikTok)
{
    ui->setupUi(this);
    initUi();
}

MyTikTok::~MyTikTok()
{
    delete ui;
    delete gvXY;
    delete gvWH;
}

void MyTikTok::initUi()
{   
    connect(ui->pbUpload,SIGNAL(clicked()),this,SLOT(uploadVideo()));
    preplayer = new QMediaPlayer(this);
    prescene = new QGraphicsScene(this);
    ui->gvVideoClip->setScene(prescene);
    preVideoItem = new QGraphicsVideoItem();
    preVideoItem->setSize(QSizeF(ui->gvVideoClip->width()-2,ui->gvVideoClip->height()-30));
    preplayer->setVideoOutput(preVideoItem);//视频输出的目标
    prethread = new GraphicsThread();
    connect(prethread,SIGNAL(trigger()),this,SLOT(previewVideo()));
    connect(ui->spSearch,SIGNAL(clicked()),this,SLOT(onSearch()));
    connect(ui->pbDanmaku,SIGNAL(clicked()),this,SLOT(onDanmaku()));
    connect(ui->pbComment,SIGNAL(clicked()),this,SLOT(onComment()));
    connect(ui->pbLike,SIGNAL(clicked()),this,SLOT(onLike()));
    ui->pbFocus->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    connect(ui->pbFocus,SIGNAL(clicked()),this,SLOT(onFocus()));
    usernameTextItem = new QGraphicsTextItem();
    QFont *font = new QFont();
    font->setBold(true);
    font->setPointSize(14);
    font->setFamily("微软雅黑");
    usernameTextItem->setPos(365,10);
    usernameTextItem->setDefaultTextColor(Qt::GlobalColor::white);//文本默认颜色
    descnoteTextItem = new QGraphicsTextItem();//描述文字
    font->setBold(true);
    font->setPointSize(12);
    font->setFamily("微软雅黑");
    descnoteTextItem->setFont(*font);
    descnoteTextItem->setPos(365,20);
    descnoteTextItem->setDefaultTextColor(Qt::GlobalColor::white);
    likecountTextItem =  new QGraphicsTextItem();
    font->setBold(true);
    font->setPointSize(10);
    font->setFamily("微软雅黑");
    likecountTextItem->setFont(*font);
    likecountTextItem->setPos(655,540);
    likecountTextItem->setDefaultTextColor(Qt::GlobalColor::yellow);
    QPixmap pixmap;
    pixmap.load("image/like.png");
    pixmap = pixmap.scaled(28,28,Qt::KeepAspectRatio);//缩放
    likepicItem = new QGraphicsPixmapItem(pixmap);
    likepicItem->setPos(660,560);
    connect(ui->pbFullScreen,SIGNAL(clicked()),this,SLOT(enterFullScreen()));
    ui->gvWatchOnline->installEventFilter(this);//安装事件过滤器
    setWindowIcon(QIcon("image/tiktok.png"));
    setWindowFlag(Qt::WindowType::MSWindowsFixedSizeDialogHint);//设置窗口为固定大小
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::ColorRole::Window,Qt::GlobalColor::white);
    setPalette(*palette);
    ui->lbLogo->setPixmap(QPixmap("image/tubiao.png"));//图像
    ui->spSearch->setIcon(QIcon("image/search.png"));//图标
    ui->spSearch->setIconSize(QSize(23,23));
    ui->spSearch->setStyleSheet("background-color:whitesmoke");
    ui->tabWidget->setTabIcon(0,QIcon("image/tuijian.png"));
    ui->tabWidget->setTabIcon(1,QIcon("image/luzhi.png"));
    ui->tabWidget->setTabIcon(2,QIcon("image/fabu.png"));
    ui->tabWidget->setIconSize(QSize(36,36));
    ui->pbPrev->setIcon(QIcon("image/prev.png"));
    ui->pbPrev->setIconSize(QSize(26,80));
    ui->pbPrev->setStyleSheet("background-color:whitesmoke");
    ui->pbNext->setIcon(QIcon("image/next.png"));
    ui->pbNext->setIconSize(QSize(26,80));
    ui->pbNext->setStyleSheet("background-color:whitesmoke");
    ui->pbFocus->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    ui->pbLike->setIcon(QIcon("image/like.png"));
    ui->pbLike->setIconSize(QSize(55,55));
    ui->pbComment->setIcon(QIcon("image/comment.png"));
    ui->pbComment->setIconSize(QSize(47,47));
    ui->pbDanmaku->setIcon(QIcon("image/ondanmaku.png"));
    ui->pbDanmaku->setIconSize(QSize(81,29));
    ui->pbFullScreen->setIcon(QIcon("image/fullscreen"));
    ui->pbFullScreen->setIconSize(QSize(27,27));
    duration = "00:00";
    position = "00:00";
    player = new QMediaPlayer(this);
    scene = new QGraphicsScene(this);
    ui->gvWatchOnline->setScene(scene);
    videoItem = new QGraphicsVideoItem();
    videoItem->setSize(QSizeF(ui->gvWatchOnline->width()-2,ui->gvWatchOnline->height()-30));
    player->setVideoOutput(videoItem);
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(setDuration(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(setPosition(qint64)));
    connect(ui->pbPrev,SIGNAL(clicked()),this,SLOT(showPrevVideo()));
    connect(ui->pbNext,SIGNAL(clicked()),this,SLOT(showNextVideo()));
    connect(ui->hsPosition,SIGNAL(valueChanged(int)),this,SLOT(setDragValue(int)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    thread = new GraphicsThread();
    connect(thread, &GraphicsThread::trigger, this, &MyTikTok::replaceVideo);
    currentUser = "sgdik";
    openDb();
    connect(ui->pbOpen,SIGNAL(clicked()),this,SLOT(openVideo()));
    ui->pbCurrentUser->setIcon(QIcon(getPhotoByName(currentUser)));
    ui->pbCurrentUser->setIconSize(QSize(61,61));
    loadOnlineVideos();
    loadFocusUsers();
    connect(ui->pbClose,SIGNAL(clicked()),this,SLOT(closeVideo()));
}

void MyTikTok::openDb()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mytiktok");
    db.setUserName("root");
    db.setPassword("114514");
    if(!db.open())
    {
        QMessageBox::critical(0,"false","no connect",QMessageBox::Cancel);
        return;
    }

}

void MyTikTok::loadOnlineVideos()
{
    //countMutex.lock(); // 加锁
    QSqlQuery query;
    query.exec(QString("SELECT Likes FROM user WHERE UserName = '%1'").arg(currentUser));
    if (query.next()) {
        QByteArray jsonData = query.value(0).toByteArray();
        if (!jsonData.isEmpty()) {
            QJsonDocument doc = QJsonDocument::fromJson(jsonData);
            if (!doc.isNull() && doc.isObject()) {
                likesjson = doc.object();
                QStringList keyList = likesjson.keys();
                if (!keyList.isEmpty()) {
                    QString likeCategory = keyList[0];
                    int maxLike = likesjson.take(likeCategory).toVariant().toInt();
                    for(int i = 1; i < keyList.count(); i++) {
                        int like = likesjson.take(keyList[i]).toVariant().toInt();
                        if(like > maxLike) {
                            likeCategory = keyList[i];
                            maxLike = like;
                        }
                    }
                    videoModel = new QSqlQueryModel(this);
                    videoModel->setQuery(QString("SELECT video.Vid,VideoData FROM videoinfo,video WHERE videoinfo.Vid = video.Vid"));
                    count = videoModel->rowCount();
                    qDebug() << "Video count: " << count;
                    index = 0;
                    playByIndex(index);
                } else {
                    qDebug() << "No keys found in likesjson";
                }
            } else {
                qDebug() << "Failed to parse JSON data: " << jsonData;
            }
        } else {
            qDebug() << "JSON data from database is empty";
        }
    } else {
        qDebug() << "No records found for user: " << currentUser;
    }
    //countMutex.unlock(); // 解锁
}

void MyTikTok::playByIndex(int id)
{
    //countMutex.lock(); // 加锁
    if (id >= 0 && id < count) {
        player->stop();
        player->setMedia(QUrl::fromLocalFile(""));
        QSqlRecord record = videoModel->record(id);
        QFile *file = new QFile("video/temp.mp4");
        if(file->exists()) file->remove();
        if(file->open(QIODevice::ReadWrite)) {
            qint64 written = file->write(record.value("VideoData").toByteArray());
            qDebug() << "Written bytes: " << written; // 输出写入的字节数
            file->close();
            qDebug() << "File size: " << file->size(); // 输出文件大小
        }
        foreach(QGraphicsItem *graphItem, scene->items())
            scene->removeItem(graphItem);
        scene->addItem(videoItem);
        thread->start();
        addDescText(record.value("Vid").toInt());
        addFocusIcon(record.value("Vid").toInt());
        addLikeText(record.value("Vid").toInt());
        if(danmakuHide == false) addDanmakuText(record.value("Vid").toInt());
    } else {
        qDebug() << "Index out of range in playByIndex";
    }
    //countMutex.unlock(); // 解锁
}
void MyTikTok::addDescText(int vid)
{
    QSqlQuery query;
    if (query.exec(QString("SELECT DescNote,UserName FROM videoinfo WHERE Vid = %1").arg(vid))) {
        if (query.next()) {
            usernameTextItem->setPlainText("@"+query.value(1).toString());
            descnoteTextItem->setPlainText(query.value(0).toString());
            if (!scene->items().contains(usernameTextItem)) {
                scene->addItem(usernameTextItem);
            }
            if (!scene->items().contains(descnoteTextItem)) {
                scene->addItem(descnoteTextItem);
            }
        } else {
            // 处理查询结果为空的情况
            qDebug() << "No records found in videoinfo for Vid: " << vid;
        }
    } else {
        // 处理查询执行失败的情况
        qDebug() << "Query execution failed: " << query.lastError().text();
    }
}

void MyTikTok::addLikeText(int vid)
{
    QSqlQuery query;
    if (query.exec(QString("SELECT * FROM likes WHERE Vid = %1").arg(vid))) {
        if (query.last()) {
            likecountTextItem->setPlainText(QString::number(985 + query.at() +1));
            query.first();
            query.previous();
            query.exec(QString("SELECT * FROM likes WHERE Vid = %1 AND UserName = '%2'").arg(vid).arg(currentUser));
            if(query.size() == 1)
            {
                ui->pbLike->setIcon(QIcon("image/onlike.png"));
                ui->pbLike->setToolTip("取消赞");
            }else
            {
                ui->pbLike->setIcon(QIcon("image/offlike.png"));
                ui->pbLike->setToolTip("点赞");
            }
            if (!scene->items().contains(likepicItem)) {
                scene->addItem(likepicItem);
            }
            if (!scene->items().contains(likecountTextItem)) {
                scene->addItem(likecountTextItem);
            }
        } else {
            // 处理查询结果为空的情况
            qDebug() << "No records found in likes for Vid: " << vid;
        }
    } else {
        // 处理查询执行失败的情况
        qDebug() << "Query execution failed: " << query.lastError().text();
    }
}

void MyTikTok::loadFocusUsers()
{
    QSqlQuery query;
    query.exec(QString("SELECT Focus FROM user WHERE UserName = '%1'").arg(currentUser));
    query.next();
    ui->tbwFocusUsers->clear();
    ui->tbwFocusUsers->setColumnCount(1);
    ui->tbwFocusUsers ->setHorizontalHeaderLabels(QStringList("关注"));
    ui->tbwFocusUsers->setColumnWidth(0,ui ->tbwFocusUsers->width());
    ui->tbwFocusUsers->setIconSize(QSize(25,25));
    focusList = query.value(0).toString().split(",");
    if(focusList.count() == 0) return;
    ui->tbwFocusUsers->setRowCount(focusList.count());
    for(int i=0;i<focusList.count();i++)
    {
        QTableWidgetItem *userItem = new QTableWidgetItem(QIcon(getPhotoByName(focusList[i])),focusList[i]);
        ui->tbwFocusUsers->setItem(i,0,userItem);
    }

}

QPixmap MyTikTok::getPhotoByName(QString username)
{
    QSqlQuery query;
    query.exec(QString("SELECT Photo FROM user WHERE UserName = '%1'").arg(username));
    query.next();
    QPixmap photo;
    photo.loadFromData(query.value(0).toByteArray(),"png");
    return photo;
}

QString MyTikTok::getNameById(int vid)
{
    QSqlQuery query;
    query.exec(QString("SELECT UserName FROM videoinfo WHERE Vid = %1").arg(vid));
    query.next();
    return query.value(0).toString();
}

void MyTikTok::addFocusIcon(int vid)
{
    QString username = getNameById(vid);
    ui->pbFocus->setIcon(QIcon(QPixmap(getPhotoByName(username))));
    if(focusList.contains(username))
    {
        ui->pbFocus->setText("");
        ui->pbFocus->setIconSize(QSize(49,49));
        ui->pbFocus->setToolTip("取消关注");
    }else
    {
        ui->pbFocus->setText("+");
        ui->pbFocus->setIconSize(QSize(31,31));
        ui->pbFocus->setToolTip("加关注");
    }

}

void MyTikTok::addDanmakuText(int vid)
{
    QSqlQuery query;
    query.exec(QString("SELECT Comment FROM evaluate WHERE Vid = %1").arg(vid));
    query.next();
    if(query.size() == 0)return;
    QFont *font = new QFont();
    font->setBold(true);
    font->setPointSize(12);
    font->setFamily("微软雅黑");
    for(int n = 0;n<query.size();n++)
    {
        GraphicsDanmakuTextItem *danmakuTextItem = new GraphicsDanmakuTextItem();
        danmakuTextItem->setPlainText(query.value(0).toString());
        danmakuTextItem->setFont(*font);
        danmakuTextItem->setPos(500 + qrand()%200,40+30*n);
        danmakuTextItem->setDefaultTextColor(Qt::GlobalColor::white);
        danmakuTextItem->startTimer(10);
        scene->addItem(danmakuTextItem);
        query.next();
    }

}

void MyTikTok::setDuration(qint64 dur)
{
    ui->hsPosition->setMaximum(dur);
    int dursecs = dur/1000;
    int mins = dursecs/60;
    int secs = dursecs%60;
    duration = QString("%1:%2").arg(mins,2,10,QChar('0')).arg(secs,2,10,QChar('0'));
    ui->lbDuration->setText(position+"/"+duration);
}

void MyTikTok::setPosition(qint64 pos)
{
    int possecs = pos/1000;
    int mins = possecs/60;
    int secs = possecs%60;
    position = QString("%1:%2").arg(mins,2,10,QChar('0')).arg(secs,2,10,QChar('0'));
    ui->lbDuration->setText(position+"/"+duration);
    ui->hsPosition->setSliderPosition(pos);
}

void MyTikTok::setDragValue(int value)
{
    player->setPosition(value);
}

void MyTikTok::showPrevVideo()
{
    if (index > 0) {
        index--;
        playByIndex(index);
    }
}

void MyTikTok::showNextVideo()
{
    if (index < count - 1) {
        index++;
        playByIndex(index);
    }
}

void MyTikTok::replaceVideo()
{
    QFile file("video/temp.mp4");
    if (file.exists()) {
        player->setMedia(QUrl::fromLocalFile("video/temp.mp4"));
        player->play();
        if (player->error() != QMediaPlayer::NoError) {
            qDebug() << "Media player error: " << player->errorString();
            QMessageBox::critical(0, "Error", "Video playback error: " + player->errorString(), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(0, "Error", "Video file not found", QMessageBox::Cancel);
    }
}

bool MyTikTok::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == QEvent::Type::MouseButtonPress)
    {
        QMouseEvent *event = static_cast<QMouseEvent *>(e);
        if(event->button() == Qt::LeftButton)
        {
            if(player->state() == QMediaPlayer::PlayingState)
            {
                player->pause();
            }
            else
            {
                player->play();
            }
        }
    }
    if(e->type() == QEvent::Type::Wheel)
    {
        QWheelEvent *event = static_cast<QWheelEvent *>(e);
        if(event->angleDelta().y() < 0)
        {
            showNextVideo();
        }
        else
        {
            showPrevVideo();
        }
    }
    if(e->type() == QEvent::Type::KeyPress)
        {
            QKeyEvent *event = static_cast<QKeyEvent *>(e);
            if(event->key() == Qt::Key::Key_Escape)
            {
                if(ui->gvWatchOnline->isFullScreen())
                {
                    // 暂停视频播放
                    player->pause();

                    // 恢复窗口标志
                    ui->gvWatchOnline->setWindowFlag(Qt::Window, false);
                    ui->gvWatchOnline->setWindowFlag(Qt::SubWindow, true);

                    // 设置视图的位置和大小
                    ui->gvWatchOnline->setGeometry(QRect(gvXY->x(), gvXY->y(), gvWH->x(), gvWH->y()));

                    // 将视图添加到父布局中
                    ui->gvWatchOnline->setParent(ui->widget);

                    // 确保布局更新
                    if (ui->widget->layout()) {
                        ui->widget->layout()->update();
                    }

                    // 显示视图
                    ui->gvWatchOnline->showNormal();

                    // 确保布局完整更新
                    ui->widget->update();

                    // 恢复视频播放
                    player->play();
                }
            }
        }
    return QWidget::eventFilter(o, e);
}

void MyTikTok::enterFullScreen()
{
    gvXY = new QPoint(ui->gvWatchOnline->x(),ui->gvWatchOnline->y());
    gvWH = new QPoint(ui->gvWatchOnline->width(),ui->gvWatchOnline->height());
    ui->gvWatchOnline->setWindowFlag(Qt::WindowType::Window);
    ui->gvWatchOnline->showFullScreen();
}

void MyTikTok::onFocus()
{
    QString username = getNameById(videoModel->record(index).value("Vid").toInt());
    if(!focusList.contains(username))
    {
        focusList.append(username);
    }else
       {
        focusList.removeOne(username);
    }
    QSqlQuery query;
    query.prepare("UPDATE user SET Focus = ? WHERE UserName = ?");
    query.bindValue(0,focusList.join(","));
    query.bindValue(1,currentUser);
    query.exec();
    loadFocusUsers();
    addFocusIcon(videoModel->record(index).value("Vid").toInt());
}

void MyTikTok::onLike()
{
    qDebug() << "onLike function called";
    int vid = videoModel->record(index).value("Vid").toInt();
    QSqlQuery query;
    query.exec(QString("SELECT Category FROM videoinfo WHERE Vid = %1").arg(videoModel->record(index).value("Vid").toInt()));
    query.next();
    QStringList cateList = query.value(0).toString().split(",");
    db.transaction(); // 开始事务
    query.exec(QString("SELECT * FROM likes WHERE Vid = %1 AND UserName = '%2'").arg(vid).arg(currentUser));
    if(query.size() == 1)
    {
        // 用户已经点赞，取消点赞
        if(!query.exec(QString("DELETE FROM likes WHERE Vid = %1 AND UserName = '%2'").arg(vid).arg(currentUser)))
        {
            qDebug() << "Delete like record failed: " << query.lastError().text();
            db.rollback(); // 回滚事务
            return;
        }
        qDebug() << "Like record deleted successfully";
        ui->pbLike->setIcon(QIcon("image/offlike.png"));
        ui->pbLike->setToolTip("点赞");
        for(int i = 0;i<cateList.count();i++)
        {
            if(cateList[i]=="music")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"music\"',JSON_EXTRACT(Likes,'$.\"music\"')-1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }else if(cateList[i] == "dance")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"dance\"',JSON_EXTRACT(Likes,'$.\"dance\"')-1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }else if(cateList[i] == "comedy")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"comedy\"',JSON_EXTRACT(Likes,'$.\"comedy\"')-1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }
        }
    }
    else
    {
        // 用户未点赞，添加点赞记录
        if(!query.exec(QString("INSERT INTO likes (Vid, UserName) VALUES (%1, '%2')").arg(vid).arg(currentUser)))
        {
            qDebug() << "Insert like record failed: " << query.lastError().text();
            db.rollback(); // 回滚事务
            return;
        }
        qDebug() << "Like record inserted successfully";
        ui->pbLike->setIcon(QIcon("image/onlike.png"));
        ui->pbLike->setToolTip("取消赞");
        for(int i=0;i<cateList.count();i++)
        {
            if(cateList[i]=="music")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"music\"',JSON_EXTRACT(Likes,'$.\"music\"')+1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }else if(cateList[i]=="dance")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"dance\"',JSON_EXTRACT(Likes,'$.\"dance\"')+1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }else if(cateList[i]=="comedy")
            {
                query.prepare("UPDATE user SET Likes = JSON_SET(Likes,'$.\"comedy\"',JSON_EXTRACT(Likes,'$.\"comedy\"')+1)WHERE UserName = ?");
                query.bindValue(0,currentUser);
                query.exec();
            }
        }
    }
    db.commit(); // 提交事务
    addLikeText(vid); // 更新点赞数显示
}

void MyTikTok::onComment()
{
    CommentDialog *commentDialog = new CommentDialog();
    if(commentDialog->exec())//以模态方式显示 commentDialog 对话框。模态对话框会阻塞程序的执行，直到对话框关闭。exec() 函数会返回一个布尔值，若用户点击 “确定” 按钮，返回 true；若点击 “取消” 按钮，返回 false。只有当用户点击 “确定” 时，才会执行 if 语句块内的代码。
    {
        QSqlQuery query;
        query.prepare("INSERT INTO evaluate(Vid,UserName,Comment) VALUES(?,?,?)");
        query.bindValue(0,videoModel->record(index).value("Vid").toInt());
        query.bindValue(1,currentUser);
        query.bindValue(2,commentDialog->leComment->text());
        query.exec();
        if((danmakuHide == false)&&(commentDialog->leComment->text()!=""));
        {
            playByIndex(index);
        }
    }
    commentDialog->destroyed();
}

void MyTikTok::onDanmaku()
{
    if(danmakuHide == false)
    {
        ui->pbDanmaku->setIcon(QIcon("image/offdanmaku.png"));
        danmakuHide = true;
    }else
    {
        ui->pbDanmaku->setIcon(QIcon("image/ondanmaku.png"));
        danmakuHide = false;
    }
    playByIndex(index);
}

void MyTikTok::onSearch()
{
    QString keyword = ui->leInterestKey->text();

    // 执行搜索查询，使用预处理语句避免 SQL 注入
    QSqlQuery query;
    query.prepare("SELECT video.Vid,VideoData FROM videoinfo,video WHERE videoinfo.Vid = video.Vid AND videoinfo.Category LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");
    if (query.exec()) {
        videoModel->setQuery(query);
        // 更新视频总数
        count = videoModel->rowCount();
        qDebug() << "Search result count: " << count;
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
        QMessageBox::critical(this, "错误", "查询数据库时出错: " + query.lastError().text());
        return;
    }

    if (count > 0) {
        // 重置索引值
        index = 0;
        if (index >= 0 && index < count) {
            playByIndex(index);
        } else {
            qDebug() << "Index out of range in onSearch";
            QMessageBox::critical(this, "错误", "索引超出范围，请重试。");
        }
    } else {
        qDebug() << "No search results found.";
        // 可以在这里添加一些提示用户的逻辑，例如弹出消息框
        QMessageBox::information(this, "提示", "未找到相关搜索结果。");
    }
}
void MyTikTok::previewVideo()
{
    preplayer->setMedia(QUrl::fromLocalFile(prefilename));
    preplayer->play();
    player->stop();
}

void MyTikTok::openVideo()
{
    prefilename = QFileDialog::getOpenFileName(this,"选择视频","C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Uploads");
    if(prefilename!="")
    {
        closeVideo();
        prescene->addItem(preVideoItem);
        ui->pbUpload->setEnabled(true);
        prethread->start();
    }

}

void MyTikTok::closeVideo()
{
    preplayer->stop();
    preplayer->setMedia(QUrl::fromLocalFile(""));//设置播放的媒体源
    foreach(QGraphicsItem *graphItem,prescene->items())
        prescene->removeItem(graphItem);
    ui->pbUpload->setEnabled(false);
}

void MyTikTok::uploadVideo()
{
    UpLoadDialog *uploadDialog = new UpLoadDialog();
    if(uploadDialog->exec())
    {
        QSqlQuery query;
        query.exec(QString("SELECT MAX(Vid) FROM videoinfo"));
        query.next();
        int vid = query.value(0).toInt()+1;
        QString category = "";
        QObjectList list = uploadDialog->gbCate->children();
        for(int i=0;i<list.count();i++)
        {
            QCheckBox *cb = static_cast<QCheckBox *>(list[i]);
            if(cb->isChecked())category += cb->text()+",";
        }
        category.chop(1);
        QString describe = uploadDialog->teDescribe->toPlainText();
        int permit = 1;
        if(ui->cbPublic->isChecked() == false)permit = 0;
        QString ptime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // 将 prefilename 转换为绝对路径
        QFileInfo fileInfo(prefilename);
        QString absolutePath = fileInfo.absoluteFilePath();

        // 插入视频文件
        query.prepare("INSERT INTO video VALUES(?,LOAD_FILE(?))");
        query.bindValue(0,vid);
        query.bindValue(1,absolutePath);
        if (!query.exec()) {
            qDebug() << "Failed to insert video file:" << query.lastError().text();
            QMessageBox::critical(this, "错误", "视频文件插入失败");
            delete uploadDialog;
            return;
        }

        // 插入视频信息
        query.prepare("INSERT INTO videoinfo VALUES (?,?,?,?,?,0,?)");
        query.bindValue(0,vid);
        query.bindValue(1,category);
        query.bindValue(2,describe);
        query.bindValue(3,currentUser);
        query.bindValue(4,permit);
        query.bindValue(5,ptime);
        if (!query.exec()) {
            qDebug() << "Failed to insert video info:" << query.lastError().text();
            QMessageBox::critical(this, "错误", "视频信息插入失败");
            delete uploadDialog;
            return;
        }

        QMessageBox::information(this,"完毕","发布成功");
    }
    delete uploadDialog;
}


void MyTikTok::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
           player->play(); // 视频播放结束，重新播放
       }
}

