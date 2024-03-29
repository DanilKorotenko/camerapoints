/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public Licence
 as published by the Free Software Foundation; either version 3
 of the Licence, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public Licence for more details.

 You should have received a copy of the GNU General Public Licence
 along with this program; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>

#include "GeoPoint.h"

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = 0);
	~Widget();

public slots:
	void slotPointsDidChange(QList<GeoPoint> points);

private:
	QRegExpValidator *latitudeValidator;
	QRegExpValidator *longitudeValidator;
	QRegExpValidator *azimuthValidator;

	QLabel *point1Name;
	QLineEdit *camera1Latitude;
	QLineEdit *camera1Longitude;
	QDoubleSpinBox *camera1Azimuth;

	QLabel *point2Name;
	QLineEdit *camera2Latitude;
	QLineEdit *camera2Longitude;
	QDoubleSpinBox *camera2Azimuth;

	QLineEdit *pointLatitude;
	QLineEdit *pointLongitude;

private slots:
	void slotSolve();

private:
	void initUI();
	void readSettings();
	void writeSettings();
};

#endif // WIDGET_H
