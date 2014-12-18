#ifndef SUBTITLEPANE_H
#define SUBTITLEPANE_H

#include <QWidget>

namespace Ui {
class SubtitlePane;
}

class SubtitlePane : public QWidget
{
    Q_OBJECT

public:
    explicit SubtitlePane(QWidget *parent = 0);
    ~SubtitlePane();

private:
    Ui::SubtitlePane *ui;
};

#endif // SUBTITLEPANE_H
