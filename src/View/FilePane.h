#ifndef FILEPANE_H
#define FILEPANE_H

#include <QWidget>

#include <src/Controller/OCTDispatcher.h>
#include <QStringListModel>

namespace Ui {
class FilePane;
}
namespace Controller
{
    class OCTDispatcher;
}

namespace Model
{
    class File;
    class Attachment;
}

class FilePane : public QWidget
{
    Q_OBJECT

public:
    explicit FilePane(QWidget *parent = 0);
    void setDispatcher(Controller::OCTDispatcher *dispatcheur);
    void refresh();
    ~FilePane();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::FilePane *ui;
    Controller::OCTDispatcher * m_dispatcher;
    QStringListModel *model;
    QStringList list;
    void addItem(QString name);

};

#endif // FILEPANE_H