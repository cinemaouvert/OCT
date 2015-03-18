#include "VideoPane.h"
#include "ui_videopane.h"

#include <AVPlayer.h>

// ========================================================================== //
// == CONSTRUCTORS AND DESTRUCTORS ========================================== //
// ========================================================================== //
VideoPane::VideoPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    m_player(NULL),
    m_file(NULL),
    m_stream(NULL),
    m_dispatcher(NULL)
{
    ui->setupUi(this);


}

VideoPane::VideoPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    m_player(NULL),
    m_file(file),
    m_stream(stream),
    m_dispatcher(NULL)
{
    ui->setupUi(this);
    initVideoLists();
    m_player = new QtAV::AVPlayer;
    m_player->setRenderer(ui->videoWidget);


    this->m_streamId = stream->getUID().toInt();
    initPane();
}

VideoPane::~VideoPane()
{
    if(ui) delete ui;
    if(m_player) m_player->disconnect();
    if(m_player) delete m_player;
    if(m_dispatcher) delete m_dispatcher;
}

// ========================================================================== //
// == ACCESSORS AND MUTATORS ================================================ //
// ========================================================================== //
void VideoPane::setDispatcher(Controller::OCTDispatcher *dispatcher) {
    m_dispatcher = dispatcher;
    connectInterface();
    applyReco();
}

Model::File* VideoPane::getFile(){
    return this->m_file;
}

Model::Stream *VideoPane::getStream(){
    return this->m_stream;
}

// ========================================================================== //
// == CLASS METHODS ========================================================= //
// ========================================================================== //
void VideoPane::seek(int pos)
{
    if (!m_player->isPlaying())
        return;
    m_player->seek(pos*1000LL); // to msecs
}

void VideoPane::loadFile(QString filepath)
{
    m_player->load(filepath,false);

    ui->startSlider->setMaximum(m_player->duration());
    ui->stopSlider->setMaximum(m_player->duration());
    ui->stopSlider->setValue(m_player->duration());

    ui->timeStop->setTime(QTime(0,0).addMSecs(m_player->duration()));
    ui->timeStop->setMaximumTime(QTime(0,0).addMSecs(m_player->duration()));

    ui->timeStart->setMaximumTime(QTime(0,0).addMSecs(m_player->duration()));

    ui->timeSlider->setMaximum(m_player->duration());
    // HorizontalSlider for x264 quality setting initialization
    ui->horizontalSlider_VideoQuality->setMaximum(51);
    ui->horizontalSlider_VideoQuality->setMinimum(0);
    ui->horizontalSlider_VideoQuality->setValue(0);
    // QpinBox for x264 quality setting initialization
    ui->spinBox_Quality->setMaximum(51);
    ui->spinBox_Quality->setMinimum(0);
    ui->spinBox_Quality->setValue(0);

    this->connectPlayer();
}

void VideoPane::initVideoLists() {
    initVideoCodecList();
    initVideoLanguageList();
    initVideoResolutionList();
    initVideoScaleList();
    initVideoBlackStuffList();
    initVideoFramePerSecondList();
    initVideoFilterList();
    initVideox264PresetList();
    initVideox264TuneList();
    initVideox264ProfileList();
    initVideox264LevelList();
}

void VideoPane::initVideoCodecList() {
    m_codecMap.insert( tr( "H264 (Recommandé)" ), "h264" );
    m_codecMap.insert( tr( "VP8" ), "vp8" );

    ui->comboBox_Codec->clear();
    ui->comboBox_Codec->insertItems(0,m_codecMap.keys());
}

void VideoPane::initVideoLanguageList() {
    m_languageMap.insert( tr( "Allemand" ), "ger" );
    m_languageMap.insert( tr( "Anglais" ), "eng" );
    m_languageMap.insert( tr( "Français" ), "fre" );
    m_languageMap.insert( tr( "Espagnol" ), "spa" );
    m_languageMap.insert( tr( "Italien" ), "ita" );

    ui->comboBox_Langage->clear();
    ui->comboBox_Langage->insertItems( 0, m_languageMap.keys() );
}

void VideoPane::initVideoResolutionList() {
    m_resolutionMap.insert( tr( "1080p (1920 x 1080)" ), "1920x1080" );
    m_resolutionMap.insert( tr( "720p (1280 x 720)" ), "1280x720" );
    m_resolutionMap.insert( tr( "480p (854 x 480)" ), "854x480" );

    ui->comboBox_VideoSize->clear();
    ui->comboBox_VideoSize->insertItems( 0, m_resolutionMap.keys() );
}

