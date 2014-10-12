#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QSysInfo>
#include <vector>

#include <processingdialog.h>
#include <output.h>
#include <about.h>
#include <help.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendOutput(QString, QByteArray);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

    void on_pushButtons_clicked();

    void on_actionHelp_triggered();

    void on_pushButtons_2_clicked();

    void on_pushButtons_3_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    QStringList arguments;
    QProcess *process;

    QMessageBox *msgBox;

    ProcessingDialog *processingDialog;
    Output *output;
    About *about;
    Help *help;

    bool stob(QString str);
    QString btos(bool bol);
    int curindex;
};

#endif // MAINWINDOW_H
