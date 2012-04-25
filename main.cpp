/**********************************************************************
 * Copyright 2012 Arto Jalkanen
 *
 * This file is part of ToggleAvailability.
 *
 * ToggleAvailability is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ToggleAvailability is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ToggleAvailability.  If not, see <http://www.gnu.org/licenses/>
**/
#include <QtCore/QCoreApplication>

#include "toggleavailability.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ToggleAvailability toggler;

    toggler.activate();

    return a.exec();
}
