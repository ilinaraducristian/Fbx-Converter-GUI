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

void Output::receiveOutput(QString output, QByteArray array)
{
    ui->text->append(("File: "+output)+"\n");
    ui->text1->append(("File: "+output)+"\n");
    ui->text2->append(("File: "+output)+"\n");
    QTextStream out(array);
    out.flush();
    while(!out.atEnd())
    {
        QString temp;
        ui->text->append(temp = out.readLine());
        if(temp.contains("error"))
            ui->text1->append(("<div style=\"color:#DB1D1D\">"+temp)+"</div>");
        if(temp.contains("warning"))
            ui->text2->append(("<div style=\"color:#CCCC00\">"+temp)+"</div>");
    }
}
