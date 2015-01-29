#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <AVPlayer.h>

#include <iostream>

#include "src/Model/File.h"
#include "src/Model/Stream.h"
#include "src/Controller/OCTDispatcher.h"

namespace Ui {
class VideoPane;
}

class VideoPane : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPane(QWidget *parent = 0);
    explicit VideoPane(Model::File *file,Model::Stream *s,QWidget *parent = 0);
    ~VideoPane();

    void setDispatcher(Controller::OCTDispatcher *dispatcher);
public slots:
    void seek(int);

private slots:
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_stopSlider_sliderMoved(int position);
    void on_startSlider_sliderMoved(int position);
    void updateSlider();
    void on_timeStart_timeChanged(const QTime &time);
    void on_timeStop_timeChanged(const QTime &time);
    void on_horizontalSlider_VideoQuality_valueChanged();
    void on_spinBox_Quality_valueChanged( int value );

    void on_lineEdit_TrackName_textChanged(const QString &name);
    void on_comboBox_Codec_activated(QString codec);
    void on_comboBox_Langage_activated(const QString &arg);
    void on_comboBox_DefaultTrack_activated(const QString &arg);
    void on_comboBox_VideoSize_activated(const QString &arg);
    void on_comboBox_Scale_activated(const QString &arg);
    // TODO :
    void on_comboBox_BlackStuff_activated(const QString &arg);
    void on_comboBox_Frames_activated(const QString &arg);
    // TODO :
    void on_comboBox_Filter_activated(const QString &arg);
    // TODO :
    void on_lineEdit_OptionsFfmpeg_textChanged(const QString &arg);
    // TODO :
    void on_spinBox_Quality_valueChanged(const QString &arg);
    void on_lineEdit_AverageBitrate_textChanged(const QString &arg);
    // TODO :
    void on_checkBox_clicked(bool checked);
    // TODO :
    void on_checkBox_2_clicked(bool checked);
    // TODO :
    void on_comboBox_x264Preset_activated(const QString &arg);
    // TODO :
    void on_comboBox_x264Tune_activated(const QString &arg);
    // TODO :
    void on_comboBox_x264Profile_activated(const QString &arg);
    // TODO :
    void on_comboBox_x264Level_activated(const QString &arg);
    // TODO :
    void on_spinTop_valueChanged(const QString &arg);
    // TODO :
    void on_spinLeft_valueChanged(const QString &arg);
    // TODO :
    void on_spinRight_valueChanged(const QString &arg);
    // TODO :
    void on_spinBot_valueChanged(const QString &arg);
    // TODO :
    void on_timeStart_dateTimeChanged(const QDateTime &dateTime);
    // TODO :
    void on_timeStop_dateTimeChanged(const QDateTime &dateTime);

signals:
    void videoParameterChanged( Model::File *, Model::Stream *, QString, QString );

private:
    Ui::VideoPane *ui;
    QtAV::AVPlayer *m_player;
    Model::File *m_file;
    int m_streamId;
    Model::Stream *m_stream;
    Controller::OCTDispatcher *m_dispatcher;

    // Class methods
    void connectInterface();
    void loadFile(QString filepath);
    void connectPlayer();

};

#endif // VIDEOPANE_H
