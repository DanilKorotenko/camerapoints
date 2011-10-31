/*******************************************************************
 Copyright (C) 2011 Danil Korotenko (danil.korotenko@gmail.com)
********************************************************************/

#include "Application.h"

Application::Application(int & argc, char ** argv) : QApplication(argc, argv)
{
	this->setOrganizationName("Biangularity");
	this->setOrganizationDomain("biangularity.com.ua");
	this->setApplicationName("Biangularity");
	this->setApplicationVersion("1.0.0.2");
}
