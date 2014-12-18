#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <AVPlayer.h>

namespace Ui {
class VideoPane;
}

class VideoPane : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPane(QWidget *parent = 0);
    ~VideoPane();

private slots:
    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_stopSlider_sliderMoved(int position);

    void on_startSlider_sliderMoved(int position);

private:
    Ui::VideoPane *ui;
    QtAV::AVPlayer *player;

    void loadFile(QString filepath);
};

#endif // VIDEOPANE_H
