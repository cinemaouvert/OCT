#ifndef SUBTITLEPANE_H
#define SUBTITLEPANE_H

#include <AVPlayer.h>
#include <QtAV/SubtitleFilter.h>
#include <QtAV/Subtitle.h>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QWidget>

#include "src/Model/File.h"
#include "src/Model/Stream.h"
#include "src/Controller/OCTDispatcher.h"

#include "MyModel.h"

namespace Ui {
class SubtitlePane;
}

class SubtitlePane : public QWidget
{
    Q_OBJECT

public:
    explicit SubtitlePane(QWidget *parent = 0);
    explicit SubtitlePane(Model::File *file,Model::Stream *stream,QWidget *parent = 0);
    ~SubtitlePane();

    void setDispatcher(Controller::OCTDispatcher *dispatcher);
    void applyReco();

public slots:
    void seek(int);
    void videoStreamAdded(Model::File*,Model::Stream*);

private slots:
    void on_playButton_clicked();

    void on_stopButton_clicked();

    void updateSlider();


    void on_lineEdit_Name_textChanged(const QString &name);

    void on_comboBox_Langage_activated(const QString &langage);

    void on_comboBox_Encode_activated(const QString &encode);

    void on_videoVisualisationComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::SubtitlePane *ui;
    Model::File *m_file;
    Model::Stream *m_stream;
    QtAV::AVPlayer *m_player;
    QStandardItemModel *m_model;
    QtAV::SubtitleFilter *m_pS;
    Controller::OCTDispatcher *m_dispatcher;
    void loadFile(QString filepath);
    void initPane();
    QString videoPath;

    void connectInterface();
    void parseSubtitleFile();

    QMap<QString,QString> m_languageMap;
    QMap<QString,QString> m_formatMap;
    QMap<QString,QString> m_encodingMap;
    void initLists();
signals:
    void subtitleChanged( Model::File *, Model::Stream *, QString, QString );
};

#endif // SUBTITLEPANE_H
