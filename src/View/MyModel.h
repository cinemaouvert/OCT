#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel( int rows, int columns,int nbVideo ,int  nbAudio ,int  nbSub, QObject *parent = 0 );

      Qt::ItemFlags flags( const QModelIndex &index ) const;
      QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
      QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
      int setItem( int row, int col, QString datum ) const;
      int rowCount( const QModelIndex &parent = QModelIndex() ) const;
      int columnCount( const QModelIndex &parent = QModelIndex() ) const;

private:
      int m_rows, m_columns;
      QString **m_array;
      int m_nbVideo;
      int m_nbAudio;
      int m_nbSubtitle;
signals:

public slots:

};

#endif // MYMODEL_H
