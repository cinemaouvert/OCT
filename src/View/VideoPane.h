#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <AVPlayer.h>

#include <iostream>

#include "src/Model/File.h"
#include "src/Model/Stream.h"

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

    // Video parameters fields
    QString m_Video_Resolution;
    QString m_Video_Scale;
    QString m_Video_Filter;
    QString m_Video_Language;
    QString m_Video_TrackName;
    bool m_Video_BlackStuff;
    QString m_Video_DefaultTrack;
    QString m_Video_FramePerSecond;
    QString m_Video_Codec;

    // Configuration x264 Codec
    int m_Video_Quality;
    int m_Video_Bitrate;
    bool m_Video_DoublePass;
    bool m_Video_Turbo;
    QString m_Video_Preset;
    QString m_Video_Tune;
    QString m_Video_Profile;
    QString m_Video_Level;
    QString m_Video_ffmpegOptions;

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

private:
    Ui::VideoPane *ui;
    QtAV::AVPlayer *m_player;
    Model::File *m_file;
    int m_streamId;
    Model::Stream *m_stream;

    // Class methods
    void loadFile(QString filepath);
};

#endif // VIDEOPANE_H
