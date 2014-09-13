#ifndef CMDOUTPUT_H
#define CMDOUTPUT_H

#include <QWidget>

namespace Ui {
class CmdOutput;
}

class CmdOutput : public QWidget
{
    Q_OBJECT

public:
    explicit CmdOutput(QWidget *parent = 0);
    ~CmdOutput();

public slots:
    void receiveData(QByteArray);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CmdOutput *ui;
};

#endif // CMDOUTPUT_H
