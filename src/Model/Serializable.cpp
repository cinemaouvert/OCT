#include "Attachment.h"
#include "Audio.h"
#include "Serializable.h"
#include "Parameter.h"



void Model::Serializable::initMetaTypes()
{
    Model::Attachment::initMetaType();
    Model::Audio::initMetaType();
    Model::Parameter::initMetaType();
}


