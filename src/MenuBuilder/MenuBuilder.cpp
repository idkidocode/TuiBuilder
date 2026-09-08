#include "MenuBuilder.hpp"
#include <ncurses.h>

namespace TuiBuilder {

    void MenuBuilder::SetOptions(const std::vector<std::string>& opts) {
        options = opts;
    }

    void MenuBuilder::SetActions(const std::vector<std::function<void()>>& act) {
        actions = act;
    }

    void MenuBuilder::SetEndChar(const std::string& end) {
        endChar = end;
    }

    void MenuBuilder::Init()
    {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, true);
    }

    void MenuBuilder::Update()
    {
        while (true) {
            clear();
            for (size_t i = 0; i < options.size(); i++) {
                if ((int)i == choice) {
                    attron(A_REVERSE);
                    mvprintw(i, 0, "%s <<", options[i].c_str());
                    attroff(A_REVERSE);
                } else {
                    attroff(A_REVERSE);
                    mvprintw(i, 0, "%s", options[i].c_str());
                }
            }
            refresh();

            int ch = getch();

            if (ch == endChar[0]) {
                break;
            } else if (ch == KEY_UP) {
                choice = (choice - 1 + options.size()) % options.size();
            } else if (ch == KEY_DOWN) {
                choice = (choice + 1) % options.size();
            } else if (ch == '\n') {
                clear();
                actions[choice]();
                refresh();
                getch();
            }
        }
    }

    void MenuBuilder::End()
    {
        endwin();
    }
}