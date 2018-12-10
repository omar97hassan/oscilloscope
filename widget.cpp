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

#include "widget.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>
#include <QGridLayout>
#include <QPushButton>
#include <Qlabel>
#include <QTimer>
#include "xyseriesiodevice.h"
#include <cmath>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    axisX = new QValueAxis;
    axisX->setRange(0, 1000);
    axisX->setLabelFormat("");
    axisX->setTitleText("Time: 1s");
    axisY = new QValueAxis;
    axisY->setRange(-0.7, 0.7);
    axisY->setLabelFormat("");
    axisY->setTitleText("Voltage: 100mVpp");
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("Data from the Audio Card");

    const QSize _sizeTwoBtns = QSize(50, 25);



    _btnONOFF = new QPushButton;
    _btnClear = new QPushButton;
    _btnAuto = new QPushButton;
    _btnScreen= new QPushButton;
    _btnZoomAmpM = new QPushButton;
    _btnZoomTimeM = new QPushButton;
    _btnZoomAmpP = new QPushButton;
    _btnZoomTimeP = new QPushButton;

    _btnONOFF->setText("ON");
    _btnClear->setText("Clear");
    _btnAuto->setText("Auto");
    _btnScreen->setText("Screenshot");

    _btnZoomAmpM->setText("-");
    _btnZoomAmpP->setText("+");
    _btnZoomTimeM->setText("-");
    _btnZoomTimeP->setText("+");


    _lblZmAmp = new QLabel;
    _lblZmTime = new QLabel;
    _lblAmp = new QLabel;
    _lblOmg = new QLabel;
    _lblPhi = new QLabel;
    //_lblDC = new QLabel;
    _lblRoot = new QLabel;
    _lblMax = new QLabel;
    _lblMin = new QLabel;
    _lblAmpV = new QLabel;
    //_lblOmgV = new QLabel;
    _lblPhiV = new QLabel;
    //_lblDCV = new QLabel;
    _lblRootV = new QLabel;
    _lblMaxV = new QLabel;
    _lblMinV = new QLabel;
    _lblFreq = new QLabel;
    _lblFreqV = new QLabel;
    _lblGlavni = new QLabel;
    _lblRMS = new QLabel;
    _lblRMSV = new QLabel;

    _lblAmp->setText("Amplitude:");
    //_lblOmg->setText("Angular Frequency:");
    _lblPhi->setText("Phase Shift:");
    //_lblDC->setText("DC Offset:");
    _lblRoot->setText("Root:");
    _lblMin->setText("Minimum:");
    _lblMax->setText("Maximum:");
    _lblZmAmp->setText("Y-axis");
    _lblZmTime->setText("X-axis");
    _lblFreq->setText("Frequency:");
    _lblGlavni->setText("QuattroFantastico");
    _lblGlavni->setStyleSheet("font-weight: bold; color: blue; font-style: italic;");

    _lblAmpV->setText("0 mV");
    //_lblOmgV->setText("0 rad/s");
    _lblPhiV->setText("0 rad");
    _lblFreqV->setText("0 Hz");
    //_lblDCV->setText("3 V");
    _lblRootV->setText("0 s");
    _lblMinV->setText("0 s");
    _lblMaxV->setText("0 s");
    _lblRMS->setText("RMS:");
    _lblRMSV->setText("0 mV");
    /*
    _lblZoom->setText("Time:");
    _lblZoomV->setText("1s");
    _lblZoom->setTextFormat(Qt::RichText);
    _lblZoomV->setTextFormat(Qt::RichText);
    */






    _laySet = new QGridLayout;
    _layZoomA= new QGridLayout;
    _layZoomT = new QGridLayout;

    _layZoomA->addWidget(_btnZoomAmpM, 0, 0);
    _layZoomA->addWidget(_lblZmAmp, 0, 1, Qt::AlignCenter);
    _layZoomA->addWidget(_btnZoomAmpP, 0, 2);

    _layZoomT->addWidget(_btnZoomTimeM, 0, 0);
    _layZoomT->addWidget(_lblZmTime, 0, 1, Qt::AlignCenter);
    _layZoomT->addWidget(_btnZoomTimeP, 0, 2);



    _laySet->addWidget(_lblRoot, 0, 0);
    _laySet->addWidget(_lblRootV, 0, 1);
    _laySet->addWidget(_lblMin, 0, 2);
    _laySet->addWidget(_lblMinV, 0, 3);
    _laySet->addWidget(_lblMax, 0, 4);
    _laySet->addWidget(_lblMaxV, 0, 5);
    _laySet->addWidget(_lblGlavni, 0, 6, 1, 2);

    _laySet->addWidget(_lblAmp, 1, 0);
    _laySet->addWidget(_lblAmpV, 1, 1);
    _laySet->addWidget(_lblFreq, 1, 2);
    _laySet->addWidget(_lblFreqV, 1, 3);
    _laySet->addWidget(_lblPhi, 1, 4);
    _laySet->addWidget(_lblPhiV, 1, 5);
    _laySet->addWidget(_lblRMS, 1, 6);
    _laySet->addWidget(_lblRMSV, 1, 7);


    _laySet->addLayout(_layZoomA, 2, 0, 1, 4);
    _laySet->addLayout(_layZoomT, 2, 4, 1, 4);


    _laySet->addWidget(_btnAuto, 3, 0, 1, 2);
    _laySet->addWidget(_btnScreen, 3, 2, 1, 2);
    _laySet->addWidget(_btnClear, 3, 4, 1, 2);
    _laySet->addWidget(_btnONOFF, 3, 6, 1, 2);

    _layA = new QGridLayout;
    _layA->addWidget(chartView);

    _layAll = new QGridLayout;
    _layAll->addLayout(_layA, 0, 0);
    _layAll->addLayout(_laySet, 1, 0);
    setLayout(_layAll);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(48000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly);


    connect(_btnONOFF,SIGNAL(clicked(bool)),this,SLOT(onof()));
    connect(_btnClear,SIGNAL(clicked(bool)),m_device,SLOT(clear()));
    connect(_btnAuto,SIGNAL(clicked(bool)),this,SLOT(autoz()));
    connect(_btnZoomAmpM,SIGNAL(clicked(bool)),this,SLOT(zoomAM()));
    connect(_btnZoomAmpP,SIGNAL(clicked(bool)),this,SLOT(zoomAP()));
    connect(_btnZoomTimeM,SIGNAL(clicked(bool)),this,SLOT(zoomTM()));
    connect(_btnZoomTimeP,SIGNAL(clicked(bool)),this,SLOT(zoomTP()));
    connect(_btnScreen,SIGNAL(clicked(bool)),this,SLOT(screen()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(apdejt()));
    timer->start(100);

    _btnZoomTimeM->setEnabled(false);
    _btnZoomAmpM->setEnabled(false);

}

