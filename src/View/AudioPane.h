#ifndef AUDIOPANE_H
#define AUDIOPANE_H

#include <QWidget>

namespace Ui {
class AudioPane;
}

class AudioPane : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPane(QWidget *parent = 0);
    ~AudioPane();

private:
    Ui::AudioPane *ui;
};

#endif // AUDIOPANE_H
