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

#ifndef __Model__File_h__
#define __Model__File_h__

#include <QString>
#include <QList>
#include <qdom.h>

#include "src/Model/Serializable.h"
#include "src/Model/StreamWrapper.h"
#include "Audio.h"
#include "Video.h"
#include "qdebug.h"

namespace Model
{
	class StreamWrapper;
	class File;
    class Serializable;
    class Parameters;
}

namespace Model
{
    /**
     * @brief The File model class
     */
    class File
	{
        private:

            friend QDataStream & operator >>(QDataStream  &in, File  &valeur);
            friend QDataStream & operator <<(QDataStream  &out, const File  &valeur);

            /**
             * @brief The name of the file.
             */
            QString m_name;

            /**
             * @brief The path to the file.
             */
            QString m_filePath;

            /**
             * @brief The output path to the processed file.
             */
            QString m_outFilePath;

            /**
             * @brief The data contained in the file.
             */
            QList<Model::StreamWrapper*> *m_datas;

            /**
             * @brief The generated video.
             * @param stream Stream associated.
             * @return The corresponding video.
             */
            Video* genereVideo(QDomNode stream);

        public:
            /**
             * @brief Default constructor.
             */
            File();

            /**
             * @brief Constructor
             * @param filePath The path to the file.
             * @param info The complementary information.
             */
            File(QString filePath, QString info);

            /**
             * @brief Copy constructor.
             * @param f The File object to copy
             */
            File(File const& f);

            /**
             * @brief Affectation operator.
             * @param f The File object to be affected.
             * @return The current File object modified.
             */
            File& operator=(File const& f);

            /**
             * @brief Destructor.
             */
            virtual ~File();

            /**
             * @brief Accessor on the data member.
             * @return The data member pointer value.
             */
            QList<Model::StreamWrapper*>* getStreamWrappers();

            /**
             * @brief getCommandLine generate the command line
             * @return the arguments of the command line
             */
            QStringList *getCommandLine();

            /**
             * @brief Accessor on the name member.
             * @return The name member value.
             */
            QString getName();

            /**
             * @brief Accessor on the filePath member.
             * @return The filePath member value.
             */
            QString getFilePath();

            /**
             * @brief Accessor on the datas member.
             * @return The datas member.
             */
            QList<Model::StreamWrapper *> *getDatas() const;

            /**
             * @brief This method returns whether or not the file has to be transcoded.
             * @return Whether or not the file has to be transcoded.
             */
            bool hasToBeTranscoded();

            /**
             * @brief Accessor on the file path member.
             * @return The file path member.
             */
            QString getOriginalFilePath();
            static void initMetaType();
    };

    QDataStream & operator <<(QDataStream  &out, const Model::File  &valeur);
    QDataStream & operator >>(QDataStream  &in, Model::File  &valeur);

}
Q_DECLARE_METATYPE(Model::File)


#endif
