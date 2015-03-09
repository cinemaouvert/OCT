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

#ifndef ENCODEPANE_H
#define ENCODEPANE_H

#include <QStringListModel>
#include <QStandardItemModel>
#include <QWidget>

#include "MyDelegate.h"
#include <src/Controller/OCTDispatcher.h>

namespace Ui {
class EncodePane;
}

class EncodePane : public QWidget
{
    Q_OBJECT

public:
    explicit EncodePane(QWidget *parent = 0);
    void setDispatcher(Controller::OCTDispatcher *dispatcher);
    ~EncodePane();

    ///
    /// \brief Refresh the whole view.
    ///
    void refresh();

    ///
    /// \brief Refresh the project pane.
    ///
    void refreshProjectPane();

    void setListViewExport( QStandardItemModel * sim, MyDelegate * md );

    ///
    /// \brief Change the current project.
    /// \param Index of the project in the list to be changed.
    ///
    void changeCurrentProject(int index);

    ///
    /// \brief Duplicate the selected project.
    /// \param Index of the project to be duplicated.
    ///
    void duplicateProject(int index);

    void closeProject(int index);

private slots:
    void on_newProjectButton_clicked();
    void initProgressBar(int);
    void passedProgressStep();

    void on_pushButton_Encode_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_Pause_clicked();

    void on_checkBoxSendSheetToDB_clicked();

    void on_radioButtonSHA1_clicked();

    void on_radioButtonMD5SUM_clicked();

    void on_radioButtonNoneFilePrint_clicked();

private:
    Ui::EncodePane *ui;
    Controller::OCTDispatcher *m_dispatcher;
    QStringListModel *m_modelProjectList;

    int m_progressMax;
    int m_currentSteps;

    int m_pause;

    ///
    /// \brief Connect the interface to the model through the OCTdispatcher.
    ///
    void connectInterface();
};

#endif // ENCODEPANE_H
