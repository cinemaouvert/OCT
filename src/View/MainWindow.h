#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}
namespace Controller
{
    class OCTDispatcher;
}
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

            /**
             * @brief Destructeur.
             */
            ~MainWindow();
/*
        private slots:
            void on_GroupBox_Import_clicked();
            void on_GroupBox_Config_clicked();
            void on_GroupBox_TracksNaming_clicked();
            void on_GroupBox_Infos_clicked();
            void on_GroupBox_Encode_clicked();
*/
    private slots:
            void on_tabWidget_currentChanged(int index);

    private:
            /**
             * @brief MainWindow.
             */
            Ui::MainWindow *ui;

            /**
             * @brief The associated dispatcher.
             */
            Controller::OCTDispatcher *m_dispatcher;

    };
}

#endif // MAINWINDOW_H