qreal Widget::minn(qreal a, qreal b){
    if(a<b)
        return a;
    else return b;
}

qreal Widget::maxx(qreal a, qreal b){
    if(a>b)
        return a;
    else return b;
}

void Widget::apdejt(){
    if(radi){
        qreal gdjemin=0;
        qreal gdjemax=0;
        qreal gdjerut=0,gdjerut2=0;
        if(m_device->points.size()){
            min=m_device->points.at(0).y();
            max=m_device->points.at(0).y();
        }
        else{
            min=0;
            max=0;
        }
        qreal sum=0;
        bool rut=false,rut2=false;
        for (int i=0;i<minn(m_device->points.size(),1000);i++){
            if(m_device->points.at(i).y()<min){
                min=m_device->points.at(i).y();
                gdjemin=m_device->points.at(i).x();
            }
            if(m_device->points.at(i).y()>max){
                max=m_device->points.at(i).y();
                gdjemax=m_device->points.at(i).x();
            }
            if(gdjerut2-gdjerut<10) // digital capacitor
                rut2=false;
            if(!rut2 && rut && i<minn(m_device->points.size(),1000)-1 && m_device->points.at(i).y()!=m_device->points.at(i+1).y() && ((m_device->points.at(i).y()>=0 && m_device->points.at(i+1).y()<=0) || (m_device->points.at(i).y()<=0 && m_device->points.at(i+1).y()>=0))){
                gdjerut2=m_device->points.at(i).x();
                rut2=true;
            }
            if(!rut && i<minn(m_device->points.size(),1000)-1 && m_device->points.at(i).y()!=m_device->points.at(i+1).y() && ((m_device->points.at(i).y()>=0 && m_device->points.at(i+1).y()<=0) || (m_device->points.at(i).y()<=0 && m_device->points.at(i+1).y()>=0))){
                gdjerut=m_device->points.at(i).x();
                rut=true;
            }
            if(rut && !rut2 && m_device->points.at(i).y()){
                sum+=pow((m_device->points.at(i).y()+m_device->points.at(i+1).y())/2,2);
            }

        }
        qreal rms=sqrt(2.0*sum/(gdjerut2-gdjerut))*50;
        max=max*100/0.7/2; // [mV]
        min=min*100/0.7/2; // [mV]
        if(zoomlevel<3){
            gdjemax/=pow(10,zoomlevel);
            gdjemin/=pow(10,zoomlevel);
            gdjerut/=pow(10,zoomlevel);
            gdjerut2/=1.0*pow(10,zoomlevel);
        }
        else{
            gdjemax/=400;
            gdjemin/=400;
            gdjerut/=400;
            gdjerut2/=400.0;
        }
        freq=500.0/(gdjerut2-gdjerut);
        qreal angfreq=3.1415926*freq*2;
        if(rut)
            _lblRootV->setText(QString::number(gdjerut)+" ms");
        else _lblRootV->setText("NO ROOT");
        _lblMaxV->setText(QString::number(gdjemax)+" ms");
        _lblMinV->setText(QString::number(gdjemin)+" ms");
        _lblAmpV->setText(QString::number(max)+" mV");
        if(rut && rut2){
            _lblFreqV->setText(QString::number(freq)+" Hz / "+ QString::number(angfreq)+" rad/s");
            _lblRMSV->setText(QString::number(rms)+" mV");
            qreal ug=-1.0*angfreq*gdjerut/1000;
            /*
            if(ug<=-3.1415926/2)
                ug+=3.1415926;
            */
            if(m_device->points.at(0).y()>0)
                ug*=-1;
            if(ug>0)
                ug=3.1415926-ug;
            _lblPhiV->setText(QString::number(180.0*ug/3.1415926)+"° / "+ QString::number(ug)+" rad");
        }
        else{
            _lblFreqV->setText("NO ROOTS");
            _lblRMSV->setText("NO ROOTS");
            _lblPhiV->setText("NO ROOTS");
        }
    }
}

