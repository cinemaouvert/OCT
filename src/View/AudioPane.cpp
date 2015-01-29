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

#include "AudioPane.h"
#include "ui_audiopane.h"

// ========================================================================== //
// == CONSTRUCTORS AND DESTRUCTORS ========================================== //
// ========================================================================== //
AudioPane::AudioPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(NULL),
    m_stream(NULL),
    m_dispatcher(NULL)
{
    ui->setupUi(this);
    fillAudioCodecComboBox();
}

AudioPane::AudioPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPane),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);
    fillAudioCodecComboBox();
}

AudioPane::~AudioPane()
{
    delete ui;
}

void AudioPane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
    connectInterface();
}

// ========================================================================== //
// == CLASS METHODS ========================================================= //
// ========================================================================== //
void AudioPane::fillAudioCodecComboBox() {
    QStringList list = (QStringList() << "FLAC" << "AAC" << "MP1" << "MP2" << "MP3");
    ui->comboBox_AudioCodec->addItems( list );
}

// ========================================================================== //
// == EVENT ANS SIGNALS METHODS ============================================= //
// ========================================================================== //
void AudioPane::connectInterface() {
    connect( this, SIGNAL( audioParameterChanged( Model::File *, Model::Stream *, QString, QString ) ),
             m_dispatcher, SLOT( parameterChanged( Model::File *, Model::Stream *, QString, QString ) ) );
}

void AudioPane::on_lineEdit_Name_textChanged( QString name ) {
    this->m_stream->setName( name );
}

void AudioPane::on_comboBox_AudioCodec_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::CODEC_NAME, arg);
}

void AudioPane::on_comboBox_Delay_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_DELAY, arg);
}

void AudioPane::on_comboBox_Sampling_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_SAMPLE_RATE, arg);
}

void AudioPane::on_comboBox_Channels_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_CHANNELS, arg);
}

void AudioPane::on_comboBox_Size_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::RESOLUTION, arg);
}
