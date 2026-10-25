// SPDX-FileCopyrightText: 2026 Reion Wong <reionwong@gmail.com>
// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "datetime.h"

#include <base/signal.h>
#include <ui/scroll_view.h>

#include <memory>
#include <vector>

namespace Lingmo::ui {
class Column;
class Label;
class RowLayout;
}

class CalendarRow;
class CalendarWindow;
class MiniMonth;

// The month at a glance and the calendars, each shown or hidden.
class Sidebar : public Lingmo::ui::ScrollView
{
public:
    explicit Sidebar(CalendarWindow* window);
    ~Sidebar() override;

    Date shownMonth() const { return m_shownMonth; }
    void setShownMonth(Date month);

protected:
    void layout() override;

private:
    class Card;

    void updateMonth();
    void updateCalendars();
    // A heading with its add button, over a card of calendar rows.
    Lingmo::ui::RowLayout* addHeading(const std::string& text, const std::string& buttonName);

    CalendarWindow* m_window;
    // The month the small calendar shows; it follows the main view until
    // its own arrows move it.
    Date m_shownMonth;
    Lingmo::ui::Label* m_monthLabel;
    std::vector<Lingmo::ui::Label*> m_headings;
    MiniMonth* m_miniMonth;
    Card* m_calendarList;
    Lingmo::ui::RowLayout* m_subscriptionHeading;
    Card* m_subscriptionList;
    std::vector<CalendarRow*> m_rows;
    bool m_updatePosted = false;
    std::shared_ptr<bool> m_alive = std::make_shared<bool>(true);
    std::vector<Lingmo::base::Subscription> m_subscriptions;
};