void VideoPane::initVideoScaleList() {
    m_scaleMap.insert( tr("1:1"), "1:1");
    m_scaleMap.insert( tr("4:3"), "4:3");
    m_scaleMap.insert( tr("16:9"), "16:9");

    ui->comboBox_Scale->clear();
    ui->comboBox_Scale->insertItems(0,m_scaleMap.keys());
}

void VideoPane::initVideoBlackStuffList() {
    m_blackStuffMap.insert( tr( "Oui" ), "1" );
    m_blackStuffMap.insert( tr( "Non" ), "0" );

    ui->comboBox_BlackStuff->clear();
    ui->comboBox_BlackStuff->insertItems( 0, m_blackStuffMap.keys() );
}

void VideoPane::initVideoFramePerSecondList() {
    m_framePerSecondMap.insert( tr( "30" ), "30" );
    m_framePerSecondMap.insert( tr( "25" ), "25" );
    m_framePerSecondMap.insert( tr( "24" ), "24" );
    m_framePerSecondMap.insert( tr( "20" ), "20" );

    ui->comboBox_Frames->clear();
    ui->comboBox_Frames->insertItems( 0, m_framePerSecondMap.keys() );
}

void VideoPane::initVideoFilterList() {
    m_filterMap.insert(tr("Desentrelacement"),"yadif");
    m_filterMap.insert(tr("None"),"");

    ui->comboBox_Filter->clear();
    ui->comboBox_Filter->insertItems(0,m_filterMap.keys());
    ui->comboBox_Filter->setCurrentText(tr("None"));
}

void VideoPane::initVideox264PresetList() {
    m_x264PresetMap.insert( tr( "Ultrafast" ), "ultrafast" );
    m_x264PresetMap.insert( tr( "Super fast" ), "superfast" );
    m_x264PresetMap.insert( tr( "Very fast" ), "veryfast" );
    m_x264PresetMap.insert( tr( "Faster" ), "faster" );
    m_x264PresetMap.insert( tr( "Fast" ), "fast" );
    m_x264PresetMap.insert( tr( "Medium" ), "medium" );
    m_x264PresetMap.insert( tr( "Slow" ), "slow" );
    m_x264PresetMap.insert( tr( "Slower" ), "Very slow" );
    m_x264PresetMap.insert( tr( "Very slow" ), "veryslow" );
    m_x264PresetMap.insert( tr( "Placebo" ), "placebo" );

    ui->comboBox_x264Preset->clear();
    ui->comboBox_x264Preset->insertItems( 0, m_x264PresetMap.keys() );
}

void VideoPane::initVideox264TuneList() {
    m_x264TuneMap.insert( tr( "None" ), "none" );
    m_x264TuneMap.insert( tr( "Film" ), "film" );
    m_x264TuneMap.insert( tr( "Animation" ), "animation" );
    m_x264TuneMap.insert( tr( "Grain" ), "grain" );
    m_x264TuneMap.insert( tr( "Still image" ), "stillimage" );
    m_x264TuneMap.insert( tr( "PSNR" ), "psnr" );
    m_x264TuneMap.insert( tr( "SSIM" ), "ssim" );
    m_x264TuneMap.insert( tr( "FastDecode" ), "fastdecode" );

    ui->comboBox_x264Tune->clear();
    ui->comboBox_x264Tune->insertItems( 0, m_x264TuneMap.keys() );
}

void VideoPane::initVideox264ProfileList() {
    m_x264ProfileMap.insert( tr( "Auto" ), "auto" );
    m_x264ProfileMap.insert( tr( "Baseline" ), "baseline" );
    m_x264ProfileMap.insert( tr( "Main" ), "main" );
    m_x264ProfileMap.insert( tr( "High" ), "high" );

    ui->comboBox_x264Profile->clear();
    ui->comboBox_x264Profile->insertItems( 0, m_x264ProfileMap.keys() );
}

