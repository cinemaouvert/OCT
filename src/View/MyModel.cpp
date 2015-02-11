#include "MyModel.h"
#include <QColor>
#include <qicon.h>
#include <QDebug>

MyModel::MyModel( int rows, int columns,int nbVideo ,int  nbAudio ,int  nbSub,QObject *parent ) : QAbstractTableModel( parent )
{
  m_rows = rows;
  m_columns = columns;
  m_array = new QString*[m_rows];
  for (int i = 0; i < m_rows; ++i) {
    m_array[i] = new QString[m_columns];
  }
  m_nbAudio = nbAudio;
  m_nbVideo = nbVideo;
  m_nbSubtitle = nbSub;
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
    if (!index.isValid() || (role != Qt::TextAlignmentRole && role != Qt::BackgroundRole && role != Qt::DecorationRole && role != Qt::DisplayRole)){
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
           return Qt::AlignCenter;
    }
    if(role == Qt::DecorationRole){
       if(index.column()==4 || index.column()==5){
            if(m_array[index.row()][index.column()] == "OK"){
                return QIcon(":/icons/resources/glyphicons/glyphicons_152_check.png");
            }else if(m_array[index.row()][index.column()] == "NOK"){
                return QIcon(":/icons/resources/glyphicons/glyphicons_153_unchecked.png");
            }
       }else if(index.column()==0){
           if(index.row()>0 && index.row() < m_nbVideo+1){
                return QIcon(":/icons/resources/glyphicons/glyphicons_008_film.png");
           }else if(index.row()>m_nbVideo+1 && index.row() < m_nbVideo + m_nbAudio +2){
               return QIcon(":/icons/resources/glyphicons/glyphicons_017_music.png");
           }else if(index.row() > m_nbVideo + m_nbAudio +2 && index.row() < m_nbVideo + m_nbAudio + m_nbSubtitle +3){
               return QIcon(":/icons/resources/glyphicons/glyphicons_029_notes_2.png");
           }
       }
       return QVariant();
    }else if(role == Qt::DisplayRole){
        if(index.column()==4 || index.column()==5){
            if(m_array[index.row()][index.column()] == "OK" || m_array[index.row()][index.column()] == "NOK"){
                return "";
            }
        }
    }else if (role == Qt::BackgroundRole){

        if(     index.row() == 0 ||
                index.row() == m_nbVideo +1 ||
                index.row() == m_nbVideo + m_nbAudio +2 ||
                index.row() == m_nbVideo + m_nbAudio + m_nbSubtitle +3 || index.row() == m_nbVideo + m_nbAudio + m_nbSubtitle +4
        ){
            return QColor(QColor(150,150,150,50));

        }
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
