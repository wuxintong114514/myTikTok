#include "commentdialog.h"
#include <QFile>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QIcon>
#include<QDebug>

CommentDialog::CommentDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("评论");
    // 检查图标文件是否存在
    if (QFile::exists("image/comment.png")) {
        setWindowIcon(QIcon("image/comment.png"));
    } else {
        // 处理图标文件不存在的情况
        qDebug() << "Icon file 'image/comment.png' not found.";
    }

    QVBoxLayout *layout = new QVBoxLayout();

    leComment = new QLineEdit();
    leComment->setPlaceholderText("留下你的精彩评论吧");
    layout->addWidget(leComment);

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    // 使用新的信号 - 槽连接语法
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CommentDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CommentDialog::accept);

    layout->addWidget(buttonBox);
    setLayout(layout);
}
