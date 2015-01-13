#ifndef SUBTITLEPANE_H
#define SUBTITLEPANE_H

#include <AVPlayer.h>
#include <QStringListModel>
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

public slots:
    void seek(int);

private slots:
    void on_playButton_clicked();

    void on_stopButton_clicked();

    void updateSlider();


private:
    Ui::SubtitlePane *ui;
    Model::File *m_file;
    Model::Stream *m_stream;
    QtAV::AVPlayer *m_player;
    QStringListModel *m_model;

    void loadFile(QString filepath);



    void parseSubtitleFile();
};

#endif // SUBTITLEPANE_H
