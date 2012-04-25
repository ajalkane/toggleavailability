/**********************************************************************
 * Copyright 2012 Arto Jalkanen, Philip Lorenz
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
#ifndef TOGGLEAVAILABILITY_H
#define TOGGLEAVAILABILITY_H

#include <QObject>
#include <TelepathyQt4/AccountManager>

namespace Accounts {
class Manager;
}

class ToggleAvailability : public QObject
{
    Q_OBJECT

    Tp::AccountManagerPtr _accountManager;
    Accounts::Manager *_manager;

public:
    ToggleAvailability();

    void activate();

private slots:
    void onAccountManagerReady(Tp::PendingOperation *op);
};

#endif // TOGGLEAVAILABILITY_H
