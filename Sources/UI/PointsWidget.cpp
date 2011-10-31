/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)
********************************************************************/

#include "PointsWidget.h"
#include <QtGui>
#include <QtSql>

////////////////////////////////////////////////////////////////////////////////
// Constants
static QString const kDataBaseName = "points.db";

static bool createConnection();

////////////////////////////////////////////////////////////////////////////////
// Implementation Points controller
PointsWidget::PointsWidget(QWidget *parent) : QWidget(parent)
{
	if (!createConnection())
	{
		return;
	}

	initializeDataModel();
	initializeUI();
}

void PointsWidget::slotAddRow()
{
	QSqlQuery query;
	qint16 rowCount = model->rowCount();
	query.exec(QString("insert into points(id, name) values(%1, '%2 %3')")
		.arg(rowCount).arg(tr("Point")).arg(rowCount));
	model->select();
	tableView->resizeColumnsToContents();
	tableView->resizeRowsToContents();
}

void PointsWidget::slotDeleteRow()
{
	QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

	if (selectedRows.count() == 0)
	{
		return;
	}

	foreach(QModelIndex modelIndex, selectedRows)
	{
		model->removeRow(modelIndex.row());
	}
	model->submitAll();

	tableView->resizeColumnsToContents();
	tableView->resizeRowsToContents();
}

void PointsWidget::slotTableViewSelectionDidChange(
	const QModelIndex &modelIndex)
{
	QList<QModelIndex> selectedRows = tableView->selectionModel()->
		selectedRows();
	if (selectedRows.count() > 2)
	{
		tableView->clearSelection();
		return;
	}

	QList<GeoPoint> points;
	foreach(QModelIndex modelIndex, selectedRows)
	{
		QSqlRecord record = model->record(modelIndex.row());
		GeoCoord latitude(record.value("latitude").toDouble());
		GeoCoord longitude(record.value("longitude").toDouble());
		QString pointName(record.value("name").toString());
		GeoPoint point(pointName,latitude,longitude);
		points.append(point);
	}
	emit selectionDidChange(points);
}

void PointsWidget::initializeUI()
{
	QGridLayout *topLayout = new QGridLayout(this);
	tableView = new QTableView(this);
	tableView->setModel(model);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::MultiSelection);
	tableView->hideColumn(0);
	connect(tableView,SIGNAL(clicked(QModelIndex)),
		SLOT(slotTableViewSelectionDidChange(QModelIndex)));
	tableView->resizeColumnsToContents();
	tableView->resizeRowsToContents();

	topLayout->addWidget(tableView,0,0,1,2);

	QPushButton *addButton = new QPushButton(tr("Add point"), this);
	connect(addButton,SIGNAL(clicked()),this,SLOT(slotAddRow()));
	topLayout->addWidget(addButton,1,0,1,1);

	QPushButton *deleteButton = new QPushButton(tr("Delete point(s)"), this);
	connect(deleteButton,SIGNAL(clicked()),this,SLOT(slotDeleteRow()));
	topLayout->addWidget(deleteButton,1,1,1,1);
}

void PointsWidget::initializeDataModel()
{
	model = new QSqlTableModel(this);
	model->setTable("points");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);

	model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("latitude"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("longitude"));

	model->select();
}

static bool createConnection()
{
	bool fileExist = QFile::exists(kDataBaseName);
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(kDataBaseName);
	if (!db.open())
	{
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
			qApp->tr("Unable to establish a database connection.\n"
					 "Click Cancel to exit."), QMessageBox::Cancel);
		return false;
	}

	if(!fileExist)
	{
		QSqlQuery query;
		query.exec("create table points (id int primary key, "
			"name varchar(20), latitude real, longitude real)");
	}
	return true;
}
