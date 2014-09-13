#include "multiplefiles.h"
#include "ui_multiplefiles.h"

MultipleFiles::MultipleFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipleFiles)
{
    ui->setupUi(this);
}

MultipleFiles::~MultipleFiles()
{
    delete ui;
}
