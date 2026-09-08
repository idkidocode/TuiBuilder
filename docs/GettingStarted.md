# API Reference

This page documents every public class and method currently available in TuiBuilder. For a walkthrough of setting up a project, see [GettingStarted.md](GettingStarted.md).

---

## `TuiBuilder::MenuBuilder`

`MenuBuilder` renders a vertical list of text options in the terminal, lets the user move between them with the arrow keys, and runs a corresponding callback when one is selected.

Header: `<TuiBuilder>` (or directly via `MenuBuilder/MenuBuilder.hpp`)

> **`MenuBuilder` does not manage ncurses setup or teardown.** You must call `initscr()` (and any other ncurses setup you need) yourself *before* calling `Update()`, and `endwin()` yourself afterward. This keeps `MenuBuilder` composable with other ncurses-based code you may already have running, instead of forcing its own screen lifecycle on your whole program.

### Example

```cpp
#include <TuiBuilder>
#include <ncurses.h>

int main() {
    // You own ncurses setup — MenuBuilder assumes it's already initialized
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    TuiBuilder::MenuBuilder menu;

    menu.SetOptions({"Option 1", "Option 2", "Option 3"});
    menu.SetActions({
        []() { mvprintw(0, 0, "Option 1 selected"); refresh(); },
        []() { mvprintw(0, 0, "Option 2 selected"); refresh(); },
        []() { mvprintw(0, 0, "Option 3 selected"); refresh(); }
    });
    menu.SetEndChar("q");

    menu.Update();

    // You own ncurses teardown too
    endwin();

    return 0;
}
```

### Methods

#### `void SetOptions(const std::vector<std::string>& opts)`
Sets the list of option labels shown in the menu, top to bottom, in the order given.

- **Required.** Must be called before `Update()`.
- Must contain the same number of items as the vector passed to `SetActions`, since each option maps to the action at the same index.

```cpp
menu.SetOptions({"New Game", "Load Game", "Settings", "Quit"});
```

---

#### `void SetActions(const std::vector<std::function<void()>>& act)`
Sets the callback functions to run when the corresponding option is selected (Enter pressed). Index `i` in this vector runs when the option at index `i` in `SetOptions` is chosen.

- **Required.** Must be called before `Update()`.
- Accepts any `std::function<void()>` — lambdas, free functions, or bound member functions.

```cpp
menu.SetActions({
    []() { startNewGame(); },
    []() { loadGame(); },
    []() { openSettings(); },
    []() { /* quit handled via SetEndChar */ }
});
```

> **Note:** Since your actions run *while* ncurses owns the terminal (after `Init()`), use ncurses output functions like `mvprintw()` + `refresh()` inside your actions rather than `std::cout` — regular stdout writes may not render correctly while the screen is in curses mode.

---

#### `void SetEndChar(const std::string& end)`
Sets the key that exits the `Update()` loop. Only the first character of the string is checked.

- **Optional.** Defaults to `"q"`.
- Call before `Update()`.

```cpp
menu.SetEndChar("x"); // exits when 'x' is pressed instead of 'q'
```

---

#### `void Update()`
Starts the main menu loop. Renders the option list, highlights the currently selected option, and handles input:

| Key | Behavior |
|---|---|
| `↑` (Up arrow) | Move selection up (wraps to bottom at top) |
| `↓` (Down arrow) | Move selection down (wraps to top at bottom) |
| `Enter` | Run the action mapped to the selected option |
| End char (default `q`) | Exit the loop |

This call blocks until the end character is pressed.

```cpp
menu.Update();
```

`MenuBuilder` does not call `endwin()` for you. Call it yourself once `Update()` returns, if you're done with ncurses.

---

### Typical lifecycle

```cpp
initscr();               // 1. you initialize ncurses
cbreak();
noecho();
curs_set(0);
keypad(stdscr, true);

menu.SetOptions(...);    // 2. configure options
menu.SetActions(...);    // 3. configure actions
menu.SetEndChar(...);    // 4. (optional) configure exit key

menu.Update();           // 5. run the interactive loop

endwin();                // 6. you tear down ncurses
```

Calling `Update()` before ncurses has been initialized (i.e. before `initscr()`) results in undefined behavior — ncurses functions require the screen to be initialized first, and `MenuBuilder` relies on this having already happened.

---

## `TuiBuilder::ProgressBar`

`ProgressBar` draws a fixed-width, 20-character progress bar at a given screen position and lets you update its fill level on demand.

Header: `<TuiBuilder>` (or directly via `ProgressBar/ProgressBar.hpp`)

> Like `MenuBuilder`, `ProgressBar` does not manage ncurses setup or teardown. Call `initscr()` (and any other ncurses setup you need) before constructing a `ProgressBar`, and `endwin()` when you're done with ncurses.

### Example

```cpp
#include <TuiBuilder>
#include <ncurses.h>

int main() {
    initscr();
    curs_set(0);

    TuiBuilder::ProgressBar bar(0, 0); // draws the empty bar at (x=0, y=0)

    for (int i = 0; i <= 100; i += 10) {
        bar.Render(static_cast<float>(i));
        napms(200); // just to visualize the fill over time
    }

    endwin();
    return 0;
}
```

This produces a bar like:

```
[==========          ]
```

### Constructor

#### `ProgressBar(int x, int y)`
Constructs the progress bar and immediately draws it, empty, at the given screen coordinates.

- `x` — column where the bar's opening `[` is drawn.
- `y` — row where the bar is drawn.
- Calls `refresh()` internally after drawing, so the empty bar is visible right away.
- Requires ncurses to already be initialized (see the note above).

```cpp
TuiBuilder::ProgressBar bar(0, 0); // top-left corner of the screen
```

---

### Methods

#### `void Render(float progress)`
Redraws the bar at its fixed position, filling it to reflect `progress`.

- `progress` — a value from `0.0f` to `100.0f`, representing a percentage. Values outside this range aren't clamped, so keep values within range yourself to avoid an under- or over-filled bar.
- The bar is a fixed 20 characters wide; the filled portion is `progress / 100 * 20` characters, rounded down, drawn with `=`, with the remainder drawn as spaces.
- Calls `refresh()` internally, so each call immediately updates what's on screen.

```cpp
bar.Render(50.0f);  // -> [==========          ]
bar.Render(100.0f); // -> [====================]
```

---

### Notes

- The bar width (20 characters) is currently fixed and not configurable.
- Calling `Render()` repeatedly (e.g. in a loop) is the intended way to animate progress — each call fully redraws the bar at the same `(x, y)`.
- Because `Render()` writes directly via `mvprintw`/`addch` and calls `refresh()`, avoid interleaving unrelated `std::cout` writes to the terminal while a `ProgressBar` is in use, for the same reason noted under `MenuBuilder`.



TuiBuilder is planned to grow into a small set of TUI components beyond `MenuBuilder`. Future additions (progress bars, text inputs, confirmation dialogs) will be documented here as they land, each still reachable via the single `#include <TuiBuilder>` umbrella header.