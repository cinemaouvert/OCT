#ifndef QUEUELISTVIEW_H
#define QUEUELISTVIEW_H


#include "EncodePane.h"

#include <QEvent>
#include <QObject>
#include <QListView>
class QueueListView : public QListView
{
public:
    QueueListView(QWidget *parent = 0);
    void setEncodePane(EncodePane *encodePane);

protected:
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
    EncodePane *m_encodePane;
};

#endif // QUEUELISTVIEW_H
