/********************************************************************************
** Form generated from reading UI file 'TikTok.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIKTOK_H
#define UI_TIKTOK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyTikTok
{
public:
    QLabel *lbLogo;
    QLineEdit *leInterestKey;
    QPushButton *spSearch;
    QPushButton *pbCurrentUser;
    QTabWidget *tabWidget;
    QWidget *widget;
    QGraphicsView *gvWatchOnline;
    QTableWidget *tbwFocusUsers;
    QPushButton *pbPrev;
    QPushButton *pbNext;
    QPushButton *pbFocus;
    QPushButton *pbLike;
    QPushButton *pbComment;
    QLabel *lbDuration;
    QSlider *hsPosition;
    QPushButton *pbDanmaku;
    QPushButton *pbFullScreen;
    QWidget *tab_2;
    QGraphicsView *gvVideoClip;
    QPushButton *pbOpen;
    QPushButton *pbClose;
    QPushButton *pbEdit;
    QPushButton *pbProc;
    QProgressBar *pgbUpload;
    QCheckBox *cbPublic;
    QPushButton *pbUpload;
    QWidget *tab;

    void setupUi(QWidget *MyTikTok)
    {
        if (MyTikTok->objectName().isEmpty())
            MyTikTok->setObjectName(QString::fromUtf8("MyTikTok"));
        MyTikTok->resize(1200, 800);
        lbLogo = new QLabel(MyTikTok);
        lbLogo->setObjectName(QString::fromUtf8("lbLogo"));
        lbLogo->setGeometry(QRect(50, 10, 201, 81));
        lbLogo->setScaledContents(true);
        leInterestKey = new QLineEdit(MyTikTok);
        leInterestKey->setObjectName(QString::fromUtf8("leInterestKey"));
        leInterestKey->setGeometry(QRect(260, 50, 551, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(14);
        leInterestKey->setFont(font);
        spSearch = new QPushButton(MyTikTok);
        spSearch->setObjectName(QString::fromUtf8("spSearch"));
        spSearch->setGeometry(QRect(810, 50, 111, 41));
        spSearch->setFont(font);
        pbCurrentUser = new QPushButton(MyTikTok);
        pbCurrentUser->setObjectName(QString::fromUtf8("pbCurrentUser"));
        pbCurrentUser->setGeometry(QRect(1070, 30, 61, 61));
        pbCurrentUser->setFlat(true);
        tabWidget = new QTabWidget(MyTikTok);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(50, 110, 1121, 671));
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::West);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gvWatchOnline = new QGraphicsView(widget);
        gvWatchOnline->setObjectName(QString::fromUtf8("gvWatchOnline"));
        gvWatchOnline->setGeometry(QRect(5, 5, 1061, 626));
        tbwFocusUsers = new QTableWidget(widget);
        tbwFocusUsers->setObjectName(QString::fromUtf8("tbwFocusUsers"));
        tbwFocusUsers->setGeometry(QRect(935, 5, 131, 251));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(12);
        tbwFocusUsers->setFont(font1);
        tbwFocusUsers->setAlternatingRowColors(true);
        tbwFocusUsers->setSelectionMode(QAbstractItemView::SingleSelection);
        tbwFocusUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbwFocusUsers->verticalHeader()->setVisible(false);
        pbPrev = new QPushButton(widget);
        pbPrev->setObjectName(QString::fromUtf8("pbPrev"));
        pbPrev->setGeometry(QRect(50, 460, 31, 81));
        pbPrev->setFlat(true);
        pbNext = new QPushButton(widget);
        pbNext->setObjectName(QString::fromUtf8("pbNext"));
        pbNext->setGeometry(QRect(50, 540, 31, 81));
        pbNext->setFlat(true);
        pbFocus = new QPushButton(widget);
        pbFocus->setObjectName(QString::fromUtf8("pbFocus"));
        pbFocus->setGeometry(QRect(935, 370, 51, 51));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        pbFocus->setFont(font2);
        pbFocus->setFlat(true);
        pbLike = new QPushButton(widget);
        pbLike->setObjectName(QString::fromUtf8("pbLike"));
        pbLike->setGeometry(QRect(935, 450, 51, 51));
        QFont font3;
        font3.setPointSize(14);
        pbLike->setFont(font3);
        pbLike->setFlat(true);
        pbComment = new QPushButton(widget);
        pbComment->setObjectName(QString::fromUtf8("pbComment"));
        pbComment->setGeometry(QRect(935, 510, 51, 51));
        pbComment->setFont(font3);
        pbComment->setFlat(true);
        lbDuration = new QLabel(widget);
        lbDuration->setObjectName(QString::fromUtf8("lbDuration"));
        lbDuration->setGeometry(QRect(5, 635, 121, 30));
        QFont font4;
        font4.setPointSize(12);
        lbDuration->setFont(font4);
        lbDuration->setScaledContents(true);
        hsPosition = new QSlider(widget);
        hsPosition->setObjectName(QString::fromUtf8("hsPosition"));
        hsPosition->setGeometry(QRect(115, 639, 811, 22));
        hsPosition->setOrientation(Qt::Horizontal);
        pbDanmaku = new QPushButton(widget);
        pbDanmaku->setObjectName(QString::fromUtf8("pbDanmaku"));
        pbDanmaku->setGeometry(QRect(940, 634, 55, 31));
        pbDanmaku->setFont(font3);
        pbDanmaku->setFlat(true);
        pbFullScreen = new QPushButton(widget);
        pbFullScreen->setObjectName(QString::fromUtf8("pbFullScreen"));
        pbFullScreen->setGeometry(QRect(1035, 634, 31, 31));
        pbFullScreen->setFont(font3);
        pbFullScreen->setFlat(true);
        tabWidget->addTab(widget, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gvVideoClip = new QGraphicsView(tab_2);
        gvVideoClip->setObjectName(QString::fromUtf8("gvVideoClip"));
        gvVideoClip->setGeometry(QRect(5, 5, 941, 611));
        pbOpen = new QPushButton(tab_2);
        pbOpen->setObjectName(QString::fromUtf8("pbOpen"));
        pbOpen->setGeometry(QRect(955, 5, 111, 41));
        pbClose = new QPushButton(tab_2);
        pbClose->setObjectName(QString::fromUtf8("pbClose"));
        pbClose->setGeometry(QRect(955, 50, 111, 41));
        pbEdit = new QPushButton(tab_2);
        pbEdit->setObjectName(QString::fromUtf8("pbEdit"));
        pbEdit->setGeometry(QRect(955, 170, 111, 41));
        pbProc = new QPushButton(tab_2);
        pbProc->setObjectName(QString::fromUtf8("pbProc"));
        pbProc->setGeometry(QRect(955, 215, 111, 41));
        pgbUpload = new QProgressBar(tab_2);
        pgbUpload->setObjectName(QString::fromUtf8("pgbUpload"));
        pgbUpload->setGeometry(QRect(5, 625, 941, 23));
        pgbUpload->setValue(0);
        pgbUpload->setTextVisible(false);
        cbPublic = new QCheckBox(tab_2);
        cbPublic->setObjectName(QString::fromUtf8("cbPublic"));
        cbPublic->setGeometry(QRect(955, 589, 80, 20));
        cbPublic->setFont(font4);
        cbPublic->setChecked(true);
        pbUpload = new QPushButton(tab_2);
        pbUpload->setObjectName(QString::fromUtf8("pbUpload"));
        pbUpload->setEnabled(false);
        pbUpload->setGeometry(QRect(955, 616, 111, 41));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setEnabled(true);
        tabWidget->addTab(tab, QString());

        retranslateUi(MyTikTok);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MyTikTok);
    } // setupUi

    void retranslateUi(QWidget *MyTikTok)
    {
        MyTikTok->setWindowTitle(QCoreApplication::translate("MyTikTok", "\346\212\226\351\237\263-\350\256\260\345\275\225\347\276\216\345\245\275\347\224\237\346\264\273", nullptr));
        lbLogo->setText(QString());
        leInterestKey->setText(QString());
        leInterestKey->setPlaceholderText(QCoreApplication::translate("MyTikTok", "\350\276\223\345\205\245\346\202\250\346\204\237\345\205\264\350\266\243\347\232\204\345\206\205\345\256\271", nullptr));
        spSearch->setText(QCoreApplication::translate("MyTikTok", "\346\220\234\347\264\242", nullptr));
        pbCurrentUser->setText(QString());
        pbPrev->setText(QString());
        pbNext->setText(QString());
        pbFocus->setText(QString());
#if QT_CONFIG(tooltip)
        pbLike->setToolTip(QCoreApplication::translate("MyTikTok", "\347\202\271\350\265\236", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLike->setText(QString());
#if QT_CONFIG(tooltip)
        pbComment->setToolTip(QCoreApplication::translate("MyTikTok", "\350\257\204\350\256\272", nullptr));
#endif // QT_CONFIG(tooltip)
        pbComment->setText(QString());
        lbDuration->setText(QCoreApplication::translate("MyTikTok", "00:00/00:00", nullptr));
#if QT_CONFIG(tooltip)
        pbDanmaku->setToolTip(QCoreApplication::translate("MyTikTok", "\345\274\271\345\271\225", nullptr));
#endif // QT_CONFIG(tooltip)
        pbDanmaku->setText(QString());
#if QT_CONFIG(tooltip)
        pbFullScreen->setToolTip(QCoreApplication::translate("MyTikTok", "\345\205\250\345\261\217", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFullScreen->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(widget), QString());
        pbOpen->setText(QCoreApplication::translate("MyTikTok", "\346\211\223\345\274\200", nullptr));
        pbClose->setText(QCoreApplication::translate("MyTikTok", "\345\205\263\351\227\255", nullptr));
        pbEdit->setText(QCoreApplication::translate("MyTikTok", "\347\274\226\350\276\221", nullptr));
        pbProc->setText(QCoreApplication::translate("MyTikTok", "\345\244\204\347\220\206", nullptr));
        cbPublic->setText(QCoreApplication::translate("MyTikTok", "\345\205\254\345\274\200", nullptr));
        pbUpload->setText(QCoreApplication::translate("MyTikTok", "\344\270\212\344\274\240", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MyTikTok", "\351\241\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MyTikTok", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyTikTok: public Ui_MyTikTok {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIKTOK_H
