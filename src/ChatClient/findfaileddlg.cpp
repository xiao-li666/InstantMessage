#include "findfaileddlg.h"
#include "ui_findfaileddlg.h"
#include <QDebug>

FindFailedDlg::FindFailedDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindFailedDlg)
{
    ui->setupUi(this);
    setWindowTitle("添加");
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("FindFailedDlg");
    ui->failSureBtn->SetState("normal","hover","press");
    this->setModal(true);
}

FindFailedDlg::~FindFailedDlg()
{
    delete ui;
    qDebug() << "findFailedDlg is distracted";
}

void FindFailedDlg::on_failSureBtn_clicked()
{
    this->hide();
}

