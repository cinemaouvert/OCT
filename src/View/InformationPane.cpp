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
    m_model(NULL),
    m_scrollArea(NULL)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    ui->treeView_Files->setModel(m_model);
    ui->treeView_Files->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    generateStruct(NULL);
}

void InformationPane::refresh(){
    QStringList list;
    ui->sampleComboBox->clear();
    ui->posterComboBox->clear();
    picturesList.clear();
    picturesList.append(tr("Aucun"));
    ui->sampleComboBox->addItem(QIcon(),tr("Aucun"));
    ui->posterComboBox->addItem(QIcon(),tr("Aucun"));
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
    if(index > 0){
        loadImageToGraphicView(ui->posterGraphicsView,index);
        QFile file(picturesList.at(index));
        if(file.open(QIODevice::ReadOnly)){
            QByteArray dataImage = file.readAll().toBase64();
            this->m_dispatcher->getCurrentProject()->addInformations("affiche", dataImage);
            this->m_dispatcher->checkProjectValidation();
        }
    }else{
        if(this->m_dispatcher->getCurrentProject()->informations()->contains("affiche")){
            this->m_dispatcher->getCurrentProject()->removeInformations("affiche");
            this->m_dispatcher->checkProjectValidation();
            ui->posterGraphicsView->setScene(NULL);
        }
    }
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
    if(index > 0)
        loadImageToGraphicView(ui->sampleGraphicView,index);
   /* if(index > 0){
        loadImageToGraphicView(ui->sampleGraphicView,index);
        QFile file(picturesList.at(index));
        if(file.open(QIODevice::ReadOnly)){
            QByteArray dataImage = file.readAll().toBase64();
            this->m_dispatcher->getCurrentProject()->addInformations("capture", dataImage);
            this->m_dispatcher->checkProjectValidation();
        }
    }else{
        if(this->m_dispatcher->getCurrentProject()->informations()->contains("capture")){
            this->m_dispatcher->getCurrentProject()->removeInformations("capture");
            this->m_dispatcher->checkProjectValidation();
            ui->posterGraphicsView->setScene(NULL);
        }
    }*/
}

void InformationPane::generateStruct(QMap<QString, QString>* infos){
    if(m_scrollArea != NULL){
        QWidget *wd = m_scrollArea->takeWidget();
        if(wd)
            delete wd;
        ui->verticalLayout_3->removeWidget(m_scrollArea);
    }

    m_scrollArea = new QScrollArea;
    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayoutLabel = new QVBoxLayout;
    QVBoxLayout *vLayoutLineEdit = new QVBoxLayout;

    if(this->m_dispatcher->informationMovieStruct() != NULL){
        QWidget *widget = new QWidget;
        for(int i = 0; i < this->m_dispatcher->informationMovieStruct()->size(); i++){

            QString labelName = this->m_dispatcher->informationMovieStruct()->at(i);
            if(labelName.compare("affiche") != 0){
                QString lineEditName = labelName;

                QLabel *label = new QLabel(labelName.replace("_", " "));
                label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                vLayoutLabel->addWidget(label);

                QLineEdit *lineEdit = new QLineEdit;
                if(infos != NULL && infos->size() > 0){
                    QString valueMovie = "";
                    valueMovie = infos->value(lineEditName);
                    lineEdit->setText(valueMovie);
                }

                lineEdit->setObjectName(lineEditName);
                lineEdit->setSizePolicy(QSizePolicy::Minimum , QSizePolicy::Minimum );
                lineEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                lineEdit->connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineEditInformation_textChanged()));
                lineEdit->connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(lineEditInformation_editingFinished()));

                vLayoutLineEdit->addWidget(lineEdit);
            }
        }
        hLayout->addItem(vLayoutLabel);
        hLayout->addItem(vLayoutLineEdit);

        widget->setLayout(hLayout);
        m_scrollArea->setWidget(widget);
        m_scrollArea->setWidgetResizable(true);

        ui->verticalLayout_3->addWidget(m_scrollArea);
    }

}

void InformationPane::lineEditInformation_textChanged(){
    QLineEdit *lineEdit = (QLineEdit*)sender();
    if(lineEdit->text().size() == 0){
        this->m_dispatcher->getCurrentProject()->removeInformations(lineEdit->objectName());
        this->m_dispatcher->checkProjectValidation();
    }else if(lineEdit->text().size() <= 1){
        this->m_dispatcher->getCurrentProject()->addInformations(lineEdit->objectName(), "OCPM");
        this->m_dispatcher->checkProjectValidation();
    }
}

void InformationPane::lineEditInformation_editingFinished(){
    QLineEdit *lineEdit = (QLineEdit*)sender();
    if(lineEdit->text().size() > 0)
        this->m_dispatcher->getCurrentProject()->addInformations(lineEdit->objectName(), lineEdit->text());
}
