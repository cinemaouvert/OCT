#ifndef __MODEL__OCPMVALIDATION_H
#define __MODEL__OCPMVALIDATION_H

#include <QObject>
#include <QFile>
#include <qstringlist.h>

namespace Model{
    class OCPMValidation;
    class Stream;
}
namespace Model{
    class OCPMValidation : public QObject
    {
        Q_OBJECT
        public:
            explicit OCPMValidation(QObject *parent = 0);
            void loadPreConfXML(QFile *file);
            void loadValidationXML(QFile *file);

            bool isValidVideo(Stream *stream);
            bool isValidAudio(Stream *stream);
            bool isValidSubtitle(Stream *stream);

        signals:

        public slots:

        private:
            QString m_recommendedVideoCodec;
            QString m_recommendedVideoMaxRate;
            QString m_recommendedVideoResolution;

            QString m_recommendedAudioCodec;
            QString m_recommendedAudioChanel;
            QString m_recommendedAudioSamplingRate;

            QString m_recommendedSubtitleFormat;
            QString m_recommendedSubtitleEncoding;


            QStringList m_validationVideoCodec;
            QStringList m_validationVideoMaxRate;
            QStringList m_validationVideoResolution;
            QStringList m_validationAudioCodec;
            QStringList m_validationAudioChanel;
            QStringList m_validationAudioSamplingRate;
            QStringList m_validationSubtitleFormat;
            QStringList m_validationSubtitleEncoding;

    };
}
#endif // __MODEL__OCPMVALIDATION_H
