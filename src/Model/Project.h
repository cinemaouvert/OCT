/**********************************************************************************
 * This file is part of Open Cinema Transcoder (OCT).
 *
 * Copyright (C) 2014 Catalogue Ouvert du Cinéma <dev@cinemaouvert.fr>
 *
 * Authors: Romain Boutin <romain.boutin@etu.univ-poitiers.fr>
 *          Thibaud Lamarche <lamarchethibaud@hotmail.com>
 *          William Le Coroller <william.le.coroller@gmail.com>
 *          Denis Saunier <saunier.denis.86@gmail.com>
 *
 * Open Cinema Transcoder is an initiative of Catalogue Ouvert du Cinéma.
 * The software was developed by four students of University of Poitiers
 * as school project.
 *
 * Open Cinema Transcoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Cinema Transcoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open Cinema Transcoder. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************/

#include <exception>
using namespace std;

#ifndef __Model__Project_h__
#define __Model__Project_h__

#include <QString>
#include <QList>

// #include "src/Model/Attachment.h"
#include "src/Model/Serializable.h"
#include "src/Model/File.h"

namespace Model
{
	class Attachment;
	// class Serializable;
	class Project;
    class File;
}

namespace Model
{
    /**
     * @brief The Project model class.
     */
    class Project
	{
        private:

            friend QDataStream & operator >>(QDataStream  &in, Project  &valeur);
            friend QDataStream & operator <<(QDataStream  &out, const Project  &valeur);

            /**
             * @brief Project name.
             */
            QString m_name;

            /**
             * @brief Path to the XML file.
             */
            QString m_xmlFilePath;

            /**
             * @brief Path to the torrent software.
             */
            QString m_torrentSoftwarePath;

            /**
             * @brief Define whether or not a magnet link is to be created.
             */
            bool m_createMagnet;

            /**
             * @brief List of Attachement associated with the current Project object.
             */
            QList<Model::Attachment*> *m_attachments;

            /**
             * @brief List of Information associated with the current Project object.
             */
            //QList<Model::Information*> *m_informations;
            QMap<QString, QString> *m_informations;

            /**
             * @brief List of File associated with the current Project object.
             */
            QList<Model::File*> *m_fileList;

            QString m_userKey;
            QString m_depot;
            QString m_affiche;
            QString m_capture;

        public:
            /**
             * @brief Default constructor.
             */
            Project();

            /**
             * @brief Copy constructor.
             * @param project Project object to copy.
             */
            Project(const Project &project);

            /**
             * @brief Affectation operator.
             * @param project Project object to be affected.
             * @return The current Project object modified.
             */
            Project & operator=(const Project &project);

            /**
             * @brief Destructor.
             */
            virtual ~Project();

            /**
             * @brief Accessor on the name member.
             * @return The name member.
             */
            QString name() const;

            /**
             * @brief Mutator on the member name.
             * @param name The name to replace the current name member value.
             */
            void setName(const QString &name);

            /**
             * @brief Accessor on the file list member.
             * @return The file list member pointer value.
             */
            QList<Model::File *> *fileList() const;

            /**
             * @brief This method add a file to the current file list member.
             * @param file The file list to add.
             */
            void addFileToList(Model::File *file);


            /**
             * @brief Accessor on the information list member.
             * @return The information list member pointer value.
             */
            QMap<QString, QString> *informations() const;

            /**
             * @brief This method add an information list to the current information list member.
             * @param information The information list to add.
             */
            void addInformations(QString key, QString value);

            /**
             * @brief Accessor on the create magnet boolean member.
             * @return The create magnet member value.
             */
            bool createMagnet() const;

            /**
             * @brief Mutator on the create magnet value member.
             * @param createMagnet The value to replace the create magnet value member.
             */
            void setCreateMagnet(bool createMagnet);

            /**
             * @brief Accessor on the Attachement list member.
             * @return The Attachement list member pointer value.
             */
            QList<Model::Attachment *> *attachments() const;

            /**
             * @brief This method add an Attachement to the current Attchement list member.
             * @param attachment The Attachement to add.
             */
            void addAttachment(Model::Attachment *attachment);

            /**
             * @brief remove a file to the current project.
             * @param filePath
             */
            void removeFile(QString filePath);

            /**
             * @brief Accessor on the path of the XML file.
             * @return The XML file path value member.
             */
            QString xmlFilePath() const;

            /**
             * @brief Mutator on the path of the XML file.
             * @param xmlFilePath New XML file path to replace the current one.
             */
            void setXmlFilePath(const QString &xmlFilePath);

            /**
             * @brief Accessor on the path of the torrent software.
             * @return The torrent software path value member.
             */
            QString getTorrentSoftwarePath() const;

            /**
             * @brief Mutator on the path of the torrent software.
             * @param xmlFilePath New torrent software path to replace the current one.
             */
            void setTorrentSoftwarePath(const QString &torrentSoftwarePath);

            QString generateInformationToXML();
            /**
             * @brief getMergeCommandLine generate the command line
             * @return the arguments of the command line
             */
            QStringList *getMergeCommandLine();

            /**
             * @brief Accessor number of video stream.
             * @return The number of video stream.
             */
            int nbVideo() const;

            /**
             * @brief Accessor number of audio stream.
             * @return The number of audio stream.
             */
            int nbAudio() const;

            /**
             * @brief Accessor number of subtitle stream.
             * @return The number of subtitle stream.
             */
            int nbSub() const;
            /**
             * @brief remove information to the current project.
             * @param key
             */
            void removeInformations(QString key);
            QString depot() const;
            void setDepot(const QString &depot);
            QString userKey() const;
            void setUserKey(const QString &userKey);

            static void initMetaType();
            QString capture() const;
            void setCapture(const QString &capture);
            QString affiche() const;
            void setAffiche(const QString &affiche);
    };
    QDataStream & operator <<(QDataStream  &out, const Model::Project  &valeur);
    QDataStream & operator >>(QDataStream  &in, Model::Project &valeur);

}
Q_DECLARE_METATYPE(Model::Project)


#endif
