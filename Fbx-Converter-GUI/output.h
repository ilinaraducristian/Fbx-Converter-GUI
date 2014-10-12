#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>
#include <QTextStream>

namespace Ui {
class Output;
}

class Output : public QWidget
{
    Q_OBJECT

public:
    explicit Output(QWidget *parent = 0);
    ~Output();

public slots:
    void receiveOutput(QString output, QByteArray array);

private:
    Ui::Output *ui;
};

#endif // OUTPUT_H
