#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>

class MyDelegate : public QItemDelegate
{
public:
    MyDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYDELEGATE_H
