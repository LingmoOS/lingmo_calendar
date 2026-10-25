// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <ui/color_provider.h>

#include <cstdint>

// The calendar's own colours, after the toolkit's; colors.cpp gives them
// for each theme. Events keep their calendars' colours.
enum class CalendarColor : uint16_t {
    WeekendColumn = uint16_t(Lingmo::ui::ColorId::ApplicationFirst),
    SelectedDay,
    MiniMonthRange,
    MiniMonthSelected,
    SearchResultSelected,
};

void addCalendarColors(Lingmo::ui::ColorMixer& mixer, const Lingmo::ui::Theme& theme);

// Added before main by every program that names one of the colours.
[[maybe_unused]] inline const bool calendarColorsAdded =
    (Lingmo::ui::ColorProvider::addMixer(addCalendarColors), true);
