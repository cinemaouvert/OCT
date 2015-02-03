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

            QString recommendedVideoCodec() const;
            void setRecommendedVideoCodec(const QString &recommendedVideoCodec);

            QString recommendedVideoMaxRate() const;
            void setRecommendedVideoMaxRate(const QString &recommendedVideoMaxRate);

            QString recommendedVideoResolution() const;
            void setRecommendedVideoResolution(const QString &recommendedVideoResolution);

            QString recommendedAudioCodec() const;
            void setRecommendedAudioCodec(const QString &recommendedAudioCodec);

            QString recommendedAudioChanel() const;
            void setRecommendedAudioChanel(const QString &recommendedAudioChanel);

            QString recommendedAudioSamplingRate() const;
            void setRecommendedAudioSamplingRate(const QString &recommendedAudioSamplingRate);

            QString recommendedSubtitleFormat() const;
            void setRecommendedSubtitleFormat(const QString &recommendedSubtitleFormat);

            QString recommendedSubtitleEncoding() const;
            void setRecommendedSubtitleEncoding(const QString &recommendedSubtitleEncoding);

            bool isExist() const;
            void setExist(bool value);

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
            bool exist;
    };
}
#endif // __MODEL__OCPMVALIDATION_H
