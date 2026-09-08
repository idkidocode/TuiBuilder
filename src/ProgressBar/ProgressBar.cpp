#include "ProgressBar.hpp"

namespace TuiBuilder {
    ProgressBar::ProgressBar(int x, int y) : x(x), y(y), progress(0.0f) {
        mvprintw(y, x, "[                    ]"); 
        refresh();
    }

    void ProgressBar::Render(float progress) {
        this->progress = progress;

        int filledLength = static_cast<int>((progress / 100.0f) * 20);

        mvprintw(y, x, "[");
        for (int i = 0; i < 20; ++i) {
            if (i < filledLength) {
                addch('=');
            } else {
                addch(' ');
            }
        }
        addch(']');

        refresh();
    }
}