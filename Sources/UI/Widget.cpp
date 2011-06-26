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

#include "Widget.h"
#include "solvers.h"
#include <math.h>
#include "GeoCoord.h"

////////////////////////////////////////////////////////////////////////////////
// Constants
// Settings keys
static QString const kCamera1Latitude = "kCamera1Latitude";
static QString const kCamera1Longitude = "kCamera1Longitude";
static QString const kCamera1Azimuth = "kCamera1Azimuth";

static QString const kCamera2Latitude = "kCamera2Latitude";
static QString const kCamera2Longitude = "kCamera2Longitude";
static QString const kCamera2Azimuth = "kCamera2Azimuth";

////////////////////////////////////////////////////////////////////////////////
// Implementation Widget

// Constructors/destructors
Widget::Widget(QWidget *parent) : QWidget(parent)
{
	QApplication::setOrganizationName("CameraSoft");
	QApplication::setApplicationName("CameraPoints");
	initUI();
	readSettings();
}

Widget::~Widget()
{
	writeSettings();
}

// Other methods
void Widget::readSettings()
{
	QSettings settings;

	camera1Latitude->setText(settings.value(kCamera1Latitude, QString())
		.toString());
	camera1Longitude->setText(settings.value(kCamera1Longitude, QString())
		.toString());
	camera1Azimuth->setText(settings.value(kCamera1Azimuth, QString())
		.toString());

	camera2Latitude->setText(settings.value(kCamera2Latitude, QString())
		.toString());
	camera2Longitude->setText(settings.value(kCamera2Longitude, QString())
		.toString());
	camera2Azimuth->setText(settings.value(kCamera2Azimuth, QString())
		.toString());
}

void Widget::writeSettings()
{
	QSettings settings;

	settings.setValue(kCamera1Latitude, camera1Latitude->text());
	settings.setValue(kCamera1Longitude, camera1Longitude->text());
	settings.setValue(kCamera1Azimuth, camera1Azimuth->text());

	settings.setValue(kCamera2Latitude, camera2Latitude->text());
	settings.setValue(kCamera2Longitude, camera2Longitude->text());
	settings.setValue(kCamera2Azimuth, camera2Azimuth->text());
}

