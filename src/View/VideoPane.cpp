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
    m_dispatcher(NULL)
{
    ui->setupUi(this);

    m_player = new QtAV::AVPlayer;
    m_player->setRenderer(ui->videoWidget);

    ui->videoWidget->show();
}

VideoPane::VideoPane(Model::File *file,Model::Stream *stream, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPane),
    m_player(NULL),
    m_file(file),
    m_stream(stream)
{
    ui->setupUi(this);

    m_player = new QtAV::AVPlayer;
    m_player->setRenderer(ui->videoWidget);

    ui->videoWidget->show();

    this->loadFile(m_file->getFilePath());
    this->m_streamId = stream->getUID().toInt();
    m_player->setVideoStream(this->m_streamId);
}

void VideoPane::setDispatcher(Controller::OCTDispatcher *dispatcher)
{
    m_dispatcher = dispatcher;
    connectInterface();
}

VideoPane::~VideoPane()
{
    if(ui) delete ui;
    if(m_player) delete m_player;
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

void VideoPane::connectInterface() {
    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(stopped()), SLOT(on_stopButton_clicked()));

    connect( this, SIGNAL( videoParameterChanged( Model::File *, Model::Stream *, QString, QString ) ),
             m_dispatcher, SLOT( parameterChanged( Model::File *, Model::Stream *, QString, QString ) ) );
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
    if ( codec.compare("H264 (x264)") == 0 ) {
        ui->groupBox_x264Settings->show();
    } else {
        ui->groupBox_x264Settings->hide();
    }
    emit videoParameterChanged(m_file, m_stream, Model::Stream::CODEC_NAME, codec);
}

void VideoPane::on_comboBox_Langage_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::LANGUAGE, arg);
}

void VideoPane::on_comboBox_DefaultTrack_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::DEFAULT, arg);
}

void VideoPane::on_comboBox_VideoSize_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::RESOLUTION, arg);
}

void VideoPane::on_comboBox_Scale_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_FORCE_ASPECT, arg);
}

void VideoPane::on_comboBox_BlackStuff_activated(const QString &arg) {
    // TODO:
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_Frames_activated(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_FRAME_RATE, arg);
}

void VideoPane::on_comboBox_Filter_activated(const QString &arg) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_lineEdit_OptionsFfmpeg_textChanged(const QString &arg) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_spinBox_Quality_valueChanged(const QString &arg) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_lineEdit_AverageBitrate_textChanged(const QString &arg) {
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_AVG_BIT_RATE, arg);
}

void VideoPane::on_checkBox_clicked( bool checked ) {
    QString arg = "";
    checked ? arg = "TRUE" : "FALSE";
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_checkBox_2_clicked( bool checked ) {
    QString arg = "";
    checked ? arg = "TRUE" : "FALSE";
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_x264Preset_activated( const QString &arg ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_x264Tune_activated( const QString &arg ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_x264Profile_activated( const QString &arg ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_comboBox_x264Level_activated( const QString &arg ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_spinTop_valueChanged( const QString &arg ) {
    // TODO :
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , arg);
}

void VideoPane::on_spinLeft_valueChanged( const QString &arg ) {
    // TODO :
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , arg);
}

void VideoPane::on_spinRight_valueChanged( const QString &arg ) {
    // TODO :
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , arg);
}

void VideoPane::on_spinBot_valueChanged( const QString &arg ) {
    // TODO :
    emit videoParameterChanged(m_file, m_stream, Model::Stream::VIDEO_CROP , arg);
}

void VideoPane::on_timeStart_dateTimeChanged( const QDateTime &dateTime ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}

void VideoPane::on_timeStop_dateTimeChanged( const QDateTime &dateTime ) {
    // TODO :
    // emit videoParameterChanged(m_file, m_stream, Model::Stream:: _____ , arg);
}
