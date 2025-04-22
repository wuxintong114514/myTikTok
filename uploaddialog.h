#ifndef UPLOADDIALOG_H
#define UPLOADDIALOG_H
#include<QDialog>
#include<QVBoxLayout>
#include<QTextEdit>
#include<QGroupBox>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QDialogButtonBox>

class UpLoadDialog : public QDialog
{
    Q_OBJECT
public:
    UpLoadDialog(QWidget *parent = nullptr);
    QTextEdit *teDescribe;
    QGroupBox *gbCate;
    QCheckBox *cbMusic,*cbDance,*cbComedy;
    QHBoxLayout *hbox;
};

#endif // UPLOADDIALOG_H
