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
    class FileWrapper;
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
    void on_pushButton_AddFile_clicked();
    void on_pushButton_DeleteFile_clicked();
    void on_EditLine_Name_Changed();

private:
    Ui::FilePane *ui;
    Controller::OCTDispatcher * m_dispatcher;
    QStringListModel *model;
    QStringList list;
    void addItem(QString name);

};

#endif // FILEPANE_H
