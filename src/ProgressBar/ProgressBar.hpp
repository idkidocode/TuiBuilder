#include "ncurses.h"

namespace TuiBuilder {
    class ProgressBar {
    public:
        ProgressBar(int x, int y);
        void Render(float progress);
        float getProgress() const { return progress; }
    private:
        int x;
        int y;
        float progress;
    };
}