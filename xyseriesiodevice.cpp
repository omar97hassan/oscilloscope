/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "xyseriesiodevice.h"
#include <QtCore/QIODevice>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QXYSeries>
#include <QLabel>
#include <QtWidgets/QApplication>
#include "widget.h"

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    m_series(series)
{
    resolution = 44;
    range = 1000;
}

qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    oldPoints = m_series->pointsVector();
    newpoints();
    if (oldPoints.count() < range) {
        points = m_series->pointsVector();
    } else {
        for (int i = maxSize/resolution; i < 1000; i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
        points.append(QPointF(k + size, ((quint8)data[int(resolution * k)] - 128)/128.0));
        //points.insert(k,QPointF(k+size, ((quint8)data[int(resolution * k)] - 128)/128.0));

    m_series->replace(points);
    qreal min=points.at(0).y();
    qreal max=min;
    for (int i=0;i<points.size();i++){
        if(points.at(i).y()<min){
            min=points.at(i).y();
        }
        if(points.at(i).y()>max){
            max=points.at(i).y();
        }
    }

    return maxSize;
}


void XYSeriesIODevice::clear()
{
    int i;

    for(i=0;i<points.size();i++){
        points[i]=QPoint(i,0);
    }

    for(i=0;i<oldPoints.size();i++){
        oldPoints[i]=QPoint(i,0);
    }
    m_series->replace(points);
}

void XYSeriesIODevice::newpoints()
{
    pointspo = new QVector<QPointF>;
    points=*pointspo;
}

