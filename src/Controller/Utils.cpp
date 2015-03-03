/**********************************************************************************
 * This file is part of Open Cinema Transcoder (OCT).
 *
 * Copyright (C) 2014 Catalogue Ouvert du Cinéma <dev@cinemaouvert.fr>
 *
 * Authors: Romain Boutin <romain.boutin@etu.univ-poitiers.fr>
 *          Thibaud Lamarche <lamarchethibaud@hotmail.com>
 *          William Le Coroller <william.le.coroller@gmail.com>
 *          Denis Saunier <saunier.denis.86@gmail.com>
 *
 * Open Cinema Transcoder is an initiative of Catalogue Ouvert du Cinéma.
 * The software was developed by four students of University of Poitiers
 * as school project.
 *
 * Open Cinema Transcoder is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Open Cinema Transcoder is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open Cinema Transcoder. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************************/
#include "Utils.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QDialog>
#include <QFile>

// ========================================================================== //
// == Static class methods ================================================== //
// ========================================================================== //
QString Utils::convertFract(QString var) {
    QString nomi = "";
    QString denomi = "";

    int i = 0;
    while (var.at(i) != '/' && var.size()>i){
        nomi += var.at(i);
        i++;
    }
    if(var.at(i) == '/'){
        i++;
        while(var.size()>i){
            denomi += var.at(i);
            i++;
        }
        if(denomi.toInt()==0)
            return nomi;
        else{
            int fract =  nomi.toInt() / denomi.toInt();
            return QString::number(fract);
        }
    }
    else return nomi;
}

QString Utils::bpsToKbps(QString var) {
    return QString::number(var.toInt()/1000);
}

QString Utils::md5File(QString pathFile){
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(readAllFile(pathFile));
    QByteArray hah = md5.result();
    return hah.toHex();
}

QString Utils::sha1File(QString pathFile){
    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(readAllFile(pathFile));
    QByteArray hah = sha1.result();
    return hah.toHex();
}

QByteArray Utils::readAllFile(QString pathFile){
    QFile file(pathFile);
    file.open(QIODevice::ReadOnly);
    return file.readAll();
}


