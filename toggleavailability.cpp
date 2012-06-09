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
#include "toggleavailability.h"

#include <TelepathyQt4/PendingReady>
#include <Accounts/Manager>

ToggleAvailability::ToggleAvailability()
{
    Tp::registerTypes();
    _manager = new Accounts::Manager(this);
    _accountManager = Tp::AccountManager::create();
}

void
ToggleAvailability::activate() {
    if (!_accountManager->isReady(Tp::AccountManager::FeatureCore)) {
        qDebug() << qPrintable(QDateTime::currentDateTime().toString()) << "ToggleAvailability::toggle Telepathy Account Manager was not ready - will retry as soon as it is ready.";
        connect(_accountManager->becomeReady(Tp::AccountManager::FeatureCore),
                SIGNAL(finished(Tp::PendingOperation*)),
                SLOT(onAccountManagerReady(Tp::PendingOperation*)), Qt::UniqueConnection);
        return;
    }

    foreach(Accounts::AccountId accountId, _manager->accountList()) {
        Accounts::Account *account = _manager->account(accountId);
        foreach (const Accounts::Service *service, account->services()) {
            account->selectService(service);

            QString uid = account->valueAsString("tmc-uid");

            if (uid.isEmpty())
                continue;

            Tp::AccountPtr tpAccount
                    = _accountManager->accountForPath(QString("/org/freedesktop/Telepathy/Account/%1").arg(uid));

            if (!tpAccount) {
                qWarning() << "ToggleAvailability::toggle could not find Telepathy account for" << uid;
                continue;
            }

            Tp::Presence presence = tpAccount->requestedPresence();            
            qDebug() << "ToggleAvailability::toggle current requestedPresence status " << presence.status();

            if (presence.type() == Tp::ConnectionPresenceTypeOffline) {
                qDebug() << "ToggleAvailability::toggle setting presence available for " << uid;
                presence = Tp::Presence::available();
                tpAccount->setConnectsAutomatically(true);
                tpAccount->setAutomaticPresence(presence);
            } else {
                qDebug() << "ToggleAvailability::toggle setting presence offline for " << uid;
                presence = Tp::Presence::offline();
                tpAccount->setConnectsAutomatically(false);
            }

            tpAccount->setRequestedPresence(presence);
        }
    }

    qDebug() << "ToggleAvailability::exiting";
    QCoreApplication::exit();
}

void
ToggleAvailability::onAccountManagerReady(Tp::PendingOperation *op) {
    qDebug("%s ToggleAvailability::onAccountManagerReady()", qPrintable(QDateTime::currentDateTime().toString()));

    if (op->isError()) {
        qWarning() << "ToggleAvailability::onAccountManagerReady failed to instantiate account manager.";
        QCoreApplication::exit();
        return;
    }

    activate();
}
