#ifndef MULTIPLEFILES_H
#define MULTIPLEFILES_H

#include <QWidget>

namespace Ui {
class MultipleFiles;
}

class MultipleFiles : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleFiles(QWidget *parent = 0);
    ~MultipleFiles();

private:
    Ui::MultipleFiles *ui;
};

#endif // MULTIPLEFILES_H
