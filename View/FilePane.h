#ifndef FILEPANE_H
#define FILEPANE_H

#include <QWidget>

#include <Controller/OCTDispatcher.h>

namespace Ui {
class FilePane;
}
namespace Controller
{
    class OCTDispatcher;
}


class FilePane : public QWidget
{
    Q_OBJECT

public:
    explicit FilePane(QWidget *parent = 0);
    void setDispatcher(Controller::OCTDispatcher *dispatcheur);
    ~FilePane();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::FilePane *ui;
    Controller::OCTDispatcher * m_dispatcher;
};

#endif // FILEPANE_H
