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
#include <QtGui>
#include "solvers.h"
#include <math.h>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	QGridLayout *topLayout = new QGridLayout(this);

	topLayout->addWidget(new QLabel(tr("camera 1"),this),0,0,1,1);

	camera1x = new QLineEdit(this);
	camera1x->setText("3");
//	connect(camera1x,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("x:"),this),1,0,1,1);
	topLayout->addWidget(camera1x,1,1,1,1);

	camera1y = new QLineEdit(this);
	camera1y->setText("2");
//	connect(camera1y,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("y:"),this),1,2,1,1);
	topLayout->addWidget(camera1y,1,3,1,1);

	camera1angle = new QLineEdit(this);
	camera1angle->setText("0");
//	connect(camera1angle,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("angle:"),this),1,4,1,1);
	topLayout->addWidget(camera1angle,1,5,1,1);

	topLayout->addWidget(new QLabel(tr("camera 2"),this),2,0,1,1);

	camera2x = new QLineEdit(this);
	camera2x->setText("7");
//	connect(camera2x,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("x:"),this),3,0,1,1);
	topLayout->addWidget(camera2x,3,1,1,1);

	camera2y = new QLineEdit(this);
	camera2y->setText("5");
//	connect(camera2y,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("y:"),this),3,2,1,1);
	topLayout->addWidget(camera2y,3,3,1,1);

	camera2angle = new QLineEdit(this);
	camera2angle->setText("270");
//	connect(camera2angle,SIGNAL(returnPressed()),this,SLOT(textDidChange()));
	topLayout->addWidget(new QLabel(tr("angle:"),this),3,4,1,1);
	topLayout->addWidget(camera2angle,3,5,1,1);

	topLayout->addWidget(new QLabel(tr("point"),this),4,0,1,1);

	pointX = new QLineEdit(this);
	topLayout->addWidget(new QLabel(tr("x:"),this),5,0,1,1);
	topLayout->addWidget(pointX,5,1,1,1);

	pointY = new QLineEdit(this);
	topLayout->addWidget(new QLabel(tr("y:"),this),5,2,1,1);
	topLayout->addWidget(pointY,5,3,1,1);

	QPushButton *solveButton = new QPushButton(tr("Solve"),this);
	connect(solveButton,SIGNAL(clicked()),SLOT(slotSolve()));
	topLayout->addWidget(solveButton,5,5,1,1);

	this->setLayout(topLayout);
}

Widget::~Widget()
{

}

void Widget::slotSolve()
{
	qreal angle1 = camera1angle->text().toFloat();
	angle1 = angle1 * (M_PI / 180);
	qreal cosAngle1 = qCos(angle1);
	qreal sinAngle1 = qSin(angle1);
	qreal angle2 = camera2angle->text().toFloat();
	angle2 = angle2 * (M_PI / 180);
	qreal cosAngle2 = qCos(angle2);
	qreal sinAngle2 = qSin(angle2);

	qreal x1 = camera1x->text().toFloat();
	qreal x2 = camera2x->text().toFloat();

	qreal y1 = camera1y->text().toFloat();
	qreal y2 = camera2y->text().toFloat();

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

	pointX->setText(QString("%1").arg(px));
	pointY->setText(QString("%1").arg(py));

}
