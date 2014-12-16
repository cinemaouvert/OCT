#ifndef FILEPANE_H
#define FILEPANE_H

#include <QWidget>

namespace Ui {
class FilePane;
}

class FilePane : public QWidget
{
    Q_OBJECT

public:
    explicit FilePane(QWidget *parent = 0);
    ~FilePane();

private:
    Ui::FilePane *ui;
};

#endif // FILEPANE_H
