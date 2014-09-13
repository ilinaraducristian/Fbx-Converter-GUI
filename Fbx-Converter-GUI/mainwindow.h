#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QFile>
#include <QDir>

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
    void on_pushBBrowse_clicked();

    void on_pushBBrowse_2_clicked();

    void on_pushBConvert_clicked();

    void on_lineEInputPath_textChanged(const QString &arg1);

    void on_lineEOutputDirectory_textChanged(const QString &arg1);

    void on_comboBFileType_currentTextChanged(const QString &arg1);

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

    void on_pushButton_clicked();

signals:
    void sendData(QByteArray);

private:
    Ui::MainWindow *ui;
    bool proces=false;
    QFileInfo fi;
    QFile file;
    QDir dir;
    QString fileExtension = "g3db";
};

#endif // MAINWINDOW_H
