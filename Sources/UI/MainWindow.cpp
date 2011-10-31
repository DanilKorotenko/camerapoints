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

#include "MainWindow.h"
#include "PointsWidget.h"
#include "Widget.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	initializeMenu();
	initializeWidgets();
}

void MainWindow::initializeMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"),this);
	fileMenu->addAction(tr("&Quit"),this,SLOT(close()));
	this->menuBar()->addMenu(fileMenu);

	QMenu *helpMenu = new QMenu(tr("&Help"),this);
	helpMenu->addAction(tr("Web site..."),this,SLOT(slotGoToWebSite()));
	helpMenu->addSeparator();
	helpMenu->addAction(tr("About %1...").arg(qApp->applicationName()), this,
		SLOT(slotShowAboutBox()));
	this->menuBar()->addMenu(helpMenu);
}

void MainWindow::initializeWidgets()
{
	Widget *widget = new Widget(this);
	this->setCentralWidget(widget);
	PointsWidget *pointsController = new PointsWidget(this);

	QDockWidget *dockWidget = new QDockWidget(tr("Points"),this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea);
	dockWidget->setWidget(pointsController);
	dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

	connect(pointsController, SIGNAL(selectionDidChange(QList<GeoPoint>)),
		widget, SLOT(slotPointsDidChange(QList<GeoPoint>)));
}

void MainWindow::slotGoToWebSite()
{
	QDesktopServices::openUrl(QUrl(QString("http://code.google.com/p/camerapoints/")));
}

void MainWindow::slotShowAboutBox()
{
	QMessageBox::about(this,tr("About %1...").arg(qApp->applicationName()),
		QString("<strong>%1 %2</strong><br>"
		"<p> Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)<br>"
		"This program is free software; you can redistribute it and/or<br>"
		"modify it under the terms of the GNU General Public Licence<br>"
		"as published by the Free Software Foundation; either version 3<br>"
		"of the Licence, or (at your option) any later version.<br>"
		"<br>"
		"This program is distributed in the hope that it will be useful,<br>"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of<br>"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<br>"
		"GNU General Public Licence for more details.<br>"
		"<br>"
		"You should have received a copy of the GNU General Public Licence<br>"
		"along with this program; if not, write to the Free Software Foundation,<br>"
		"Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.</p>")
		.arg(qApp->applicationName()).arg(qApp->applicationVersion()));
}
