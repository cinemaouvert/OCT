#include "MyDelegate.h"

MyDelegate::MyDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QIcon icon =  qvariant_cast<QIcon>(index.model()->data(index, Qt::DecorationRole));

    QPixmap iconPixmap = icon.pixmap(option.decorationSize);
    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignLeft ;

    QStyleOptionViewItem myOption2 = option;
    myOption2.displayAlignment = Qt::AlignRight ;
    QRect rect(option.rect.width()-20,option.rect.top(),20,20);


     drawDecoration(painter, option, rect, iconPixmap);

        drawDisplay(painter, myOption, myOption.rect, text);
        drawFocus(painter, myOption, myOption.rect);


}
