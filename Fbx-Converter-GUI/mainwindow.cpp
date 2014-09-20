#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    output = new Output;
    mfiles = new MultipleFiles;
    about = new About;
    help = new Help;
    connect(this, SIGNAL(sendData(QByteArray)), output, SLOT(receiveData(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browse0_clicked()
{
    ui->input_file->setText(QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("Filmbox (*.fbx);;Collada (*.dae);;Object (*.obj)")));
}

void MainWindow::on_browse1_clicked()
{
    ui->output_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_convert_clicked()
{
    if(!QFile(ui->input_file->text()).exists() || ui->input_file->text().isEmpty())
    {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("Files doesn't exists!");
        messageBox->show();
    }else if(!QDir(ui->output_folder->text()).exists() || ui->output_folder->text().isEmpty())
    {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("Folder doesn't exists!");
        messageBox->show();
    }else if(QFileInfo(ui->input_file->text()).suffix() != "fbx" && QFileInfo(ui->input_file->text()).suffix() != "dae" && QFileInfo(ui->input_file->text()).suffix() != "obj")
    {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("Invalid file extension, only .fbx , .dae or .obj are permitted!");
        messageBox->show();
    }else
    {
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
        list<<ui->input_file->text();
        if(ui->filename->text().isEmpty())
            list<<(ui->output_folder->text()+'/')+(QFileInfo(ui->input_file->text()).baseName()+ui->fileT->currentText());
        else
            list<<(ui->output_folder->text()+'/')+(ui->filename->text()+ui->fileT->currentText());
        process->start(prgPath, list);
        process->waitForFinished(-1);
        emit sendData(process->readAll());
        if(ui->log->isChecked() && output->isHidden())
            output->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    mfiles->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    about->exec();
}

void MainWindow::on_actionHelp_triggered()
{
    help->exec();
}
