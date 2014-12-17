#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>
#include <QVideoWidget>

namespace Ui {
class VideoPane;
}

class VideoPane : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPane(QWidget *parent = 0);
    ~VideoPane();

private:
    Ui::VideoPane *ui;
    QVideoWidget *qvideoWidget;
};

#endif // VIDEOPANE_H
