#include <exception>

using namespace std;

#ifndef __Controller__Transcoder_h__
#define __Controller__Transcoder_h__


#include <QString>
#include <QSettings>

// #include "Controller/OCTDispatcher.h"

namespace Controller
{
	class OCTDispatcher;
	class Transcoder;
}

namespace Controller
{
	class Transcoder
	{
        public:
            /**
             * @brief The associated transcoder controller.
             */
            Controller::OCTDispatcher* m_transcoder;

            /**
             * @brief Default constructor.
             */
            Transcoder();

            /**
             * @brief This method retrieves informations from a given file.
             * @param filePath to the file.
             * @return
             */
            QString getInfo(QString filePath);

            /**
             * @brief This method transcode from a given command.
             * @param command
             * @return
             */
            QString transcode(QString command);

        private:
            /**
             * @brief The associated settings.
             */
            QSettings                   *m_settings;
	};
}

#endif
