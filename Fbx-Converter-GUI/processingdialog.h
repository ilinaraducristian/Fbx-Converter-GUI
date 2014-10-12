#ifndef PROCESSINGDIALOG_H
#define PROCESSINGDIALOG_H

#include <QDialog>

namespace Ui {
class ProcessingDialog;
}

class ProcessingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessingDialog(QWidget *parent = 0);
    ~ProcessingDialog();

private:
    Ui::ProcessingDialog *ui;
};

#endif // PROCESSINGDIALOG_H
