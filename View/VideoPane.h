#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

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

private:
    Ui::VideoPane *ui;
    QMediaPlayer * player;
};

#endif // VIDEOPANE_H
