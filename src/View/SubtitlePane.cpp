#include "MyModel.h"
#include "SubtitlePane.h"
#include "ui_subtitlepane.h"

#include <QFile>
#include <QMimeDatabase>


SubtitlePane::SubtitlePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubtitlePane),
    m_file(NULL),
    m_stream(NULL),
    m_player(NULL),
    m_model(NULL)
{
    ui->setupUi(this);
}

SubtitlePane::SubtitlePane(Model::File *file,Model::Stream *stream,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubtitlePane),
    m_file(file),
    m_stream(stream),
    m_player(NULL),
    m_model(NULL)
{
    ui->setupUi(this);

    m_player = new QtAV::AVPlayer;
    m_player->setRenderer(ui->videoWidget);
    ui->videoWidget->show();

    ui->subtitleTableView->setAlternatingRowColors(true);
    ui->subtitleTableView->horizontalHeader()->setStretchLastSection(true);

    parseSubtitleFile();

    /*
     * TODO : file to load
    this->loadFile(m_file->getFilePath());
    this->m_streamId = stream->getUID().toInt();
    player->setVideoStream(this->m_streamId);
    */

}

SubtitlePane::~SubtitlePane()
{
    if(ui) delete ui;
    if(m_player) delete m_player;
    if(m_model) delete m_model;
}

void SubtitlePane::on_playButton_clicked()
{

    if(!m_player->isPlaying()){
        m_player->play();
        if(m_player->isPlaying())
            ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else if(m_player->isPaused()){
        m_player->pause(false);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else{
        m_player->pause(true);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    }
}


void SubtitlePane::on_stopButton_clicked()
{
    if(m_player->isPlaying()){
        m_player->stop();
    }
    ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    ui->timeSlider->setValue(0);
    ui->timeLabel->setText(QTime(0,0).toString("hh:mm:ss"));
}

void SubtitlePane::loadFile(QString filepath)
{
    m_player->load(filepath,false);

    ui->timeSlider->setMaximum(m_player->duration());

    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(stopped()), SLOT(on_stopButton_clicked()));

}

void SubtitlePane::seek(int pos)
{
    if (!m_player->isPlaying())
        return;
    m_player->seek(pos*1000LL); // to msecs
}

void SubtitlePane::updateSlider()
{
    ui->timeSlider->setRange(0, int(m_player->duration()/1000LL));
    ui->timeSlider->setValue(int(m_player->position()/1000LL));
    ui->timeLabel->setText(QTime(0,0).addMSecs(m_player->position()).toString("hh:mm:ss"));
}

void SubtitlePane::parseSubtitleFile(){
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(this->m_file->getFilePath());
    QStringList subtitleList;
    QStringList startList;
    QStringList endList;
    QFile *file = new QFile(this->m_file->getFilePath());

    if (file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        QTextStream in(file);
        if(mime.name().contains("subrip")){
            while ( !in.atEnd() )
            {
                in.readLine(); // drop unused field
                QString line = in.readLine();   // read timestamps
                QStringList times = line.split("-->");  // split in start and stop
                startList.append(times.size()>0 ? times.at(0) :"");
                endList.append(times.size()>0 ? times.at(1) :"");
                QString line2 = " ";
                QString contentLine = "";
                while(line2 != "" && !in.atEnd()){
                    line2 = in.readLine();
                    contentLine += line2;
                }
                subtitleList.append(contentLine);

            }
        }else if(mime.name().contains("ssa") || mime.name().contains("ass")){
            while ( !in.atEnd() )
            {
                QString line = in.readLine();
                subtitleList.append(line);
            }
        }
    }
    file->close();
    delete file;

    m_model = new QStandardItemModel(subtitleList.size(),3);
    for(int i = 0; i < subtitleList.count() ; i++)
    {
        m_model->setItem(i,0,new QStandardItem(startList.at(i)));
        m_model->setItem(i,1,new QStandardItem(endList.at(i)));
        m_model->setItem(i,2,new QStandardItem(subtitleList.at(i)));
    }
    ui->subtitleTableView->setModel(m_model);
}
