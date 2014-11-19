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
    Parameter *codecNameParam = new Parameter("-vcodec ","This is the codec of the video stream","");
    Parameters::m_videoParameters.insert("codec_name",codecNameParam);

    Parameter *language = new Parameter("-metadata:s:v:%1 language=","This is the language of the stream","");
    Parameters::m_videoParameters.insert("language",language);

    Parameter *isDefault = new Parameter("-metadata:s:v:#UID# default-flag=","This indicates if the stream is tagged as the default one","1");
    Parameters::m_videoParameters.insert("default",isDefault);

    Parameter *resolution = new Parameter("-vf scale=","This is the resolution of the video stream (AAAxBBB)","");
    resolution->SetNoSpaceForNext();
    Parameters::m_videoParameters.insert("resolution",resolution);

    Parameter *forceAspect = new Parameter("force_original_aspect_ratio=","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","");
    Parameters::m_videoParameters.insert("forceAspect",forceAspect);

    Parameter *frameRate = new Parameter("-r ","This is the frame rate (in frame by second)","24");
    Parameters::m_videoParameters.insert("r_frame_rate",frameRate);

    /**** AUDIO PARAMETERS ****/



    /**** SUBTITLE PARAMETERS ***/


}
