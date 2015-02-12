#ifndef INFORMATIONPANE_H
#define INFORMATIONPANE_H

#include <QGraphicsView>
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
    void generateStruct(QMap<QString, QString>* infos);

public slots:
    void lineEditInformation_textChanged();
    void lineEditInformation_editingFinished();
private slots:

    void on_posterComboBox_currentIndexChanged(int index);

    void on_sampleComboBox_currentIndexChanged(int index);

private:
    Ui::InformationPane *ui;
    Controller::OCTDispatcher *m_dispatcher;
    QStringListModel *m_model;
    QStringList picturesList;
    QScrollArea *m_scrollArea;

    void loadImageToGraphicView(QGraphicsView *graphV, int index);

};

#endif // INFORMATIONPANE_H
