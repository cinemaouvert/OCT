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

    void on_comboBox_Codec_activated(QString codec);

    void on_horizontalSlider_VideoQuality_valueChanged();
    void on_spinBox_Quality_valueChanged( int value );

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
