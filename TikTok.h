#ifndef MYTIKTOK_H
#define MYTIKTOK_H

#include <QWidget>
#include<QMediaPlayer>
#include<QGraphicsScene>
#include<QGraphicsVideoItem>//用于显示视频
#include"graphicsthread.h"
#include<QUrl>//对URL进行解析与构建
#include<QSqlDatabase>//建立数据库连接
#include<QSqlTableModel>//对数据库单个表进行操作
#include<QSqlRecord>//访问与操作数据库字段
#include<QMessageBox>
#include<QFile>
#include<QIODevice>//读写数据
#include<QByteArray>
#include<QEvent>
#include<QMouseEvent>
#include<QSqlQuery>//执行sql语句并处理查询结果
#include"commentdialog.h"
#include"graphicsdanmakutextitem.h"
#include<QJsonObject>//操作json对象
#include<QJsonDocument>//将json数据与文本进行转换
#include<QFileDialog>
#include"uploaddialog.h"
#include<QDateTime>
#include<QMutex>
#include<QDateTime>





QT_BEGIN_NAMESPACE
namespace Ui { class MyTikTok; }
QT_END_NAMESPACE

class MyTikTok : public QWidget
{
    Q_OBJECT

public:
    MyTikTok(QWidget *parent = nullptr);
    ~MyTikTok();
    void initUi();
    void openDb();
    int count;//视频总数
    int index;//当前视频播放索引
    void loadOnlineVideos();
    void playByIndex(int);
    void addDescText(int);
    void addLikeText(int);
    QString currentUser;//当前用户
    QStringList focusList;//当前用户关注的用户列表
    QJsonObject likesjson;//当前用户喜好记录（json类型）
    void loadFocusUsers();
    QPixmap getPhotoByName(QString);
    QString getNameById(int);
    void addFocusIcon(int);
    bool danmakuHide = false;//默认开启弹幕
    void addDanmakuText(int);
    QString prefilename;
private slots:
    void setDuration(qint64);//持续时间
    void setPosition(qint64);
    void setDragValue(int);
    void showPrevVideo();
    void showNextVideo();
    void replaceVideo();
    bool eventFilter(QObject *,QEvent *);
    void enterFullScreen();
    void onFocus();
    void onLike();
    void onComment();
    void onDanmaku();
    void onSearch();
    void previewVideo();
    void openVideo();
    void closeVideo();
    void uploadVideo();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
private:
    Ui::MyTikTok *ui;
    QSqlDatabase db;
    QSqlQueryModel *videoModel;//用指针避免在栈上分配过多内存
    QString duration;//也可以使用指针但是要注意内存释放问题
    QString position;
    QMediaPlayer *player;
    QGraphicsScene *scene;
    QGraphicsVideoItem *videoItem;
    GraphicsThread *thread;
    QPoint *gvXY;
    QPoint *gvWH;
    QGraphicsTextItem *usernameTextItem;
    QGraphicsTextItem *descnoteTextItem;
    QGraphicsTextItem *likecountTextItem;
    QGraphicsPixmapItem *likepicItem;
    QPushButton *pbCurrentUser;
    QMediaPlayer *preplayer;
    QGraphicsScene *prescene;
    QGraphicsVideoItem *preVideoItem;
    GraphicsThread *prethread;
    QMutex countMutex; // 互斥锁
};
#endif // MYTIKTOK_H
