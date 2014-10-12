#include "processingdialog.h"
#include "ui_processingdialog.h"

ProcessingDialog::ProcessingDialog(QWidget *parent) :
    QDialog(parent,Qt::CustomizeWindowHint),
    ui(new Ui::ProcessingDialog)
{
    ui->setupUi(this);
    this->setFixedSize(230, 100);
}

ProcessingDialog::~ProcessingDialog()
{
    delete ui;
}
