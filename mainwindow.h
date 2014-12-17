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

#endif // MAINWINDOW_H
