#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedWidth(400);

    processingDialog = new ProcessingDialog;
    output = new Output;
    about = new About;
    help = new Help;

    connect(this, SIGNAL(sendOutput(QString,QByteArray)), output, SLOT(receiveOutput(QString,QByteArray)));
    QFile prop("prop.fbxgui");
    if(prop.exists())
    {
        prop.open(QIODevice::ReadOnly);
        QTextStream in(&prop);
        ui->input_folder->setText(in.readLine());
        ui->output_folder->setText(in.readLine());
        ui->flipV->setChecked(stob(in.readLine()));
        ui->packC->setChecked(stob(in.readLine()));
        ui->showLog->setChecked(stob(in.readLine()));
        ui->maxM->setValue(in.readLine().toInt());
        ui->maxB->setValue(in.readLine().toInt());
        ui->maxW->setValue(in.readLine().toInt());
        ui->fbx->setChecked(stob(in.readLine()));
        ui->g3db->setChecked(stob(in.readLine()));
        ui->g3dj->setChecked(stob(in.readLine()));
        ui->sinput_folder->setText(in.readLine());
        ui->soutput_folder->setText(in.readLine());
        ui->sflipV->setChecked(stob(in.readLine()));
        ui->spackC->setChecked(stob(in.readLine()));
        ui->sshowLog->setChecked(stob(in.readLine()));
        ui->smaxM->setValue(in.readLine().toInt());
        ui->smaxB->setValue(in.readLine().toInt());
        ui->smaxW->setValue(in.readLine().toInt());
        ui->sfbx->setChecked(stob(in.readLine()));
        ui->sg3db->setChecked(stob(in.readLine()));
        ui->sg3dj->setChecked(stob(in.readLine()));
        prop.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->input_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Input Folder"), "", QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->output_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Output Folder"), "", QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!QDir(ui->input_folder->text()).exists() || ui->input_folder->text().isEmpty())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Input directory doesn't exists!");
        msgBox->show();
    }else if(!QDir(ui->output_folder->text()).exists() || ui->output_folder->text().isEmpty())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Output directory doesn't exists!");
        msgBox->show();
    }else if(!ui->fbx->isChecked() && !ui->g3db->isChecked() && !ui->g3dj->isChecked())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Please select a file output type!");
        msgBox->show();
    }else
    {
        QFileInfoList list = QDir(ui->input_folder->text()).entryInfoList();
        vector<QFileInfo> files;
        for(QFileInfo fileInfo : list)
            if(fileInfo.suffix().toLower() == "fbx" || fileInfo.suffix().toLower() == "dae" || fileInfo.suffix().toLower() == "obj")
                files.push_back(fileInfo);
        if(files.empty())
        {
            msgBox = new QMessageBox(this);
            msgBox->setText("No file with .fbx , .dae , .obj extension found!");
            msgBox->show();
        }else
        {
            // START CONVERSION
            processingDialog->show();
            if(ui->flipV->isChecked()) arguments << "-f";
            if(ui->packC->isChecked()) arguments << "-p";
            if(ui->showLog->isChecked()) arguments << "-v";
            arguments << "-m" << QString::number(ui->maxM->value());
            arguments << "-b" << QString::number(ui->maxB->value());
            arguments << "-w" << QString::number(ui->maxW->value());
            arguments << "-o";
            if(ui->fbx->isChecked())
            {
                arguments << "fbx";
                for(QFileInfo file : files)
                {
                    arguments << file.filePath();
                    arguments << (ui->output_folder->text()+"\\")+(file.baseName()+".fbx");
                    process = new QProcess(this);
                    process->start(QDir::currentPath()+"\\fbx-conv-win32.exe", arguments);
                    process->waitForFinished(-1);
                    emit sendOutput(file.baseName()+".fbx", process->readAll());
                    arguments.removeLast();arguments.removeLast();
                }
                arguments.removeLast();
            }
            if(ui->g3db->isChecked())
            {
                arguments << "g3db";
                for(QFileInfo file : files)
                {
                    arguments << file.filePath();
                    arguments << (ui->output_folder->text()+"\\")+(file.baseName()+".g3db");
                    process = new QProcess(this);
                    process->start(QDir::currentPath()+"\\fbx-conv-win32.exe", arguments);
                    process->waitForFinished(-1);
                    emit sendOutput(file.baseName()+".g3db", process->readAll());
                    arguments.removeLast();arguments.removeLast();
                }
                arguments.removeLast();
            }
            if(ui->g3dj->isChecked())
            {
                arguments << "g3dj";
                for(QFileInfo file : files)
                {
                    arguments << file.filePath();
                    arguments << (ui->output_folder->text()+"\\")+(file.baseName()+".g3dj");
                    process = new QProcess(this);
                    process->start(QDir::currentPath()+"\\fbx-conv-win32.exe", arguments);
                    process->waitForFinished(-1);
                    emit sendOutput(file.baseName()+".g3dj", process->readAll());
                    arguments.removeLast();arguments.removeLast();
                }
                arguments.removeLast();
            }
            if(output->isHidden())
                output->show();
            processingDialog->hide();
        }
        arguments.clear();
    }

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

