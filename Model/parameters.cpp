#include "parameters.h"

QMap<QString, Model::Parameter *> Model::Parameters::m_videoParameters;
QMap<QString, Model::Parameter *> Model::Parameters::m_audioParameters;
QMap<QString, Model::Parameter *> Model::Parameters::m_subtitleParameters;

Model::Parameter *Model::Parameters::getVideoParameter(QString key)
{
    return Parameters::m_videoParameters.value(key);
}

Model::Parameter *Model::Parameters::getAudioParameter(QString key)
{
    return Parameters::m_audioParameters.value(key);
}

Model::Parameter *Model::Parameters::getSubtitleParameter(QString key)
{
    return Parameters::m_subtitleParameters.value(key);
}

void Model::Parameters::init()
{
    /**** VIDEO PARAMETERS ****/



    /**** AUDIO PARAMETERS ****/



    /**** SUBTITLE PARAMETERS ***/


}
