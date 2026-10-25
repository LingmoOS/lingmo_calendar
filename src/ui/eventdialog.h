// SPDX-FileCopyrightText: 2026 Reion Wong <reionwong@gmail.com>
// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "calendarmodel.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace Lingmo::ui {
class ComboBox;
class DialogButton;
class DialogWindow;
class Label;
class Switch;
class TextArea;
class TextField;
class View;
class Window;
}

class DateButton;
class FormCard;

// The editor of an event: its title and place, when it is, how it repeats,
// its alert, calendar and notes.
class EventDialog
{
public:
    EventDialog(Lingmo::ui::Window* parent, CalendarModel* model, EventForm event);
    ~EventDialog();

    const EventForm& event() const { return m_event; }
    bool isNew() const { return m_event.key.empty(); }
    Lingmo::ui::Window* window() const;

    void show();
    void close();
    void save();
    // Made again in the session's new language, with what was entered so far.
    void retranslate();

    // A typed time in minutes of the day, or the fallback when it reads as none.
    static int parseTime(const std::string& text, int fallback);

    std::function<void(const EventForm& form)> onSaveRequested;
    std::function<void()> onDeleteRequested;
    std::function<void()> onClosed;

private:
    struct Alarm
    {
        std::string text;
        int alarm;
        int offset;
    };

    void buildContent();
    DateTime start() const;
    DateTime end() const;
    bool isValid() const { return end() >= start(); }
    std::vector<Alarm> alarmChoices() const;
    int alarmIndexFor(int alarm, int offset) const;
    // The event keeps its length when its start moves.
    void setStart(Date date, int minute);
    void update();
    void setUpTimeBox(Lingmo::ui::ComboBox* box, std::function<int()> minute, std::function<void(int)> changed);
    static void showTime(Lingmo::ui::ComboBox* box, int minute);

    CalendarModel* m_model;
    EventForm m_event;
    std::unique_ptr<Lingmo::ui::DialogWindow> m_dialog;

    bool m_allDay = false;
    Date m_startDate;
    Date m_endDate;
    int m_startMinute = 0;
    int m_endMinute = 0;
    int m_repeat = 0;
    int m_repeatEnd = 0;
    Date m_repeatUntil;
    int m_repeatCount = 10;
    int m_alarmIndex = 0;
    int m_shownStartMinute = -1;
    int m_shownEndMinute = -1;
    std::vector<int> m_repeatValues;

    Lingmo::ui::TextField* m_title = nullptr;
    Lingmo::ui::TextField* m_location = nullptr;
    Lingmo::ui::TextArea* m_notes = nullptr;
    Lingmo::ui::Switch* m_allDaySwitch = nullptr;
    DateButton* m_startDateButton = nullptr;
    DateButton* m_endDateButton = nullptr;
    DateButton* m_untilButton = nullptr;
    Lingmo::ui::ComboBox* m_startTime = nullptr;
    Lingmo::ui::ComboBox* m_endTime = nullptr;
    Lingmo::ui::ComboBox* m_repeatBox = nullptr;
    Lingmo::ui::ComboBox* m_repeatEndBox = nullptr;
    Lingmo::ui::TextField* m_countField = nullptr;
    Lingmo::ui::Label* m_timesLabel = nullptr;
    Lingmo::ui::ComboBox* m_alarmBox = nullptr;
    Lingmo::ui::ComboBox* m_calendarBox = nullptr;
    Lingmo::ui::Label* m_error = nullptr;
    Lingmo::ui::View* m_repeatEndRow = nullptr;
    FormCard* m_repeatCard = nullptr;
    Lingmo::ui::DialogButton* m_saveButton = nullptr;
};