bool MainWindow::stob(QString str)
{
    if(str == "true")
        return true;
    return false;
}

QString MainWindow::btos(bool bol)
{
    if(bol)
        return "true";
    return "false";
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(QFileDialog::getSaveFileName(this, tr("Save File"), "prop", tr("Prop File (*.fbxgui)")));
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
        out<<ui->input_folder->text()+"\n";
        out<<ui->output_folder->text()+"\n";
        out<<btos(ui->flipV->isChecked())+"\n";
        out<<btos(ui->packC->isChecked())+"\n";
        out<<btos(ui->showLog->isChecked())+"\n";
        out<<QString::number(ui->maxM->value())+"\n";
        out<<QString::number(ui->maxB->value())+"\n";
        out<<QString::number(ui->maxW->value())+"\n";
        out<<btos(ui->fbx->isChecked())+"\n";
        out<<btos(ui->g3db->isChecked())+"\n";
        out<<btos(ui->g3dj->isChecked())+"\n";
        out<<ui->sinput_folder->text()+"\n";
        out<<ui->soutput_folder->text()+"\n";
        out<<btos(ui->sflipV->isChecked())+"\n";
        out<<btos(ui->spackC->isChecked())+"\n";
        out<<btos(ui->sshowLog->isChecked())+"\n";
        out<<QString::number(ui->smaxM->value())+"\n";
        out<<QString::number(ui->smaxB->value())+"\n";
        out<<QString::number(ui->smaxW->value())+"\n";
        out<<btos(ui->sfbx->isChecked())+"\n";
        out<<btos(ui->sg3db->isChecked())+"\n";
        out<<btos(ui->sg3dj->isChecked());
        file.close();
}

