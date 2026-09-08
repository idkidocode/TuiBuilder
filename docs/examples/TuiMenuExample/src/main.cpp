#include <TuiBuilder>
#include <ncurses.h>

#include <functional>
#include <string>
#include <vector>


int main() {
    //Vector of options and corresponding actions
    std::vector<std::string> options = {"poo", "Option 2", "Option 3"};
    std::vector<std::function<void()>> actions = {
        []() { mvprintw(0, 0, "poo selected"); refresh(); },
        []() { mvprintw(0, 0, "Option 2 selected"); refresh(); },
        []() { mvprintw(0, 0, "Option 3 selected"); refresh(); }
    };

    //Intialize the menu builder
    TuiBuilder::MenuBuilder menuBuilder;

    //Settings : Required
    menuBuilder.SetOptions(options);
    menuBuilder.SetActions(actions);

    //Settings : Optional
    menuBuilder.SetEndChar("q");

    menuBuilder.Init(); //Initialize the menu(ncurses)
        menuBuilder.Update(); //Update the menu and wait for user input
    menuBuilder.End(); //End the menu

    return 0;
}