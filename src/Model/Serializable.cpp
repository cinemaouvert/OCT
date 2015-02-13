#include "Attachment.h"
#include "Audio.h"
#include "Parameter.h"
#include "File.h"
#include "StreamWrapper.h"
#include "Subtitle.h"
#include "Video.h"
#include "Project.h"
#include "Serializable.h"



void Model::Serializable::initMetaTypes()
{
    Model::Attachment::initMetaType();
    Model::Audio::initMetaType();
    Model::Parameter::initMetaType();
    Model::File::initMetaType();
    Model::StreamWrapper::initMetaType();
    Model::Subtitle::initMetaType();
    Model::Video::initMetaType();
    Model::Project::initMetaType();
}


