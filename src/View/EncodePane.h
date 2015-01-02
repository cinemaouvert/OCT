#ifndef ENCODEPANE_H
#define ENCODEPANE_H

#include <QStringListModel>
#include <QWidget>

#include <src/Controller/OCTDispatcher.h>

namespace Ui {
class EncodePane;
}

class EncodePane : public QWidget
{
    Q_OBJECT

public:
    explicit EncodePane(QWidget *parent = 0);
    void setDispatcher(Controller::OCTDispatcher *dispatcher);
    ~EncodePane();

    void refresh();
    void refreshProjectPane();
private slots:
    void on_newProjectButton_clicked();

private:
    Ui::EncodePane *ui;
    Controller::OCTDispatcher *m_dispatcher;
    QStringListModel *m_modelProjectList;
};

#endif // ENCODEPANE_H
