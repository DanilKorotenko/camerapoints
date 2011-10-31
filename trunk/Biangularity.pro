#-------------------------------------------------
#
# Project created by QtCreator 2011-06-22T00:03:34
#
#-------------------------------------------------

QT += core gui sql

TARGET = Biangularity
TEMPLATE = app

VERSION = 1.0.0.2

INCLUDEPATH = Sources \
	Sources/UI \
	Sources/UI/Dialogs \
	Sources/DataModel \
	Sources/Controllers \
	alglib/src

SOURCES += Sources/main.cpp\
	Sources/UI/Widget.cpp \
	alglib/src/statistics.cpp \
	alglib/src/specialfunctions.cpp \
	alglib/src/solvers.cpp \
	alglib/src/optimization.cpp \
	alglib/src/linalg.cpp \
	alglib/src/interpolation.cpp \
	alglib/src/integration.cpp \
	alglib/src/fasttransforms.cpp \
	alglib/src/diffequations.cpp \
	alglib/src/dataanalysis.cpp \
	alglib/src/ap.cpp \
	alglib/src/alglibmisc.cpp \
	alglib/src/alglibinternal.cpp \
	Sources/DataModel/GeoCoord.cpp \
	Sources/UI/MainWindow.cpp \
	Sources/UI/PointsWidget.cpp \
	Sources/DataModel/GeoPoint.cpp \
	Sources/Controllers/Application.cpp

HEADERS  += Sources/UI/Widget.h \
	alglib/src/stdafx.h \
	alglib/src/statistics.h \
	alglib/src/specialfunctions.h \
	alglib/src/solvers.h \
	alglib/src/optimization.h \
	alglib/src/linalg.h \
	alglib/src/interpolation.h \
	alglib/src/integration.h \
	alglib/src/fasttransforms.h \
	alglib/src/diffequations.h \
	alglib/src/dataanalysis.h \
	alglib/src/ap.h \
	alglib/src/alglibmisc.h \
	alglib/src/alglibinternal.h \
	Sources/DataModel/GeoCoord.h \
	Sources/UI/MainWindow.h \
	Sources/UI/PointsWidget.h \
	Sources/DataModel/GeoPoint.h \
	Sources/Controllers/Application.h

TRANSLATIONS += Resources/translations/ru.ts

RESOURCES += \
	Resources/resources.qrc


