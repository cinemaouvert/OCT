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

#ifndef __View__MainWindow_h__
#define __View__MainWindow_h__

// #include "Controller/OCTDispatcher.h"
// #include "View/FilePane.h"

#include <QMainWindow>

namespace Controller
{
	class OCTDispatcher;
}
namespace View
{
	class FilePane;
	class MainWindow;
}
namespace Ui
{
    class MainWindow;
}

namespace View
{
    /**
     * @brief The MainWindow class
     */
    class MainWindow : public QMainWindow
	{
        Q_OBJECT
        public:
            /**
             * @brief The associated FilePane view.
             */
            View::FilePane* m__;

            /**
             * @brief The associated OCTDispatcher.
             */
            Controller::OCTDispatcher* m_unnamed_OCTDispatcher_;

            /**
             * @brief Explicit constructor.
             * @param parent
             * @param dispatcher
             */
            explicit MainWindow(QWidget *parent = 0,Controller::OCTDispatcher *dispatcher = NULL);

            /**
             * @brief Destructeur.
             */
            ~MainWindow();

        private:
            /**
             * @brief MainWindow.
             */
            Ui::MainWindow *ui;

            /**
             * @brief The associated dispatcher.
             */
            Controller::OCTDispatcher *dispatcher;

	};
}

#endif