void Widget::autoz(){
    qreal koji=2*maxx(max,-min);
    if(koji>45){
        //prvi zum

        _btnZoomAmpM->setEnabled(false);
        _btnZoomAmpP->setEnabled(true);
        axisY->setTitleText("Voltage: 100mVpp");
        axisY->setRange(-0.7, 0.7);
        zoomlevel2=0;
    }
    else if(koji>20){
        // drugi zum
        _btnZoomAmpM->setEnabled(true);
        _btnZoomAmpP->setEnabled(true);
        axisY->setTitleText("Voltage: 50mVpp");
        axisY->setRange(-0.35, 0.35);
        zoomlevel2=1;
    }
    else if(koji>8){
        // treci zum

        _btnZoomAmpM->setEnabled(true);
        _btnZoomAmpP->setEnabled(true);
        axisY->setTitleText("Voltage: 25mVpp");
        axisY->setRange(-0.175, 0.175);
        zoomlevel2=2;
    }
    else{
        // cetti zum

        axisY->setTitleText("Voltage: 10mVpp");
        axisY->setRange(-0.07, 0.07);
        _btnZoomAmpM->setEnabled(true);
        _btnZoomAmpP->setEnabled(false);
        zoomlevel2=3;
    }

    if(freq>900){

        _btnZoomTimeP->setEnabled(false);
        _btnZoomTimeM->setEnabled(true);
        axisX->setTitleText("Time: 2.5ms");
        m_device->resolution=0.12;
        zoomlevel=3;
    }
    else if(freq>190){


        m_device->resolution=0.48;
        _btnZoomTimeM->setEnabled(true);
        _btnZoomTimeP->setEnabled(true);
        //_btnZoomTimeP->setEnabled(false);
        axisX->setTitleText("Time: 10ms");
        zoomlevel=2;
    }
    else if(freq>20){


        _btnZoomTimeM->setEnabled(true);
        _btnZoomTimeP->setEnabled(true);
        m_device->resolution=4.8;
        axisX->setTitleText("Time: 100ms");
        zoomlevel=1;
    }
    else{

        _btnZoomTimeM->setEnabled(false);
        _btnZoomTimeP->setEnabled(true);
        m_device->resolution=48;
        axisX->setTitleText("Time: 1s");
        zoomlevel=0;
    }
}

