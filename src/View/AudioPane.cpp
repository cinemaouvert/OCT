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
#include "src/Controller/Utils.h"

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
    initLists();
    initPane();
}

void AudioPane::initLists() {
    m_languageMap.insert( tr( "Allemand" ), "ger" );
    m_languageMap.insert( tr( "Anglais" ), "eng" );
    m_languageMap.insert( tr( "Français" ), "fre" );
    m_languageMap.insert( tr( "Espagnol" ), "spa" );
    m_languageMap.insert( tr( "Italien" ), "ita" );

    ui->comboBox_Langage->clear();
    ui->comboBox_Langage->insertItems( 0, m_languageMap.keys() );

    m_codecMap.insert(tr("FLAC"),"flac");
    m_codecMap.insert(tr("AAC"),"aac");
    m_codecMap.insert(tr("MP2"),"mp2");
    m_codecMap.insert(tr("MP3"),"mp3");

    ui->comboBox_AudioCodec->clear();
    ui->comboBox_AudioCodec->insertItems(0,m_codecMap.keys());

    //TODO FILL DELAI
    //m_delaiMap

    m_sampleRateMap.insert(tr("48 kHz"), "48");
    m_sampleRateMap.insert(tr("96 kHz (Recommendé)"),"96");

    ui->comboBox_Sampling->clear();
    ui->comboBox_Sampling->insertItems(0,m_sampleRateMap.keys());

    m_chanelsMap.insert(tr("Stéréo"),"2");
    m_chanelsMap.insert(tr("Mono"),"1");

    ui->comboBox_Channels->clear();
    ui->comboBox_Channels->insertItems(0,m_chanelsMap.keys());

    m_resolutionMap.insert(tr("16 bits"),"16");
    m_resolutionMap.insert(tr("24 bits"),"24");
    m_resolutionMap.insert(tr("35 bits"),"32");

    ui->comboBox_Size->clear();
    ui->comboBox_Size->insertItems(0,m_resolutionMap.keys());
}

AudioPane::~AudioPane()
{
    delete ui;
}

void AudioPane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
    connectInterface();
    applyReco();
}

// ========================================================================== //
// == CLASS METHODS ========================================================= //
// ========================================================================== //
void AudioPane::fillAudioCodecComboBox() {
    QStringList list = (QStringList() << "FLAC" << "AAC" << "MP1" << "MP2" << "MP3");
    ui->comboBox_AudioCodec->addItems( list );
}

void AudioPane::applyReco()
{
    if(this->m_dispatcher->getOCPMValidation()->isExist()){
        QString codec= this->m_dispatcher->getOCPMValidation()->recommendedAudioCodec();
        QString chanel= this->m_dispatcher->getOCPMValidation()->recommendedAudioChanel();
        QString spRate= this->m_dispatcher->getOCPMValidation()->recommendedAudioSamplingRate();

        int ixd = ui->comboBox_AudioCodec->findText(m_codecMap.key(codec),Qt::MatchExactly);
        if(ixd != -1){
            ui->comboBox_AudioCodec->setCurrentIndex(ixd);
            emit(on_comboBox_AudioCodec_activated(m_codecMap.key(codec)));
        }

        ixd = ui->comboBox_Channels->findText(m_chanelsMap.key(chanel),Qt::MatchExactly);
        if(ixd != -1){
            ui->comboBox_Channels->setCurrentIndex(ixd);
            emit(on_comboBox_Channels_activated(m_chanelsMap.key(chanel)));
        }
        // Khz
        ixd = ui->comboBox_Sampling->findText(m_sampleRateMap.key(spRate),Qt::MatchExactly);
        if(ixd != -1){
            ui->comboBox_Sampling->setCurrentIndex(ixd);
            emit(on_comboBox_Sampling_activated(m_sampleRateMap.key(spRate)));
        }
    }
}

// ========================================================================== //
// == EVENT ANS SIGNALS METHODS ============================================= //
// ========================================================================== //
void AudioPane::connectInterface() {
    connect( this, SIGNAL( audioParameterChanged( Model::File *, Model::Stream *, QString, QString ) ),
             m_dispatcher, SLOT( parameterChanged( Model::File *, Model::Stream *, QString, QString ) ) );
}

