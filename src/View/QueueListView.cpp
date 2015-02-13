#include "QueueListView.h"

#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QPoint>

QueueListView::QueueListView(QWidget *parent)
{
}

void QueueListView::setEncodePane(EncodePane *encodePane)
{
    this->m_encodePane = encodePane;
}

void QueueListView::mouseReleaseEvent(QMouseEvent *releaseEvent){
    if(releaseEvent->button() == Qt::RightButton){

        QPoint globalPos = this->mapToGlobal(releaseEvent->pos());


        QMenu contextMenu;
        QAction *charger = new QAction(tr("Charger le projet"), this);
        contextMenu.addAction(charger);

        QAction *duplicate = new QAction(tr("Dupliquer le projet"), this);
        contextMenu.addAction(duplicate);

        QAction *close = new QAction(tr("Fermer le projet"), this);
        contextMenu.addAction(close);

        QAction* selectedItem = contextMenu.exec(globalPos);
        if (selectedItem == charger)
        {
            if(m_encodePane){
                m_encodePane->changeCurrentProject(this->selectedIndexes().at(0).row());
            }
        }else if(selectedItem == duplicate){
            if(m_encodePane){
                m_encodePane->duplicateProject(this->selectedIndexes().at(0).row());
            }
        }else if(selectedItem == close){
            if(m_encodePane){
                m_encodePane->closeProject(this->selectedIndexes().at(0).row());
            }
        }
     }
}