void MainWindow::on_actionOpen_triggered()
{
    QFile prop(QFileDialog::getOpenFileName(this, tr("Select File"), "prop.fbxgui", "Prop File (*.fbxgui)"));
    if(prop.exists())
    {
        prop.open(QIODevice::ReadOnly);
        QTextStream in(&prop);
            ui->input_folder->setText(in.readLine());
            ui->output_folder->setText(in.readLine());
            ui->flipV->setChecked(stob(in.readLine()));
            ui->packC->setChecked(stob(in.readLine()));
            ui->showLog->setChecked(stob(in.readLine()));
            ui->maxM->setValue(in.readLine().toInt());
            ui->maxB->setValue(in.readLine().toInt());
            ui->maxW->setValue(in.readLine().toInt());
            ui->fbx->setChecked(stob(in.readLine()));
            ui->g3db->setChecked(stob(in.readLine()));
            ui->g3dj->setChecked(stob(in.readLine()));
            ui->sinput_folder->setText(in.readLine());
            ui->soutput_folder->setText(in.readLine());
            ui->sflipV->setChecked(stob(in.readLine()));
            ui->spackC->setChecked(stob(in.readLine()));
            ui->sshowLog->setChecked(stob(in.readLine()));
            ui->smaxM->setValue(in.readLine().toInt());
            ui->smaxB->setValue(in.readLine().toInt());
            ui->smaxW->setValue(in.readLine().toInt());
            ui->sfbx->setChecked(stob(in.readLine()));
            ui->sg3db->setChecked(stob(in.readLine()));
            ui->sg3dj->setChecked(stob(in.readLine()));
            prop.close();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    about->show();
}

void MainWindow::on_actionHelp_triggered()
{
    help->show();
}

void MainWindow::on_pushButtons_clicked()
{
    ui->sinput_folder->setText(QFileDialog::getOpenFileName(this, tr("Select File"), "", "Filmbox (*.fbx);;Collada (*.dae);;Object (*.obj)"));
}

void MainWindow::on_pushButtons_2_clicked()
{
    ui->soutput_folder->setText(QFileDialog::getExistingDirectory(this, tr("Select Output Folder"), "", QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_pushButtons_3_clicked()
{
    if(!QFile(ui->input_folder->text()).exists() || ui->input_folder->text().isEmpty())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Input file doesn't exists!");
        msgBox->show();
    }else if(!QDir(ui->output_folder->text()).exists())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Output directory doesn't exists!");
        msgBox->show();
    }else if(!ui->sfbx->isChecked() && !ui->sg3db->isChecked() && !ui->sg3dj->isChecked())
    {
        msgBox = new QMessageBox(this);
        msgBox->setText("Please select a file output type!");
        msgBox->show();
    }else
    {
        //START PROCESSING
        processingDialog->show();
        if(ui->sflipV->isChecked()) arguments << "-f";
        if(ui->spackC->isChecked()) arguments << "-p";
        if(ui->sshowLog->isChecked()) arguments << "-v";
        arguments << "-m" << QString::number(ui->smaxM->value());
        arguments << "-b" << QString::number(ui->smaxB->value());
        arguments << "-w" << QString::number(ui->smaxW->value());
        arguments << "-o";
        if(ui->sfbx->isChecked())
        {
            arguments<<"fbx";
            arguments<<ui->sinput_folder->text();
            arguments<<(ui->soutput_folder->text()+"\\")+(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".fbx");
            process = new QProcess(this);
            process->start(QDir::currentPath()+"\\fbx-conv-win32.exe", arguments);
            process->waitForFinished(-1);
            emit sendOutput(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".fbx", process->readAll());
            arguments.removeLast();arguments.removeLast();arguments.removeLast();
        }
        if(ui->sg3db)
        {
            arguments<<"g3db";
            arguments<<ui->sinput_folder->text();
            arguments<<(ui->soutput_folder->text()+"\\")+(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".g3db");
            process = new QProcess(this);
            process->start(QDir::currentPath()+"\\fbx-conv-win32.exe", arguments);
            process->waitForFinished(-1);
            emit sendOutput(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".g3db", process->readAll());
            arguments.removeLast();arguments.removeLast();arguments.removeLast();
        }
        if(ui->g3dj)
        {
            arguments<<"g3dj";
            arguments<<ui->sinput_folder->text();
            arguments<<(ui->soutput_folder->text()+"\\")+(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".g3dj");
            process = new QProcess(this);
            process->start(QDir::currentPath()+"\\fbx-conv-win32-win32.exe", arguments);
            process->waitForFinished(-1);
            emit sendOutput(QFileInfo(QFile(ui->sinput_folder->text())).baseName()+".g3dj", process->readAll());
            arguments.removeLast();arguments.removeLast();arguments.removeLast();
        }
        arguments.clear();
        processingDialog->hide();
        if(output->isHidden())
            output->show();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    curindex=index;
}
