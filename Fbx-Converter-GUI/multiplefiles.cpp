#include "multiplefiles.h"
#include "ui_multiplefiles.h"

#include <QFileDialog>
#include <mainwindow.h>
#include <QMessageBox>
MultipleFiles::MultipleFiles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipleFiles)
{
    ui->setupUi(this);
    output = new Output;
    connect(this, SIGNAL(sendData(QByteArray)), output, SLOT(receiveData(QByteArray)));
}

MultipleFiles::~MultipleFiles()
{
    delete ui;
}

void MultipleFiles::on_browse0_clicked()
{
    ui->input_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MultipleFiles::on_browse1_clicked()
{
    ui->output_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MultipleFiles::on_convert_clicked()
{
    if(!QDir(ui->input_folder->text()).exists() || ui->input_folder->text().isEmpty())
    {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("Files doesn't exists!");
        messageBox->show();
    }else if(!QDir(ui->output_folder->text()).exists() || ui->output_folder->text().isEmpty())
    {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("Files doesn't exists!");
        messageBox->show();
    }else
    {
        int p=0;
        QFileInfoList list = QDir(ui->input_folder->text()).entryInfoList();
        QFileInfo temp[list.size()];
        for(int i=0,size=list.size();i<size;i++)
            if(list.at(i).suffix() == "fbx" || list.at(i).suffix() == "dae" || list.at(i).suffix() == "obj")
                temp[p++] = list.at(i);
        if(p==0)
        {
            QMessageBox *messageBox = new QMessageBox(this);
            messageBox->setText("No files with '.fbx, .dae, .obj' extension found!");
            messageBox->show();
        }else
        {
            QFileInfo files[p];
            for(int i=0;i<p;i++)
                files[i] = temp[i];

            QString prgPath = QDir::currentPath()+"\\fbx-conv.exe";
            QProcess *process = new QProcess(this);
            QStringList list;

            if(ui->log->isChecked())
                list<<"-v";
            if(ui->flip->isChecked())
                list<<"-f";
            if(ui->pack->isChecked())
                list<<"-p";
            list<<"-m"<<QString::number(ui->maxV->value());
            list<<"-b"<<QString::number(ui->maxB->value());
            list<<"-w"<<QString::number(ui->maxW->value());
            list<<"-o"<<ui->fileT->currentText().remove(0,1);
            list<<files[0].filePath();

            if(ui->filename->text().isEmpty())
                list<<(ui->output_folder->text()+'/')+((files[0].baseName())+ui->fileT->currentText());
            else
                list<<(ui->output_folder->text()+'/')+((ui->filename->text()+'0')+ui->fileT->currentText());

            process->start(prgPath, list);
            process->waitForFinished(-1);

            emit sendData(process->readAll());
            if(ui->log->isChecked() && output->isHidden())
                output->show();

            for(int i=1;i<p;i++)
            {
                list.removeLast();
                list.removeLast();
                list<<files[i].filePath();

                if(ui->filename->text().isEmpty())
                    list<<(ui->output_folder->text()+'/')+((files[i].baseName())+ui->fileT->currentText());
                else
                    list<<(ui->output_folder->text()+'/')+((ui->filename->text()+QString::number(i))+ui->fileT->currentText());

                process->start(prgPath, list);
                process->waitForFinished(-1);

                emit sendData(process->readAll());
                if(ui->log->isChecked() && output->isHidden())
                    output->show();
            }
        }
    }
}

void MultipleFiles::on_changeWindow_clicked()
{
    (new MainWindow)->show();
    this->hide();
}
