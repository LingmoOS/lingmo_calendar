// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#include "calendarstore.h"
#include "reminderservice.h"

#include <base/dbus.h>
#include <base/event_loop.h>
#include <base/i18n.h>
#include <base/locale.h>
#include <base/session_language.h>


int main()
{
    Lingmo::base::Locale::setProcessLocale();
    Lingmo::i18n::setDomain("lingmo-calendar");
    Lingmo::base::EventLoop loop;
    Lingmo::base::dbus::Connection* bus = Lingmo::base::dbus::Connection::session(&loop);
    if (!bus || !bus->requestName("org.lingmo.CalendarReminders"))
        return 0;

    Lingmo::base::SessionLanguage language(bus);
    CalendarStore store;
    ReminderService service(&store, bus);
    store.loadAsync();
    return loop.run();
}