void Widget::onof()
{

    if(_btnONOFF->text()=="OFF"){
        m_audioInput->stop();
        _btnONOFF->setText("ON");
        radi=false;
    }
    else {
        m_audioInput->start(m_device);
        _btnONOFF->setText("OFF");
        radi=true;
    }
}

void Widget::zoomTP()
{
    if(zoomlevel==0){
        _btnZoomTimeM->setEnabled(true);
        m_device->resolution=4.8;
        axisX->setTitleText("Time: 100ms");
    }

    if(zoomlevel==1){
        m_device->resolution=0.48;
        //_btnZoomTimeP->setEnabled(false);
        axisX->setTitleText("Time: 10ms");
    }

    if(zoomlevel==2){
        _btnZoomTimeP->setEnabled(false);
        axisX->setTitleText("Time: 2.5ms");
        m_device->resolution=0.12;
    }
    zoomlevel++;
}

void Widget::zoomTM()
{

    if(zoomlevel==1){
        _btnZoomTimeM->setEnabled(false);
        m_device->resolution=48;
        axisX->setTitleText("Time: 1s");

    }

    if(zoomlevel==2){
        //_btnZoomTimeP->setEnabled(true);
        m_device->resolution=4.8;
        axisX->setTitleText("Time: 100ms");
    }

    if(zoomlevel==3){
        _btnZoomTimeP->setEnabled(true);
        m_device->resolution=0.48;
        axisX->setTitleText("Time: 10ms");

    }

    zoomlevel--;
}

void Widget::zoomAP()
{
    if(zoomlevel2==0){
        _btnZoomAmpM->setEnabled(true);
        axisY->setTitleText("Voltage: 50mVpp");
        axisY->setRange(-0.35, 0.35);
    }

    if(zoomlevel2==1){
        axisY->setTitleText("Voltage: 25mVpp");
        axisY->setRange(-0.175, 0.175);
    }

    if(zoomlevel2==2){
        axisY->setTitleText("Voltage: 10mVpp");
        axisY->setRange(-0.07, 0.07);
        _btnZoomAmpP->setEnabled(false);
    }

    zoomlevel2++;
}

void Widget::zoomAM()
{

    if(zoomlevel2==1){
        _btnZoomAmpM->setEnabled(false);
        axisY->setTitleText("Voltage: 100mVpp");
        axisY->setRange(-0.7, 0.7);
    }

    if(zoomlevel2==2){
        axisY->setTitleText("Voltage: 50mVpp");
        axisY->setRange(-0.35, 0.35);
    }

    if(zoomlevel2==3){
        axisY->setTitleText("Voltage: 25mVpp");
        axisY->setRange(-0.175, 0.175);
        _btnZoomAmpP->setEnabled(true);
    }

    zoomlevel2--;
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
}
