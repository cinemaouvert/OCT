#include "OCPMValidation.h"
#include <QXmlQuery>
#include <QDebug>

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


