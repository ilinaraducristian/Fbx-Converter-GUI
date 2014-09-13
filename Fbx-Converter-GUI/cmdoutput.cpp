#include "cmdoutput.h"
#include "ui_cmdoutput.h"

CmdOutput::CmdOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmdOutput)
{
    ui->setupUi(this);
}

CmdOutput::~CmdOutput()
{
    delete ui;
}

void CmdOutput::receiveData(QByteArray ar)
{
    ui->textBrowser->setText(ar);
}

void CmdOutput::on_pushButton_clicked()
{
    this->close();
}
