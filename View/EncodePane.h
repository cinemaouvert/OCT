#ifndef ENCODEPANE_H
#define ENCODEPANE_H

#include <QWidget>

namespace Ui {
class EncodePane;
}

class EncodePane : public QWidget
{
    Q_OBJECT

public:
    explicit EncodePane(QWidget *parent = 0);
    ~EncodePane();

private:
    Ui::EncodePane *ui;
};

#endif // ENCODEPANE_H
