#ifndef FILEPANE_H
#define FILEPANE_H

#include <QWidget>

#include <src/Controller/OCTDispatcher.h>
#include <QStringListModel>
#include <QDir>

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
    ~FilePane();

    View::MainWindow *mainWindow() const;
    void setMainWindow(View::MainWindow *myMainWindow);
    void setDispatcher(Controller::OCTDispatcher *dispatcheur);

    void refresh();
    void refreshListViewImportFile();

signals:
    void projectNameChanged(QString newName);

private slots:
    void on_pushButtonAddFile_clicked();
    void on_pushButtonDeleteFile_clicked();

    //void on_lineEditExportName_textChanged(const QString &arg1);

    void on_comboBoxPreconfig_currentTextChanged(const QString &arg1);

    void on_findExport_clicked();

    void on_pushButtonGetInfos_clicked();

private:
    Ui::FilePane *ui;
    Controller::OCTDispatcher *m_dispatcher;
    QStringListModel *m_model;
    QStringList list;
    QDir m_preConfigsDir;
    View::MainWindow *m_mainWindow;
    void addItem(QString name);
    void splitterNoCollapsing();
    void connectInterface();
};

#endif // FILEPANE_H
