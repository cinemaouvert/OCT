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
    /**
     * @brief The OCPMValidation model class
     */
    class OCPMValidation : public QObject
    {
        Q_OBJECT
        public:
            /**
             * @brief Constructor.
             * @param parent The associated parent.
             */
            explicit OCPMValidation(QObject *parent = 0);

            /**
             * @brief This method loads the XML pre-configuration.
             * @param file The XML file to load the pre-configuration from.
             */
            void loadPreConfXML(QFile *file);

            /**
             * @brief This method loads the validation from an XML file.
             * @param file The XML file to load the validation from.
             */
            void loadValidationXML(QFile *file);

            /**
             * @brief This method returns if a given video stream is valid or not.
             * @param stream The input video stream to check.
             * @return True if the video stream is value, False else.
             */
            bool isValidVideo(Stream *stream);

            /**
             * @brief This method returns if a given audio stream is valid or not.
             * @param stream The input audio stream to check.
             * @return True if the audio stream is value, False else.
             */
            bool isValidAudio(Stream *stream);

            /**
             * @brief This method returns if a given subtitle stream is valid or not.
             * @param stream The input subtitle stream to check.
             * @return True if the subtitle stream is value, False else.
             */
            bool isValidSubtitle(Stream *stream);

            /**
             * @brief Accessor on the recommended video codec member.
             * @return The recommended video codec member.
             */
            QString recommendedVideoCodec() const;

            /**
             * @brief Mutator on the recommended video codec member.
             * @param recommendedVideoCodec The recommended video codec to remplace
             * the current member.
             */
            void setRecommendedVideoCodec(const QString &recommendedVideoCodec);

            /**
             * @brief Accessor on the recommended video max rate member.
             * @return The recommended video max rate member.
             */
            QString recommendedVideoMaxRate() const;

            /**
             * @brief Mutator on the recommended video max rate member.
             * @param recommendedVideoMaxRate The recommended video max rate member
             * to remplace the current member.
             */
            void setRecommendedVideoMaxRate(const QString &recommendedVideoMaxRate);

            /**
             * @brief Accessor on the recommended video resolution member.
             * @return The recommended video resolution member.
             */
            QString recommendedVideoResolution() const;

            /**
             * @brief Mutator on the recommended video resolution member.
             * @param recommendedVideoResolution The recommended video resolution
             * to remplace the current member.
             */
            void setRecommendedVideoResolution(const QString &recommendedVideoResolution);

            /**
             * @brief Accessor on the recommended audio codec member.
             * @return The recommended audio codec member.
             */
            QString recommendedAudioCodec() const;

            /**
             * @brief Mutator on the recommended audio codec member.
             * @param recommendedAudioCodec The recommended audio codec to
             * remplace the current member.
             */
            void setRecommendedAudioCodec(const QString &recommendedAudioCodec);

            /**
             * @brief Accessor on the recommended audio channel member.
             * @return The recommended audio channel member.
             */
            QString recommendedAudioChanel() const;

            /**
             * @brief Mutator on the recommended audio channel member.
             * @param recommendedAudioChanel The recommended audio channel
             * to remplace the current member.
             */
            void setRecommendedAudioChanel(const QString &recommendedAudioChanel);

            /**
             * @brief Accessor on the recommended audio sampling rate member.
             * @return The recommended audio sampling rate member.
             */
            QString recommendedAudioSamplingRate() const;

            /**
             * @brief Mutator on the recommended audio sampling rate member.
             * @param recommendedAudioSamplingRate The recommended audio sampling
             * rate to remplace the current member.
             */
            void setRecommendedAudioSamplingRate(const QString &recommendedAudioSamplingRate);

            /**
             * @brief Accessor on the recommended subtitle format member.
             * @return The recommended subtitle format member.
             */
            QString recommendedSubtitleFormat() const;

            /**
             * @brief Mutator on the recommended subtitle format member.
             * @param recommendedSubtitleFormat The recommended subtitle format
             * to remplace the current member.
             */
            void setRecommendedSubtitleFormat(const QString &recommendedSubtitleFormat);

            /**
             * @brief Accessor on the recommended subtitle encoding member.
             * @return The recommended subtitle encoding member.
             */
            QString recommendedSubtitleEncoding() const;

            /**
             * @brief Mutator on the recommended subtitle encoding member.
             * @param recommendedSubtitleEncoding The recommended subtitle
             * encoding to remplace the current member.
             */
            void setRecommendedSubtitleEncoding(const QString &recommendedSubtitleEncoding);

            /**
             * @brief Accessor on the exist boolean member.
             * @return The exist boolean member.
             */
            bool isExist() const;

            /**
             * @brief Mutator on the exist boolean member.
             * @param value The value to remplace the current exist member.
             */
            void setExist(bool value);

    signals:

    public slots:

    private:
            /**
             * @brief A QString representing the recommended video codec
             * associated with the OCMP recommendation.
             */
            QString m_recommendedVideoCodec;

            /**
             * @brief A QString representing the recommended video max rate
             * associated with the OCMP recommendation.
             */
            QString m_recommendedVideoMaxRate;

            /**
             * @brief A QString representing the recommended video resolution
             * associated with the OCMP recommendation.
             */
            QString m_recommendedVideoResolution;

            /**
             * @brief A QString representing the recommended audio codec
             * associated with the OCMP recommendation.
             */
            QString m_recommendedAudioCodec;

            /**
             * @brief A QString representing the recommended audio channel
             * associated with the OCMP recommendation.
             */
            QString m_recommendedAudioChanel;

            /**
             * @brief A QString representing the recommended audio sampling rate
             * associated with the OCMP recommendation.
             */
            QString m_recommendedAudioSamplingRate;

            /**
             * @brief A QString representing the recommended subtitle format
             * associated with the OCMP recommendation.
             */
            QString m_recommendedSubtitleFormat;

            /**
             * @brief A QString representing the recommended subtitle encoding
             * associated with the OCMP recommendation.
             */
            QString m_recommendedSubtitleEncoding;

            /**
             * @brief A QStringList representing the validation of the video codec
             * within the OCMP recommendation.
             */
            QStringList m_validationVideoCodec;

            /**
             * @brief A QStringList representing the validation of the video max rate
             * within the OCMP recommendation.
             */
            QStringList m_validationVideoMaxRate;

            /**
             * @brief A QStringList representing the validation of the video resolution
             * within the OCMP recommendation.
             */
            QStringList m_validationVideoResolution;

            /**
             * @brief A QStringList representing the validation of the audio codec
             * within the OCMP recommendation.
             */
            QStringList m_validationAudioCodec;

            /**
             * @brief A QStringList representing the validation of the audio channel
             * within the OCMP recommendation.
             */
            QStringList m_validationAudioChanel;

            /**
             * @brief A QStringList representing the validation of the audio sampling rate
             * within the OCMP recommendation.
             */
            QStringList m_validationAudioSamplingRate;

            /**
             * @brief A QStringList representing the validation of the subtitle format
             * within the OCMP recommendation.
             */
            QStringList m_validationSubtitleFormat;

            /**
             * @brief A QStringList representing the validation of the subtitle encoding
             * within the OCMP recommendation.
             */
            QStringList m_validationSubtitleEncoding;

            /**
             * @brief Boolean representing whether or not the recommendation is specified.
             */
            bool exist;
    };
}
#endif // __MODEL__OCPMVALIDATION_H
