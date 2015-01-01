#include "MyModel.h"
#include <QColor>

MyModel::MyModel( int rows, int columns, QObject *parent ) : QAbstractTableModel( parent )
{
  m_rows = rows;
  m_columns = columns;
  m_array = new QString*[m_rows];
  for (int i = 0; i < m_rows; ++i) {
    m_array[i] = new QString[m_columns];
  }
}

int MyModel::rowCount( const QModelIndex &parent ) const
{
  return m_rows;
}

int MyModel::columnCount( const QModelIndex &parent ) const
{
  return m_columns;
}

Qt::ItemFlags MyModel::flags( const QModelIndex &index ) const
{
  return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant MyModel::data( const QModelIndex &index, int role ) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (role == Qt::BackgroundRole){
        if (index.row() == 0)
            return QColor(Qt::blue);
        if (index.row() == 1)
            return QColor(Qt::red);
        if (index.row() == 2)
            return QColor(Qt::green);
    }
    return m_array[index.row()][index.column()];
}

QVariant MyModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    /*if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Word %1").arg(section);
    else
        return QString("Set %1").arg(section);
        */
    return QVariant();
}

int MyModel::setItem(int row, int col, QString datum) const
{
    //--- validate the index ---
        if ( row < 0 || col < 0 || row >= m_rows|| col >= m_columns )
            return 0;	// error!

        //--- sets the data ---
        m_array[row][col] = datum;

        //--- tell the world ---
        //emit dataChanged( createIndex( row, col ), createIndex( row, col ) );

        return 1;
}
