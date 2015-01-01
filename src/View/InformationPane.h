#ifndef INFORMATIONPANE_H
#define INFORMATIONPANE_H

#include <QWidget>

namespace Ui {
class InformationPane;
}

class InformationPane : public QWidget
{
    Q_OBJECT

public:
    explicit InformationPane(QWidget *parent = 0);
    ~InformationPane();

private:
    Ui::InformationPane *ui;


};

#endif // INFORMATIONPANE_H