void AudioPane::initPane()
{
    int ixd ;
    Model::Parameter *p = m_stream->getParameters()->value(Model::Stream::CODEC_NAME);
    if(p){
        QString codec = p->value();
        ixd = ui->comboBox_AudioCodec->findText(m_codecMap.key(codec),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_AudioCodec->setCurrentIndex(ixd);
        else{
            ui->comboBox_AudioCodec->insertItem(0,codec);
            ui->comboBox_AudioCodec->setCurrentIndex(0);
        }

        ui->label_AudioCodecDefault->setText(tr("Original: ") + codec);
    }
    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::LANGUAGE);
    if(p){
        QString langue = p->value().remove("language=");
        ixd = ui->comboBox_Langage->findText(m_languageMap.key(langue),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Langage->setCurrentIndex(ixd);
        else{
            ui->comboBox_Langage->insertItem(0,langue);
            ui->comboBox_Langage->setCurrentIndex(0);
        }
        ui->labelLanguage->setText(tr("Original: ") + langue);
    }
    else{
        ui->comboBox_Langage->insertItem(0,"");
        ui->comboBox_Langage->setCurrentIndex(0);
    }
    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::AUDIO_CHANNELS);
    if(p){
        QString chanel = p->value();
        ixd = ui->comboBox_Channels->findText(m_chanelsMap.key(chanel),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Channels->setCurrentIndex(ixd);
        else{
            ui->comboBox_Channels->insertItem(0,chanel);
            ui->comboBox_Channels->setCurrentIndex(0);
        }
        ui->labelChannels->setText(tr("Original: ") + chanel);
    }else{
        ui->comboBox_Channels->insertItem(0,"");
        ui->comboBox_Channels->setCurrentIndex(0);
    }

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::AUDIO_DELAY);
    if(p){
        QString delay = p->value();    // TODO //
        ixd = ui->comboBox_Delay->findText(m_delaiMap.key(delay),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Delay->setCurrentIndex(ixd);
        else{
            ui->comboBox_Delay->insertItem(0,delay);
            ui->comboBox_Delay->setCurrentIndex(0);
        }
        ui->labelChannels->setText(tr("Original: ") + delay);
    }else{
        ui->comboBox_Delay->insertItem(0,"");
        ui->comboBox_Delay->setCurrentIndex(0);
    }

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::AUDIO_SAMPLE_RATE);
    if(p){
        QString sampleRate = p->value();  // INT //
        ixd = ui->comboBox_Sampling->findText(m_sampleRateMap.key(sampleRate),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Sampling->setCurrentIndex(ixd);
        else{
            ui->comboBox_Sampling->insertItem(0,sampleRate);
            ui->comboBox_Sampling->setCurrentIndex(0);
        }
        ui->labelSamplingRate->setText(tr("Original: ") + sampleRate);
    }else{
        ui->comboBox_Sampling->insertItem(0,"");
        ui->comboBox_Sampling->setCurrentIndex(0);
    }

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::RESOLUTION);
    if(p){
        QString resolution = p->value(); //TODO//
        ixd = ui->comboBox_Size->findText(m_resolutionMap.key(resolution),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Size->setCurrentIndex(ixd);
        else{
            ui->comboBox_Size->insertItem(0,resolution);
            ui->comboBox_Size->setCurrentIndex(0);
        }
        ui->labelResolution->setText(tr("Original: ") + resolution);
    }else{
        ui->comboBox_Size->insertItem(0,"");
        ui->comboBox_Size->setCurrentIndex(0);
    }


    QString name = m_stream->name();
    ui->lineEdit_Name->setText(name);
}

void AudioPane::on_lineEdit_Name_textChanged( QString name ) {
    this->m_stream->setName( name );
}

void AudioPane::on_comboBox_AudioCodec_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::CODEC_NAME, m_codecMap.value(arg));
}

void AudioPane::on_comboBox_Delay_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_DELAY, m_delaiMap.value(arg));
}

void AudioPane::on_comboBox_Sampling_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_SAMPLE_RATE, m_sampleRateMap.value(arg));
}

void AudioPane::on_comboBox_Channels_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::AUDIO_CHANNELS, m_chanelsMap.value(arg));
}

void AudioPane::on_comboBox_Size_activated(const QString &arg) {
    emit audioParameterChanged(m_file, m_stream, Model::Stream::RESOLUTION, m_resolutionMap.value(arg));
}
