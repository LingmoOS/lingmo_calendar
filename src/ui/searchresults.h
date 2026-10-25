// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "calendarmodel.h"

#include <base/signal.h>
#include <ui/view.h>

#include <string>
#include <vector>

namespace Lingmo::ui {
class Column;
class Label;
class ScrollView;
}

class CalendarWindow;

// Events whose title, location or notes match, coming ones first, under
// the day they fall on.
class SearchResults : public Lingmo::ui::View
{
public:
    explicit SearchResults(CalendarWindow* window);
    ~SearchResults() override;

    void setText(const std::string& text);
    const std::vector<EventItem>& results() const { return m_results; }

protected:
    void layout() override;
    void paint(Lingmo::ui::Painter& painter) override;

private:
    void update();

    CalendarWindow* m_window;
    std::string m_text;
    std::vector<EventItem> m_results;
    Lingmo::ui::ScrollView* m_scroll;
    Lingmo::ui::Column* m_list;
    Lingmo::ui::Label* m_empty;
    std::vector<Lingmo::base::Subscription> m_subscriptions;
};
