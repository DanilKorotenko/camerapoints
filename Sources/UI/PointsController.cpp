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

#include "PointsController.h"
#include <QtGui>
#include <QtSql>

////////////////////////////////////////////////////////////////////////////////
// Constants
static QString const kDataBaseName = "points.db";

////////////////////////////////////////////////////////////////////////////////
// Implementation Points controller
PointsController::PointsController(QWidget *parent) : QWidget(parent)
{
	QGridLayout *topLayout = new QGridLayout(this);
	QTableView *tableView = new QTableView(this);
}

static bool createConnection()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(kDataBaseName);
	if (!db.open()) {
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
			qApp->tr("Unable to establish a database connection.\n\n"
					 "Click Cancel to exit."), QMessageBox::Cancel);
		return false;
	}

	if (!QFile::exists(kDataBaseName))
	{
		// create empty database
		QSqlQuery query;
		query.exec("create table points (id int primary key, "
			   "firstname varchar(20), lastname varchar(20))");
	query.exec("insert into person values(101, 'Danny', 'Young')");
	query.exec("insert into person values(102, 'Christine', 'Holand')");
	query.exec("insert into person values(103, 'Lars', 'Gordon')");
	query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
	query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

	query.exec("create table offices (id int primary key,"
											 "imagefile int,"
											 "location varchar(20),"
											 "country varchar(20),"
											 "description varchar(100))");
	query.exec("insert into offices "
			   "values(0, 0, 'Oslo', 'Norway',"
			   "'Oslo is home to more than 500 000 citizens and has a "
			   "lot to offer.It has been called \"The city with the big "
			   "heart\" and this is a nickname we are happy to live up to.')");
	query.exec("insert into offices "
			   "values(1, 1, 'Brisbane', 'Australia',"
			   "'Brisbane is the capital of Queensland, the Sunshine State, "
			   "where it is beautiful one day, perfect the next.  "
			   "Brisbane is Australia''s 3rd largest city, being home "
			   "to almost 2 million people.')");
	query.exec("insert into offices "
			   "values(2, 2, 'Redwood City', 'US',"
			   "'You find Redwood City in the heart of the Bay Area "
			   "just north of Silicon Valley. The largest nearby city is "
			   "San Jose which is the third largest city in California "
			   "and the 10th largest in the US.')");
	query.exec("insert into offices "
			   "values(3, 3, 'Berlin', 'Germany',"
			   "'Berlin, the capital of Germany is dynamic, cosmopolitan "
			   "and creative, allowing for every kind of lifestyle. "
			   "East meets West in the metropolis at the heart of a "
			   "changing Europe.')");
	query.exec("insert into offices "
			   "values(4, 4, 'Munich', 'Germany',"
			   "'Several technology companies are represented in Munich, "
			   "and the city is often called the \"Bavarian Silicon Valley\". "
			   "The exciting city is also filled with culture, "
			   "art and music. ')");
	query.exec("insert into offices "
			   "values(5, 5, 'Beijing', 'China',"
			   "'Beijing as a capital city has more than 3000 years of "
			   "history. Today the city counts 12 million citizens, and "
			   "is the political, economic and cultural centre of China.')");

	query.exec("create table images (locationid int, file varchar(20))");
	query.exec("insert into images values(0, 'images/oslo.png')");
	query.exec("insert into images values(1, 'images/brisbane.png')");
	query.exec("insert into images values(2, 'images/redwood.png')");
	query.exec("insert into images values(3, 'images/berlin.png')");
	query.exec("insert into images values(4, 'images/munich.png')");
	query.exec("insert into images values(5, 'images/beijing.png')");
	}

	return true;
}

