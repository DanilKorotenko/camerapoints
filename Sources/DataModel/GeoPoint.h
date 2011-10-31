/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)
********************************************************************/

#ifndef GEOPOINT_H
#define GEOPOINT_H

#include "GeoCoord.h"
#include <QString>

class GeoPoint
{
public:
	GeoPoint(QString name, GeoCoord latitude, GeoCoord longitude);

	GeoCoord latitude();
	GeoCoord longitude();
	QString name();

private:
	GeoCoord _latitude;
	GeoCoord _longitude;
	QString _name;
};

#endif // GEOPOINT_H
