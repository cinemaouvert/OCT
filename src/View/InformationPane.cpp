#include "InformationPane.h"
#include "ui_informationpane.h"
#include "../Controller/OCTDispatcher.h"
#include "../Model/Attachment.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>

InformationPane::InformationPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationPane),
    m_model(NULL)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    ui->treeView_Files->setModel(m_model);
    ui->treeView_Files->header()->setVisible(false);
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
    generateStruct();
}

void InformationPane::refresh(){
    QStringList list;
    ui->sampleComboBox->clear();
    ui->posterComboBox->clear();
    picturesList.clear();
    foreach (Model::Attachment *attachment, *(m_dispatcher->getCurrentProject()->attachments())) {
        QStringList filepath = attachment->filepath().split("/");
        QString fileName = filepath.at(filepath.size()-1);
        list.append(fileName);
        if(fileName.contains(".jpg") || fileName.contains(".jpeg") || fileName.contains(".png") || fileName.contains(".gif")){
            ui->sampleComboBox->addItem(QIcon(),fileName);
            ui->posterComboBox->addItem(QIcon(),fileName);
            picturesList.append(attachment->filepath());
        }

    }
    m_model->setStringList(list);
    loadImageToGraphicView(ui->posterGraphicsView,0);
    loadImageToGraphicView(ui->sampleGraphicView,0);
}



void InformationPane::on_posterComboBox_currentIndexChanged(int index)
{
    loadImageToGraphicView(ui->posterGraphicsView,index);
}

void InformationPane::loadImageToGraphicView(QGraphicsView *graphV,int index){
    if(picturesList.size()>0 && index>=0){
        QGraphicsScene* scene = new QGraphicsScene();
        graphV->setScene(scene);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(picturesList.at(index))));
        scene->addItem(item);
        graphV->fitInView(0,0,scene->width(),scene->height());
        graphV->show();
    }
}

void InformationPane::on_sampleComboBox_currentIndexChanged(int index)
{
    loadImageToGraphicView(ui->sampleGraphicView,index);
}

void InformationPane::generateStruct(){
    QScrollArea *scrollArea = new QScrollArea;
    QVBoxLayout *vLayout = new QVBoxLayout;
    for(int i = 0; i <= this->m_dispatcher->informationMovieStruct()->size(); i++){

        QHBoxLayout *hLayout = new QHBoxLayout;
        QLabel *label = new QLabel("");
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        hLayout->addWidget(label);
        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        hLayout->addSpacerItem(spacer);
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setAlignment(Qt::AlignLeft);
        hLayout->addWidget(lineEdit);
        hLayout->addSpacerItem(spacer);
        vLayout->addItem(hLayout);

    }

    scrollArea->setLayout(vLayout);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->verticalLayout_3->addWidget(scrollArea);
    //ui->verticalLayout_3->addSpacerItem(new QSpacerItem(20,30,QSizePolicy::Minimum, QSizePolicy::Maximum));


}
