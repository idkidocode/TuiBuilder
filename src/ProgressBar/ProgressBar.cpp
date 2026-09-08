#include "ProgressBar.hpp"

namespace TuiBuilder {
    ProgressBar::ProgressBar(int x, int y) : x(x), y(y), progress(0.0f) {
        // Initialize the progress bar at the given position
        mvprintw(y, x, "[                    ]"); // 20 spaces for the progress bar
        refresh();
    }

    void ProgressBar::Update(float progress) {
        this->progress = progress;
        int filledLength = static_cast<int>(progress * 20); // Assuming the bar has 20 segments
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