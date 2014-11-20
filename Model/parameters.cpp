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
    Parameter *v_codecNameParam = new Parameter("-vcodec %1","This is the codec of the video stream","");
    Parameters::m_videoParameters.insert("codec_name",v_codecNameParam);

    Parameter *v_language = new Parameter("-metadata:s:v:%2 language=%1","This is the language of the stream","");
    Parameters::m_videoParameters.insert("language",v_language);

    Parameter *v_isDefault = new Parameter("-metadata:s:v:%2 default-flag=%1","This indicates if the stream is tagged as the default one","1");
    Parameters::m_videoParameters.insert("default",v_isDefault);

    Parameter *v_resolution = new Parameter("-vf scale=%1","This is the resolution of the video stream (AAAxBBB)","");
    v_resolution->SetNoSpaceForNext();
    Parameters::m_videoParameters.insert("resolution",v_resolution);

    Parameter *v_forceAspect = new Parameter("force_original_aspect_ratio=%1","Enable decreasing or increasing output video width or height if necessary to keep the original aspect ratio. Possible values: disable,decrease,increase","");
    Parameters::m_videoParameters.insert("forceAspect",v_forceAspect);

    Parameter *v_frameRate = new Parameter("-r %1","This is the frame rate (in frame by second)","24");
    Parameters::m_videoParameters.insert("r_frame_rate",v_frameRate);

    Parameter *v_averageBitRate= new Parameter("-b:v %1 -bufsize %1","This is the average bit rate (in frame by second)","");
    Parameters::m_videoParameters.insert("sample_rate",v_averageBitRate);

    Parameter *v_filter= new Parameter("-filter:v %1","This is the video filter can be (yadif for deinterlace, ))","");
    Parameters::m_videoParameters.insert("deinterlace",v_filter);


    /**** AUDIO PARAMETERS ****/



    /**** SUBTITLE PARAMETERS ***/


}