void VideoPane::initVideox264LevelList() {
    m_x264LevelMap.insert( tr( "Auto" ), "auto" );
    m_x264LevelMap.insert( tr( "1.0" ), "1.0" );
    m_x264LevelMap.insert( tr( "1b" ), "1b" );
    m_x264LevelMap.insert( tr( "1.1" ), "1.1" );
    m_x264LevelMap.insert( tr( "1.2" ), "1.2" );
    m_x264LevelMap.insert( tr( "1.3" ), "1.3" );
    m_x264LevelMap.insert( tr( "2.0" ), "2.0" );
    m_x264LevelMap.insert( tr( "2.1" ), "2.1" );
    m_x264LevelMap.insert( tr( "2.2" ), "2.2" );
    m_x264LevelMap.insert( tr( "3.0" ), "3.0" );
    m_x264LevelMap.insert( tr( "3.1" ), "3.1" );
    m_x264LevelMap.insert( tr( "3.2" ), "3.2" );
    m_x264LevelMap.insert( tr( "4.0" ), "4.0" );
    m_x264LevelMap.insert( tr( "4.1" ), "4.1" );
    m_x264LevelMap.insert( tr( "4.2" ), "4.2" );
    m_x264LevelMap.insert( tr( "5.0" ), "5.0" );
    m_x264LevelMap.insert( tr( "5.1" ), "5.1" );
    m_x264LevelMap.insert( tr( "5.2" ), "5.2" );

    ui->comboBox_x264Level->clear();
    ui->comboBox_x264Level->insertItems( 0, m_x264LevelMap.keys() );
}

void VideoPane::updateSlider()
{
    ui->timeSlider->setRange(0, int(m_player->duration()/1000LL));
    ui->timeSlider->setValue(int(m_player->position()/1000LL));
    ui->timeLabel->setText(QTime(0,0).addMSecs(m_player->position()).toString("hh:mm:ss"));
}

// ========================================================================== //
// == EVENT AND SIGNALS METHODS ============================================= //
// ========================================================================== //
void VideoPane::connectPlayer() {
    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(stopped()), SLOT(on_stopButton_clicked()));
}

void VideoPane::initPane()
{

    int ixd ;
    Model::Parameter *p = m_stream->getParameters()->value(Model::Stream::CODEC_NAME);
    if(p){
        QString codec = p->value();
        ixd = ui->comboBox_Codec->findText(m_codecMap.key(codec),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Codec->setCurrentIndex(ixd);
        else{
            ui->comboBox_Codec->insertItem(0,codec);
            ui->comboBox_Codec->setCurrentIndex(0);
        }
        ui->labelCodec->setText(tr("Original: ") + codec);
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
    p = m_stream->getParameters()->value(Model::Stream::DEFAULT);
    if(p){
        QString defaut = p->value();
        if (defaut == "1")
            ui->checkBoxDefaultStream->setChecked(true);
        else
            ui->checkBoxDefaultStream->setChecked(false);
    }
    else
        ui->checkBoxDefaultStream->setChecked(false);

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::RESOLUTION);
    if(p){
        QString scale = p->value().remove("scale=");
        ixd = ui->comboBox_VideoSize->findText(m_resolutionMap.key(scale),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_VideoSize->setCurrentIndex(ixd);
        else{
            ui->comboBox_VideoSize->insertItem(0,scale);
            ui->comboBox_VideoSize->setCurrentIndex(0);
        }
        ui->labelSize->setText(tr("Original: ") + scale);
    }
    else{
        ui->comboBox_VideoSize->insertItem(0,"");
        ui->comboBox_VideoSize->setCurrentIndex(0);
    }

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::VIDEO_FRAME_RATE);
    if(p){
        QString fps = p->value().remove("scale=");
        ixd = ui->comboBox_Frames->findText(m_framePerSecondMap.key(fps),Qt::MatchExactly);
        if(ixd != -1)
            ui->comboBox_Frames->setCurrentIndex(ixd);
        else{
            ui->comboBox_Frames->insertItem(0,fps);
            ui->comboBox_Frames->setCurrentIndex(0);
        }
        ui->labelFPS->setText(tr("Original: ") + fps);
    }
    else{
        ui->comboBox_Frames->insertItem(0,"");
        ui->comboBox_Frames->setCurrentIndex(0);
    }

    p = NULL;
    p = m_stream->getParameters()->value(Model::Stream::VIDEO_AVG_BIT_RATE);
    if(p){
        QString avgBitRate = p->value().remove("-b:v").remove("-bufsize").split(" ").at(1);
        ui->lineEdit_AverageBitrate->setText(avgBitRate);
    }

    QString name = m_stream->name();
    ui->lineEdit_TrackName->setText(name);

}

void VideoPane::applyReco()
{
    if(this->m_dispatcher->getOCPMValidation()->isExist()){
        QString codec= this->m_dispatcher->getOCPMValidation()->recommendedVideoCodec();
        QString rate= this->m_dispatcher->getOCPMValidation()->recommendedVideoMaxRate();
        QString resolution= this->m_dispatcher->getOCPMValidation()->recommendedVideoResolution();

        int ixd = ui->comboBox_Codec->findText(m_codecMap.key(codec),Qt::MatchExactly);
        if(ixd != -1){
            ui->comboBox_Codec->setCurrentIndex(ixd);
            emit(on_comboBox_Codec_activated(m_codecMap.key(codec)));
        }

        ui->lineEdit_AverageBitrate->setText(rate);
        emit(on_lineEdit_AverageBitrate_textChanged(rate));

        ixd = ui->comboBox_VideoSize->findText(m_resolutionMap.key(resolution),Qt::MatchExactly);
        if(ixd != -1){
            ui->comboBox_VideoSize->setCurrentIndex(ixd);
            emit(on_comboBox_VideoSize_activated(m_resolutionMap.key(resolution)));
        }
    }
}


void VideoPane::connectInterface() {
    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(stopped()), SLOT(on_stopButton_clicked()));

    connect( this, SIGNAL( videoParameterChanged( Model::File *, Model::Stream *, QString, QString ) ),
             m_dispatcher, SLOT( parameterChanged( Model::File *, Model::Stream *, QString, QString ) ) );
    connect( this, SIGNAL( deleteVideoParameter( Model::File *, Model::Stream *, QString ) ),
             m_dispatcher, SLOT( deleteParameter( Model::File *, Model::Stream *, QString ) ) );
}



