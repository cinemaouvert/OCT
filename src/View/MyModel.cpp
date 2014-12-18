#include "mymodel.h"

MyModel::MyModel( int rows, int columns, QObject *parent ) : QAbstractTableModel( parent )
{
  m_rows = rows;
  m_columns = columns;
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
  switch( role )
  {
  case Qt::DisplayRole:
    return (index.row()+1) * (index.column()+1);

  case Qt::ToolTipRole:
    return QString( "%1 x %2" ).arg( index.row()+1 ).arg( index.column()+1 );

  default:
    return QVariant();
  }
}

QVariant MyModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
  if( role != Qt::DisplayRole )
    return QVariant();

  return QString::number( section+1 );
}
