#include <exception>

using namespace std;

#ifndef __Controller__Transcoder_h__
#define __Controller__Transcoder_h__


#include <QString>
#include <QSettings>

// #include "src/Controller/OCTDispatcher.h"

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
             * @brief Default constructor.
             */
            Transcoder();

            ~Transcoder();

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
            QString transcode(QStringList *list);

        private:
            /**
             * @brief The associated settings.
             */
            QSettings                   *m_settings;
	};
}

#endif
