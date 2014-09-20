#ifndef MULTIPLEFILES_H
#define MULTIPLEFILES_H

#include <QWidget>
#include <QFileInfo>
#include <QProcess>
#include <output.h>

namespace Ui {
class MultipleFiles;
}

class MultipleFiles : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleFiles(QWidget *parent = 0);
    ~MultipleFiles();

private slots:
    void on_browse0_clicked();

    void on_browse1_clicked();

    void on_convert_clicked();

    void on_changeWindow_clicked();

signals:
    void sendData(QByteArray);

private:
    Ui::MultipleFiles *ui;
    Output *output;
};

#endif // MULTIPLEFILES_H
