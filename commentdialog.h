#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H
#include<QDialog>
#include<QIcon>
#include<QVBoxLayout>//垂直布局管理
#include<QLineEdit>
#include<QDialogButtonBox>


class CommentDialog : public QDialog
{
    Q_OBJECT
public:
    CommentDialog(QWidget *parent = nullptr);
    QLineEdit *leComment;
};

#endif // COMMENTDIALOG_H
