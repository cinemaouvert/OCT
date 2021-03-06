#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ParametersDialog.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}
namespace Controller
{
    class OCTDispatcher;
}

class FilePane;
class EncodePane;
class AudioPane;
class VideoPane;
class InformationPane;
class SubtitlePane;


namespace View
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:

            /**
             * @brief Explicit constructor.
             * @param parent
             * @param dispatcher
             */
            explicit MainWindow(QWidget *parent = 0,Controller::OCTDispatcher *dispatcher = NULL);

            /**
             * @brief Refresh MainWindow.
             */
            void refresh();

            void refreshProjectPane();

            /**
             * @brief Destructeur.
             */
            ~MainWindow();

            void setOCPMState(bool isValid);
            void updateReco();

            FilePane* getFilePane();
            EncodePane* getEncodePane();
            QObjectList getAudioPanes();
            QTabWidget *getVideoPane();
            QObjectList getSubtitlePanes();
            InformationPane* getInformationPane();

            QStringList getVideoFileNames();
            void infosFromBDD(QMap<QString, QString> *infos);
            void infosFromBDD();
    private slots:
            void on_tabWidget_currentChanged(int index);
            void on_OpenSettings();
            void on_SaveProject();
            void on_SaveProjectSous();
            void on_LoadProject();
            void on_NewProject();
            void on_UpdateVersion();
            void on_viewTorrent();
    private:
            /**
             * @brief MainWindow.
             */
            Ui::MainWindow *ui;

            /**
             * @brief The associated dispatcher.
             */
            Controller::OCTDispatcher *m_dispatcher;

            ParametersDialog *m_settingsW;

            QStringList m_videoFileNames;



    };
}

#endif // MAINWINDOW_H
