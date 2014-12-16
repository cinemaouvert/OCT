#ifndef VIDEOPANE_H
#define VIDEOPANE_H

#include <QWidget>

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
};

#endif // VIDEOPANE_H
