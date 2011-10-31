/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)
********************************************************************/

#include "GeoPoint.h"

GeoPoint::GeoPoint(QString name, GeoCoord latitude, GeoCoord longitude)
{
	_latitude = latitude;
	_longitude = longitude;
	_name = name;
}

QString GeoPoint::name()
{
	return _name;
}

GeoCoord GeoPoint::latitude()
{
	return _latitude;
}

GeoCoord GeoPoint::longitude()
{
	return _longitude;
}
