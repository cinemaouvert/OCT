/**********************************************************************************
 * This file is part of Open Cinema Transcoder (OCT).
 *
 * Copyright (C) 2014 Catalogue Ouvert du Cinéma <dev@cinemaouvert.fr>
 *
 * Authors: Romain Boutin <romain.boutin@etu.univ-poitiers.fr>
 *          Thibaud Lamarche <lamarchethibaud@hotmail.com>
 *          William Le Coroller <william.le.coroller@gmail.com>
 *          Denis Saunier <saunier.denis.86@gmail.com>
 *
 * Open Cinema Transcoder is an initiative of Catalogue Ouvert du Cinéma.
 * The software was developed by four students of University of Poitiers
 * as school project.
 *
 * Open Cinema Transcoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Cinema Transcoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open Cinema Transcoder. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************/

#ifndef AUDIOPANE_H
#define AUDIOPANE_H

#include <QWidget>

#include "src/Model/File.h"
#include "src/Model/Stream.h"
#include "src/Controller/OCTDispatcher.h"

namespace Ui {
class AudioPane;
}

///
/// \brief The AudioPane class manages the audio pane view.
///
class AudioPane : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPane(QWidget *parent = 0);
    explicit AudioPane(Model::File *file,Model::Stream *stream, QWidget *parent = 0);
    ~AudioPane();

    ///
    /// \brief Set the OCTDispatcher
    /// \param dispatcher
    ///
    void setDispatcher(Controller::OCTDispatcher *dispatcher);

    ///
    /// \brief Initialize the corresponding comboBox with a set of known audio codec.
    ///
    void fillAudioCodecComboBox();

private:
    Ui::AudioPane *ui;
    Model::File *m_file;
    Model::Stream *m_stream;
    Controller::OCTDispatcher *m_dispatcher;


    ///
    /// \brief Connect the interface to the model through the OCTdispatcher.
    ///
    void connectInterface();

private slots:
    void on_lineEdit_Name_textChanged( QString name );

    void on_comboBox_AudioCodec_activated( const QString &arg );
    void on_comboBox_Delay_activated( const QString &arg );
    void on_comboBox_Sampling_activated(const QString &arg);
    void on_comboBox_Channels_activated(const QString &arg);
    void on_comboBox_Size_activated(const QString &arg);

signals:
    void audioCodecChanged( Model::File *, Model::Stream *, QString, QString );
    void audioDelayChanged( Model::File *, Model::Stream *, QString, QString );
    void audioSampleRateChanged( Model::File *, Model::Stream *, QString, QString );
    void audioChannelsChanged( Model::File *, Model::Stream *, QString, QString );
    void audioResolutionChanged( Model::File *, Model::Stream *, QString, QString );
};

#endif // AUDIOPANE_H
