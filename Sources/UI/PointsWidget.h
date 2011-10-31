/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)
********************************************************************/

#ifndef POINTSCONTROLLER_H
#define POINTSCONTROLLER_H

#include <QWidget>
#include <QPoint>
#include <QList>

#include "GeoPoint.h"

class QSqlTableModel;
class QSqlDatabase;
class QTableView;
class QModelIndex;

class PointsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PointsWidget(QWidget *parent = 0);

signals:
	void selectionDidChange(QList<GeoPoint> selectedPoints);

private slots:
	void slotAddRow();
	void slotDeleteRow();

	// Table view slots
	void slotTableViewSelectionDidChange(const QModelIndex &modelIndex);

private:
	QSqlTableModel *model;
	QSqlDatabase *db;

	QTableView *tableView;

	void initializeUI();
	void initializeDataModel();

};

#endif // POINTSCONTROLLER_H
