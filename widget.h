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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QValueAxis>
#include <QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QLabel *_lblZmAmp, *_lblZmTime,*_lblAmp, *_lblOmg,* _lblPhi,
            *_lblDC, *_lblRoot, *_lblMax, *_lblMin, *_lblAmpV,
            *_lblOmgV, *_lblPhiV, *_lblDCV, *_lblRootV, *_lblMaxV,
            *_lblMinV, *_lblZoom, *_lblZoomV, *_lblFreqV, *_lblFreq, *_lblGlavni, *_lblRMS, *_lblRMSV;
    qreal minn(qreal a, qreal b);
    qreal maxx(qreal a, qreal b);
    ~Widget();

private slots:
    void onof();
    void zoomTP();
    void zoomTM();
    void zoomAP();
    void zoomAM();
    void autoz();
    //void clear();

public slots:
    void apdejt();

private:
    XYSeriesIODevice *m_device;
    QChart *m_chart;
    QLineSeries *m_series;
    QAudioInput *m_audioInput;
    QGridLayout *_layA, *_layB, *_layAll,* _laySet,*_layZoomA,*_layZoomT;
    QPushButton *_btnONOFF, *_btnClear, *_btnAuto,*_btnScreen,
    *_btnZoomAmpM, *_btnZoomAmpP,*_btnZoomTimeM, *_btnZoomTimeP;
    int zoomlevel = 0, zoomlevel2 = 0;
    QValueAxis *axisX, *axisY;
    QTimer *timer;
    bool radi=false;
    qreal min,max,gdjerut,gdjerut2,freq;
};

#endif // WIDGET_H