void VideoPane::on_playButton_clicked()
{

    m_player->setStartPosition(ui->startSlider->value());
    m_player->setStopPosition(ui->stopSlider->value());

    if(!m_player->isPlaying()){
        m_player->play();
        if(m_player->isPlaying())
            ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else if(m_player->isPaused()){
        m_player->pause(false);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_pause.png"));
    }else{
        m_player->pause(true);
        ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    }
}

void VideoPane::on_stopButton_clicked()
{
    if(m_player->isPlaying()){
        m_player->stop();
    }
    ui->playButton->setIcon(QIcon(":/icons/resources/icons/icon_play.png"));
    ui->timeSlider->setValue(0);
    ui->timeLabel->setText(QTime(0,0).toString("hh:mm:ss"));
}

void VideoPane::on_stopSlider_sliderMoved(int position)
{
    if(position>ui->startSlider->value()){
        m_player->setStopPosition(qint64(position));
        ui->timeStop->setTime(QTime(0,0).addMSecs(position));
    }else{
        ui->stopSlider->setValue(ui->startSlider->value());
    }
}

void VideoPane::on_startSlider_sliderMoved(int position)
{
    if(position<ui->stopSlider->value()){
        m_player->setStartPosition(qint64(position));
        ui->timeStart->setTime(QTime(0,0).addMSecs(position));
    }else{
        ui->startSlider->setValue(ui->stopSlider->value());
    }
}

void VideoPane::on_timeStart_timeChanged(const QTime &time)
{
    ui->startSlider->setValue(QTime(0,0).msecsTo(time));
}

void VideoPane::on_timeStop_timeChanged(const QTime &time)
{
    ui->stopSlider->setValue(QTime(0,0).msecsTo(time));
}

void VideoPane::on_horizontalSlider_VideoQuality_valueChanged() {
    ui->spinBox_Quality->setValue(ui->horizontalSlider_VideoQuality->value());
}

void VideoPane::on_spinBox_Quality_valueChanged(int value) {
    ui->horizontalSlider_VideoQuality->setValue( value );
}

void VideoPane::on_lineEdit_TrackName_textChanged(const QString &name) {
    this->m_stream->setName( name );
}

void VideoPane::on_comboBox_Codec_activated( QString codec ) {
    // if the codec selected is the x264 codec, show the groupBox settings
    // associated to the x264 codec.
    if ( m_codecMap.value(codec).compare("h264") == 0 ) {
        ui->groupBox_x264Settings->show();
        emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_QUALITY, QString::number(ui->spinBox_Quality->value()));
    } else {
        ui->groupBox_x264Settings->hide();
        emit deleteVideoParameter(m_file,m_stream,Model::Stream::VIDEO_H264_QUALITY);
        emit deleteVideoParameter(m_file,m_stream,Model::Stream::VIDEO_H264_BASELINE);
        emit deleteVideoParameter(m_file,m_stream,Model::Stream::VIDEO_H264_LEVEL);
        emit deleteVideoParameter(m_file,m_stream,Model::Stream::VIDEO_H264_PRESET);
        emit deleteVideoParameter(m_file,m_stream,Model::Stream::VIDEO_H264_TUNE);
    }
    emit videoParameterChanged(m_file, m_stream, Model::Stream::CODEC_NAME, m_codecMap.value(codec));
}

