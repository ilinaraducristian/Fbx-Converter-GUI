#include "output.h"
#include "ui_output.h"

Output::Output(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Output)
{
    ui->setupUi(this);
}

Output::~Output()
{
    delete ui;
}

void Output::receiveData(QByteArray byteArray)
{
    ui->text->append(byteArray);
}
