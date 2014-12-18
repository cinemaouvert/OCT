#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <GLWidgetRenderer2.h>
#include <QVideoWidget>
#include <QWidget>

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QtAV::GLWidgetRenderer2
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

private:
    Ui::VideoPlayer *ui;
};

#endif // VIDEOPLAYER_H
