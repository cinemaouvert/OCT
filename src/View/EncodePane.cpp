#include "EncodePane.h"
#include "ui_encodepane.h"
#include "src/Controller/TreatmentThread.h"

#include <QMouseEvent>

EncodePane::EncodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncodePane)
{
    ui->setupUi(this);
    m_modelProjectList = new QStringListModel(this);
    ui->listViewProjects->setModel(m_modelProjectList);
    ui->listViewProjects->setAlternatingRowColors(true);
    ui->listViewProjects->setEncodePane(this);
    m_currentSteps = 0;
}

void EncodePane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    this->m_dispatcher = dispatcher;
    refreshProjectPane();
    connectInterface();
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
    QStringList list;
    foreach (Model::Project *project, *(m_dispatcher->getProjects())) {
        list << project->name();
    }
    m_modelProjectList->setStringList(list);
}

void EncodePane::on_newProjectButton_clicked()
{
    m_dispatcher->addToQueue();
    refreshProjectPane();
}

void EncodePane::initProgressBar(int progressMax)
{
    m_progressMax = progressMax;
    ui->progressBar_Encoding->setValue(0);
}

void EncodePane::passedProgressStep()
{
    m_currentSteps ++;
    ui->progressBar_Encoding->setValue((int)((float)((float)m_currentSteps/(float)m_progressMax)*100));
}

void EncodePane::connectInterface()
{
    connect(m_dispatcher->getTreatmentThread(),SIGNAL(initProgress(int)),this,SLOT(initProgressBar(int)));
    connect(m_dispatcher->getTreatmentThread(),SIGNAL(passedStep()),this,SLOT(passedProgressStep()));
}

void EncodePane::changeCurrentProject(int index)
{
    m_dispatcher->setCurrentProjectIndex(index);
}

void EncodePane::duplicateProject(int index)
{
    m_dispatcher->duplicateProject(index);
    refreshProjectPane();
}




