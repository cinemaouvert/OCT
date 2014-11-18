
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
    class MainWindow : public QMainWindow
	{
        Q_OBJECT
        public:
            View::FilePane* m__;
            Controller::OCTDispatcher* m_unnamed_OCTDispatcher_;
            explicit MainWindow(QWidget *parent = 0,Controller::OCTDispatcher *dispatcher = NULL);
            ~MainWindow();
        private:
            Ui::MainWindow *ui;
            Controller::OCTDispatcher *dispatcher;

	};
}

#endif
