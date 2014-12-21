#include "EncodePane.h"
#include "ui_encodepane.h"

EncodePane::EncodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncodePane)
{
    ui->setupUi(this);
    m_modelProjectList = new QStringListModel(this);

    ui->listViewProjects->setModel(m_modelProjectList);

}

void EncodePane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    this->m_dispatcher = dispatcher;
    refreshProjectPane();
}


EncodePane::~EncodePane()
{
    if(ui) delete ui;
    if(m_modelProjectList) delete m_modelProjectList;
}

void EncodePane::refresh()
{
}

void EncodePane::refreshProjectPane(){
    int i = 1;
    QStringList list;
    foreach (Model::Project *project, *(m_dispatcher->getProjects())) {
        list << project->name() + QString::number(i);
        qDebug() << project->name() + QString::number(i);
    }
    m_modelProjectList->setStringList(list);
}
