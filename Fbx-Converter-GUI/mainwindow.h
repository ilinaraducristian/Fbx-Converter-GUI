#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <output.h>
#include <multiplefiles.h>
#include <about.h>
#include <help.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_browse0_clicked();

    void on_browse1_clicked();

    void on_convert_clicked();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

signals:
    void sendData(QByteArray);

private:
    Ui::MainWindow *ui;
    Output *output;
    MultipleFiles *mfiles;
    About *about;
    Help *help;
};

#endif // MAINWINDOW_H
