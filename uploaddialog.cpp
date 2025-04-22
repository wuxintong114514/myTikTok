#include "uploaddialog.h"

UpLoadDialog::UpLoadDialog(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("发布");
    setWindowIcon(QIcon("image/tiktok.png"));
    QVBoxLayout *layout = new QVBoxLayout();
    teDescribe = new QTextEdit();
    teDescribe->setPlaceholderText("添加作品描述...");
    layout->addWidget(teDescribe);
    gbCate = new QGroupBox();
    cbMusic = new QCheckBox("music");
    cbDance = new QCheckBox("dance");
    cbDance->setChecked(true);
    cbComedy = new QCheckBox("comedy");
    hbox = new QHBoxLayout();
    hbox->addWidget(cbMusic);
    hbox->addWidget(cbDance);
    hbox->addWidget(cbComedy);
    gbCate->setLayout(hbox);
    layout->addWidget(gbCate);
    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->setOrientation(Qt::Orientation::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(accept()));
    layout->addWidget(buttonBox);
    setLayout(layout);
}
