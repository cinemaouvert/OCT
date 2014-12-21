#ifndef AUDIOPANE_H
#define AUDIOPANE_H

#include <QWidget>

#include "src/Model/File.h"
#include "src/Model/Stream.h"

namespace Ui {
class AudioPane;
}

class AudioPane : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPane(QWidget *parent = 0);
    explicit AudioPane(Model::File *file,Model::Stream *stream, QWidget *parent = 0);
    ~AudioPane();

private:
    Ui::AudioPane *ui;
    Model::File *m_file;
    Model::Stream *m_stream;
};

#endif // AUDIOPANE_H
