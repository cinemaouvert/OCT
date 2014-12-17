#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QVideoWidget>
#include <QWidget>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QVideoWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

private:
    Ui::VideoPlayer *ui;
};

#endif // VIDEOPLAYER_H
