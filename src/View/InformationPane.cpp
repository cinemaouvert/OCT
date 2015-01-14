#include "InformationPane.h"
#include "ui_informationpane.h"
#include "../Controller/OCTDispatcher.h"
#include "../Model/Attachment.h"


InformationPane::InformationPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationPane),
    m_model(NULL)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    ui->treeView_Files->setModel(m_model);
}

InformationPane::~InformationPane()
{
    if(ui) delete ui;
    if(m_model) delete m_model;
}

void InformationPane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    this->m_dispatcher = dispatcher;

    refresh();
}

void InformationPane::refresh(){
    QStringList list;
    foreach (Model::Attachment *attachment, *(m_dispatcher->getCurrentProject()->attachments())) {
        QStringList filepath = attachment->filepath().split("/");
        list.append(filepath.at(filepath.size()-1));
    }
    m_model->setStringList(list);
}
