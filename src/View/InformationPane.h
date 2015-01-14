#ifndef INFORMATIONPANE_H
#define INFORMATIONPANE_H

#include <QStringlistModel>
#include <QWidget>
namespace Ui {
class InformationPane;
}
namespace Controller {
    class OCTDispatcher;
}
namespace Model {
    class Attachment;
}

class InformationPane : public QWidget
{
    Q_OBJECT

public:
    explicit InformationPane(QWidget *parent = 0);
    ~InformationPane();
    void setDispatcher(Controller::OCTDispatcher *m_dispatcher);

    void refresh();
private:
    Ui::InformationPane *ui;
    Controller::OCTDispatcher *m_dispatcher;
    QStringListModel *m_model;
};

#endif // INFORMATIONPANE_H