void Widget::initUI()
{
	QGridLayout *topLayout = new QGridLayout(this);

	topLayout->addWidget(new QLabel(tr("camera 1"),this),0,0,1,1);

	QRegExp latitudeRegExp("(-?(?:[0-9]{1,2})) ([0-5]?[0-9]) ([0-5]?[0-9]\\.[0-9]{1,2})");
	QRegExp longitudeRegExp("(-?(?:(?:1[0-7][0-9])|(?:[0-9]{1,2}))) ([0-5]?[0-9]) ([0-5]?[0-9]\\.[0-9]{1,2})");
	QRegExp azimuthRegExp("^((\\d|[1-9]\\d|[12]\\d\\d|3[0-5]\\d)(\\.\\d)?|360(\\.0)?)$");
	latitudeValidator = new QRegExpValidator(latitudeRegExp, this);
	longitudeValidator = new QRegExpValidator(longitudeRegExp, this);
	azimuthValidator = new QRegExpValidator(azimuthRegExp, this);

	camera1Latitude = new QLineEdit(this);
	camera1Latitude->setValidator(latitudeValidator);
	topLayout->addWidget(new QLabel(tr("Latitude:"),this),1,0,1,1);
	topLayout->addWidget(camera1Latitude,1,1,1,1);

	camera1Longitude = new QLineEdit(this);
	camera1Longitude->setValidator(longitudeValidator);
	topLayout->addWidget(new QLabel(tr("Longitude:"),this),1,2,1,1);
	topLayout->addWidget(camera1Longitude,1,3,1,1);

	camera1Azimuth = new QLineEdit(this);
	camera1Azimuth->setValidator(azimuthValidator);
	topLayout->addWidget(new QLabel(tr("Azimuth:"),this),1,4,1,1);
	topLayout->addWidget(camera1Azimuth,1,5,1,1);

	topLayout->addWidget(new QLabel(tr("camera 2"),this),2,0,1,1);

	camera2Latitude = new QLineEdit(this);
	camera2Latitude->setValidator(latitudeValidator);
	topLayout->addWidget(new QLabel(tr("Latitude:"),this),3,0,1,1);
	topLayout->addWidget(camera2Latitude,3,1,1,1);

	camera2Longitude = new QLineEdit(this);
	camera2Longitude->setValidator(longitudeValidator);
	topLayout->addWidget(new QLabel(tr("Longitude:"),this),3,2,1,1);
	topLayout->addWidget(camera2Longitude,3,3,1,1);

	camera2Azimuth = new QLineEdit(this);
	camera2Azimuth->setValidator(azimuthValidator);
	topLayout->addWidget(new QLabel(tr("Azimuth:"),this),3,4,1,1);
	topLayout->addWidget(camera2Azimuth,3,5,1,1);

	topLayout->addWidget(new QLabel(tr("point"),this),4,0,1,1);

	pointLatitude = new QLineEdit(this);
	pointLatitude->setReadOnly(true);
	topLayout->addWidget(new QLabel(tr("Latitude:"),this),5,0,1,1);
	topLayout->addWidget(pointLatitude,5,1,1,1);

	pointLongitude = new QLineEdit(this);
	pointLongitude->setReadOnly(true);
	topLayout->addWidget(new QLabel(tr("Longitude:"),this),5,2,1,1);
	topLayout->addWidget(pointLongitude,5,3,1,1);

	QPushButton *solveButton = new QPushButton(tr("Solve"),this);
	connect(solveButton,SIGNAL(clicked()),SLOT(slotSolve()));
	topLayout->addWidget(solveButton,5,5,1,1);

	new QShortcut(Qt::Key_Return, this, SLOT(slotSolve()));
	new QShortcut(Qt::Key_Escape, this, SLOT(close()));

	this->setLayout(topLayout);
}

// Slots
void Widget::slotSolve()
{
	qreal angle1 = camera1Azimuth->text().toFloat();
	angle1 = angle1 * (M_PI / 180);
	qreal cosAngle1 = qCos(angle1);
	qreal sinAngle1 = qSin(angle1);
	qreal angle2 = camera2Azimuth->text().toFloat();
	angle2 = angle2 * (M_PI / 180);
	qreal cosAngle2 = qCos(angle2);
	qreal sinAngle2 = qSin(angle2);

	GeoCoord lat1;
	lat1.setString(camera1Latitude->text());
	GeoCoord lat2;
	lat2.setString(camera2Latitude->text());

	qreal x1 = lat1.getDouble();
	qreal x2 = lat2.getDouble();

	GeoCoord longitude1;
	longitude1.setString(camera1Longitude->text());
	GeoCoord longitude2;
	longitude2.setString(camera2Longitude->text());

	qreal y1 = longitude1.getDouble();
	qreal y2 = longitude2.getDouble();

	QString matrix = QString("[[%1,%2],[%3,%4]]")
		.arg(cosAngle1).arg(-cosAngle2).arg(sinAngle1).arg(-sinAngle2);

	QString vector = QString("[%1,%2]").arg(x2-x1).arg(y2-y1);

	alglib::real_2d_array matr(matrix.toAscii().data());
	alglib::real_1d_array vec(vector.toAscii().data());
	alglib::real_1d_array res;

	alglib::ae_int_t info;
	alglib::densesolverreport rep;
	alglib::rmatrixsolve(matr,2,vec,info,rep,res);

	std::string resStr = res.tostring(1);

	qreal r1 = res[0];

	qreal px = r1 * qCos(angle1) + x1;
	qreal py = r1 * qSin(angle1) + y1;

	GeoCoord plat;
	plat.setDouble(px);

	GeoCoord plongi;
	plongi.setDouble(py);

	pointLatitude->setText(plat.getString());
	pointLongitude->setText(plongi.getString());

}
