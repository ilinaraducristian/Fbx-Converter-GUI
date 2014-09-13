#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmdoutput.h>
#include <about.h>
#include <help.h>
#include <QtCore>
#include <QFileDialog>

CmdOutput *cmd;
About *about;
Help *help;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    file.setFileName("");
    dir.setPath("");
    ui->setupUi(this);
    cmd = new CmdOutput;
    connect(this, SIGNAL(sendData(QByteArray)), cmd, SLOT(receiveData(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushBBrowse_clicked()
{
    ui->lineEInputPath->setText(QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("Filmbox (*.fbx);;Collada (*.dae);;Object (*.obj)")));
}

void MainWindow::on_pushBBrowse_2_clicked()
{
    ui->lineEOutputDirectory->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_pushBConvert_clicked()
{
    if(!proces)
    {
        proces=true;
        ui->labelStatus->setText("<html><head/><body><p><center><span style=\" font-size:18pt; font-weight:600; color:#ff0004;\">Converting Please Wait...</span></center></p></body></html>");
        QProcess *process = new QProcess(this);
        QStringList list;
        list << "-v" << "-o " << fileExtension;
        if(ui->checkBFlipV->isChecked())list<<"-f";
        if(ui->checkBPackcolors->isChecked())list<<"-p";
        list<< "-m" << QString::number(ui->spinBMaxV->value())
            << "-b" << QString::number(ui->spinBMaxBones->value())
            << "-w" << QString::number(ui->spinBMaxWeight->value());
        list<< file.fileName();
        if(ui->lineEFileName->text().isEmpty())
            list<< ((dir.path() + "\\") + ("convertedFile" + ui->comboBFileType->currentText()));
        else
            list<<((dir.path() + "\\") + (ui->lineEFileName->text() + ui->comboBFileType->currentText()));
        process->start(QDir::currentPath() + "\\fbx-conv.exe", list);
        process->waitForFinished(-1);
        if(process->exitCode() == 0)
            ui->labelStatus->setText("<html><head/><body><p><center><span style=\" font-size:18pt; font-weight:600; color:#009900;\">Converted!</span></center></p></body></html>");
        else
            ui->labelStatus->setText("<html><head/><body><p><center><span style=\" font-size:18pt; font-weight:600; color:#ff0004;\">Error!</span></center></p></body></html>");
        if(ui->checkBLog->isChecked())
        {
            emit sendData(process->readAll());
            if(cmd->isHidden())cmd->show();
        }
        proces=false;
    }
}

void MainWindow::on_lineEInputPath_textChanged(const QString &arg1)
{
    file.setFileName(arg1);
    fi = QFileInfo(file.fileName());
    if(QFile(QDir::currentPath() + "\\fbx-conv.exe").exists() && file.exists() && dir.exists() && (fi.suffix() == "fbx" || fi.suffix() == "obj" || fi.suffix() == "dae"))
        ui->pushBConvert->setEnabled(true);
    else ui->pushBConvert->setEnabled(false);
}

void MainWindow::on_lineEOutputDirectory_textChanged(const QString &arg1)
{
    dir.setPath(arg1);
    if(QFile(QDir::currentPath() + "\\fbx-conv.exe").exists() && file.exists() && dir.exists() && (fi.suffix() == "fbx" || fi.suffix() == "obj" || fi.suffix() == "dae"))
        ui->pushBConvert->setEnabled(true);
    else ui->pushBConvert->setEnabled(false);
}

void MainWindow::on_comboBFileType_currentTextChanged(const QString &arg1)
{
    fileExtension = arg1;
    fileExtension.remove(0, 1);
}

void MainWindow::on_actionAbout_triggered()
{
    about = new About;
    about->setWindowFlags(Qt::WindowCloseButtonHint);
    about->exec();
}

void MainWindow::on_actionHelp_triggered()
{
    help = new Help;
    help->setWindowFlags(Qt::WindowCloseButtonHint);
    help->exec();
}
