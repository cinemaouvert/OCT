#ifndef SUBTITLEPANE_H
#define SUBTITLEPANE_H

#include <QWidget>

#include "src/Model/File.h"
#include "src/Model/Stream.h"

namespace Ui {
class SubtitlePane;
}

class SubtitlePane : public QWidget
{
    Q_OBJECT

public:
    explicit SubtitlePane(QWidget *parent = 0);
    explicit SubtitlePane(Model::File *file,Model::Stream *stream,QWidget *parent = 0);
    ~SubtitlePane();

private:
    Ui::SubtitlePane *ui;
    Model::File *m_file;
    Model::Stream *m_stream;
};

#endif // SUBTITLEPANE_H
