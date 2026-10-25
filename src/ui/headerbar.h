// SPDX-FileCopyrightText: 2026 LingmoOS Contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <base/signal.h>
#include <ui/view.h>

#include <functional>
#include <string>
#include <vector>

namespace Lingmo::ui {
class HeaderButton;
class Icon;
class Label;
class SearchField;
class SegmentedControl;
}

class CalendarWindow;

// A pill on the calendar's surface: a round one for an icon, a wider one for text.
class NavigationButton : public Lingmo::ui::View
{
public:
    // An icon name, or the text with an empty one.
    NavigationButton(std::string icon, std::string text = {});

    Lingmo::ui::SizeF sizeHint() const override;
    bool acceptsPointer() const override { return true; }

    std::function<void()> onClicked;

protected:
    void layout() override;
    void paint(Lingmo::ui::Painter& painter) override;
    void pointerEnter() override;
    void pointerLeave() override;
    void pointerPress(const Lingmo::ui::PointerEvent& event) override;
    void pointerRelease(const Lingmo::ui::PointerEvent& event) override;

private:
    Lingmo::ui::Icon* m_icon = nullptr;
    Lingmo::ui::Label* m_label = nullptr;
    bool m_hovered = false;
    bool m_pressed = false;
};

// The title bar's tools: the application title and the sidebar button at
// the start, the view switch in the middle, search and the menu at the end.
class HeaderBar : public Lingmo::ui::View
{
public:
    explicit HeaderBar(CalendarWindow* window);
    ~HeaderBar() override;

    // Where the window buttons go from the top: on the title's capitals.
    double buttonsTopMargin() const;
    Lingmo::ui::SearchField* searchField() const { return m_search; }
    Lingmo::ui::HeaderButton* menuButton() const { return m_menuButton; }
    Lingmo::ui::HeaderButton* sidebarButton() const { return m_sidebarButton; }

    std::function<void(const std::string& text)> onSearchChanged;

protected:
    void layout() override;

private:
    CalendarWindow* m_window;
    Lingmo::ui::Label* m_title;
    Lingmo::ui::HeaderButton* m_sidebarButton;
    Lingmo::ui::SegmentedControl* m_viewSwitch;
    Lingmo::ui::SearchField* m_search;
    Lingmo::ui::HeaderButton* m_menuButton;
    std::vector<Lingmo::base::Subscription> m_subscriptions;
};

// The period's title with the previous, today and next buttons.
class NavigationRow : public Lingmo::ui::View
{
public:
    explicit NavigationRow(CalendarWindow* window);
    ~NavigationRow() override;

    // The title can reach below the buttons.
    double rowHeight() const;

protected:
    void layout() override;

private:
    double titleTop() const;

    CalendarWindow* m_window;
    Lingmo::ui::Label* m_title;
    NavigationButton* m_previous;
    NavigationButton* m_today;
    NavigationButton* m_next;
    std::vector<Lingmo::base::Subscription> m_subscriptions;
};
