#include "OCPMValidation.h"
#include <QXmlQuery>
#include <QDebug>
#include "Stream.h"

Model::OCPMValidation::OCPMValidation(QObject *parent) :
    QObject(parent)
{

}

void Model::OCPMValidation::loadValidationXML(QFile *file)
{
    m_validationVideoCodec.clear();
    m_validationVideoMaxRate.clear();
    m_validationVideoResolution.clear();
    m_validationAudioCodec.clear();
    m_validationAudioChanel.clear();
    m_validationAudioSamplingRate.clear();
    m_validationSubtitleFormat.clear();
    m_validationSubtitleEncoding.clear();

    file->open(QFile::ReadOnly);

    QXmlQuery query(QXmlQuery::XQuery10);
    query.setFocus(file);

    query.setQuery("/oct/video/codecs/value/string()");
    query.evaluateTo(&m_validationVideoCodec);

    query.setQuery("/oct/video/maxRate/@value/string()");
    query.evaluateTo(&m_validationVideoMaxRate);

    query.setQuery("/oct/video/resolutions/value/string()");
    query.evaluateTo(&m_validationVideoResolution);

    query.setQuery("/oct/audio/codecs/value/string()");
    query.evaluateTo(&m_validationAudioCodec);

    query.setQuery("/oct/audio/chanels/value/string()");
    query.evaluateTo(&m_validationAudioChanel);

    query.setQuery("/oct/audio/samplingRates/value/string()");
    query.evaluateTo(&m_validationAudioSamplingRate);

    query.setQuery("/oct/subtitle/formats/value/string()");
    query.evaluateTo(&m_validationSubtitleFormat);

    query.setQuery("/oct/subtitle/encodings/value/string()");
    query.evaluateTo(&m_validationSubtitleEncoding);

    file->close();
}


void Model::OCPMValidation::loadPreConfXML(QFile *file)
{
    file->open(QFile::ReadOnly);

    QXmlQuery query(QXmlQuery::XQuery10);
    query.setFocus(file);

    query.setQuery("/oct/video/codecs/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedVideoCodec);
    m_recommendedVideoCodec = m_recommendedVideoCodec.remove("\n");

    query.setQuery("/oct/video/maxRate/@value/string()");
    query.evaluateTo(&m_recommendedVideoMaxRate);
    m_recommendedVideoMaxRate = m_recommendedVideoMaxRate.remove("\n");

    query.setQuery("/oct/video/resolutions/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedVideoResolution);
    m_recommendedVideoResolution = m_recommendedVideoResolution.remove("\n");

    query.setQuery("/oct/audio/codecs/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedAudioCodec);
    m_recommendedAudioCodec = m_recommendedAudioCodec.remove("\n");

    query.setQuery("/oct/audio/chanels/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedAudioChanel);
    m_recommendedAudioChanel = m_recommendedAudioChanel.remove("\n");

    query.setQuery("/oct/audio/samplingRates/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedAudioSamplingRate);
    m_recommendedAudioSamplingRate = m_recommendedAudioSamplingRate.remove("\n");

    query.setQuery("/oct/subtitle/formats/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedSubtitleFormat);
    m_recommendedSubtitleFormat = m_recommendedSubtitleFormat.remove("\n");

    query.setQuery("/oct/subtitle/encodings/value[@preConf='true']/string()");
    query.evaluateTo(&m_recommendedSubtitleEncoding);
    m_recommendedSubtitleEncoding = m_recommendedSubtitleEncoding.remove("\n");

    file->close();
    loadValidationXML(file);
}


bool Model::OCPMValidation::isValidVideo(Model::Stream *stream)
{
    bool retval = true;
    QString codec = stream->getParameters()->value("codec_name")->value();
    retval = retval && m_validationVideoCodec.contains(codec,Qt::CaseInsensitive);

    if(!retval)
        return retval;

    Parameter *bitRateParam = stream->getParameters()->value("bitRate");
    if(!bitRateParam)
        return false;
    QString bitRate = bitRateParam->value().remove(QRegExp("[a-zA-Z:\-]")).split(" ").at(1);
    QString maxBitRate = m_validationVideoMaxRate.at(0);
    retval = retval && (bitRate.toInt() <= maxBitRate.toInt());

    if(!retval)
        return retval;

    QString resolution = stream->getParameters()->value("resolution")->value().remove("scale=");
    retval = retval && m_validationVideoResolution.contains(resolution,Qt::CaseInsensitive);

    return retval;
}

bool Model::OCPMValidation::isValidAudio(Model::Stream *stream)
{
    bool retval = true;

    QString codec = stream->getParameters()->value("codec_name")->value();
    retval = retval && m_validationAudioCodec.contains(codec,Qt::CaseInsensitive);

    QString channels = stream->getParameters()->value("channels")->value();
    retval = retval && m_validationAudioChanel.contains(channels == "1" ? "mono" : "stereo" ,Qt::CaseInsensitive);

    QString samplingRate = stream->getParameters()->value("sample_rate")->value();
    retval = retval && m_validationAudioSamplingRate.contains(samplingRate,Qt::CaseInsensitive);

    return retval;

}

bool Model::OCPMValidation::isValidSubtitle(Model::Stream *stream)
{
    bool retval = true;

    QString codec = stream->getParameters()->value("codec_name")->value();
    retval = retval && m_validationSubtitleFormat.contains(codec,Qt::CaseInsensitive);

    QString encoding = stream->getParameters()->value("charEncode")->value();
    retval = retval && m_validationAudioSamplingRate.contains(encoding,Qt::CaseInsensitive);

    return retval;

}