void VideoPane::on_comboBox_Langage_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::LANGUAGE, m_languageMap.value(arg));
}

void VideoPane::on_checkBoxDefaultStream_clicked(bool checked)
{
    QString arg = checked ? "1" : "0";
    emit videoParameterChanged(m_file, m_stream, Model::Stream::DEFAULT, arg);
}

void VideoPane::on_comboBox_VideoSize_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::RESOLUTION, m_resolutionMap.value(arg));
}

void VideoPane::on_comboBox_Scale_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_SCALE, m_scaleMap.value(arg));
    QStringList list = arg.split(":");
    if(list.size()==2){
        m_player->renderer()->setOutAspectRatioMode(QtAV::VideoRenderer::CustomAspectRation );
        m_player->renderer()->setOutAspectRatio((list.at(0).toFloat() / list.at(1).toFloat()));
    }
}

void VideoPane::on_comboBox_BlackStuff_activated(const QString &arg) {
    // TODO:
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_Frames_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_FRAME_RATE, arg);
}

void VideoPane::on_comboBox_Filter_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_DEINTERLACE , m_filterMap.value(arg));
}

void VideoPane::on_lineEdit_OptionsFfmpeg_textChanged(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::EXTRA_CMD , arg);
}

void VideoPane::on_spinBox_Quality_valueChanged(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_QUALITY , arg);
}

void VideoPane::on_lineEdit_AverageBitrate_textChanged(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_AVG_BIT_RATE, arg);
}

void VideoPane::on_checkBoxEncodage_clicked( bool checked ) {
    QString arg = "";
    arg = checked ? "TRUE" : "FALSE";
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_checkBoxTurbo_clicked( bool checked ) {
    QString arg = "";
    arg = checked ? "TRUE" : "FALSE";
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_x264Preset_activated( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_PRESET , m_x264PresetMap.value(arg));
}

void VideoPane::on_comboBox_x264Tune_activated( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_TUNE , m_x264TuneMap.value(arg));
}

void VideoPane::on_comboBox_x264Profile_activated( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_BASELINE , m_x264ProfileMap.value(arg));
}

void VideoPane::on_comboBox_x264Level_activated( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_H264_LEVEL , m_x264LevelMap.value(arg));
}

void VideoPane::on_spinTop_valueChanged( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , getCropValue());
}

void VideoPane::on_spinLeft_valueChanged( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , getCropValue());
}

void VideoPane::on_spinRight_valueChanged( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , getCropValue());
}

void VideoPane::on_spinBot_valueChanged( const QString &arg ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , getCropValue());
}

void VideoPane::on_timeStart_dateTimeChanged( const QDateTime &dateTime ) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_START_TIME, dateTime.toString("hh:mm:ss.z"));
    on_timeStop_dateTimeChanged(ui->timeStop->dateTime());
}

void VideoPane::on_timeStop_dateTimeChanged( const QDateTime &dateTime ) {
    QDateTime final = dateTime;
    final = final.addMSecs(-ui->timeStart->time().msec());
    final = final.addSecs(-ui->timeStart->time().second());
    final = final.addSecs(-(ui->timeStart->time().minute()*60));
    final = final.addSecs(-(ui->timeStart->time().hour()*60*60));
    qDebug() << final.toString("hh:mm:ss.z");
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_STOP_POINT , final.toString("hh:mm:ss.z"));
}

QString VideoPane::getCropValue() {
    QString resolution = m_stream->getParameters()->value(Model::Stream::RESOLUTION)->value();
    QString width = resolution.split("x").at(0);
    QString height = resolution.split("x").at(1);

    width = width.remove("scale=");

    width = QString::number((width.toInt() - ui->spinLeft->value()) - ui->spinRight->value());
    height = QString::number((height.toInt() - ui->spinTop->value()) - ui->spinBot->value());

    m_player->renderer()->setRegionOfInterest(ui->spinLeft->text().toInt(),ui->spinTop->text().toInt(),width.toInt(),height.toInt());

    return (width + ":" + height + ":" + ui->spinLeft->text() + ":" + ui->spinTop->text());
}

void VideoPane::on_loadFileStream_clicked()
{
    if(!m_player->isLoaded()){
        this->loadFile(m_file->getOriginalFilePath());
        m_player->setVideoStream(this->m_streamId);
    }
    ui->videoButtons->setEnabled(true);
}
