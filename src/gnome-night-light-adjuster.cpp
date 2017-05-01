#include <iostream>
#include <cstdlib>
#include <string>
#include <giomm/settings.h>
#include <ncurses.h>
#include "DimmerCLI.h"
using namespace std;

void printInfo(){
    printw("This program helps you set color temperature for Gnome Night Light feature (introduced in 3.24).\n");
    printw("To increase temperature use +, d or right arrow.\n");
    printw("To decrease use -, a or left arrow.\n");
    printw("Save with s, reset to default value using r, reset to last value with l.\n");
    printw("If you want to edit setting quickly, call the program with new temperature as argument.\n\n");
}

int main(int argc, char** argv){
    Glib::RefPtr<Gio::Settings> colorSetting = 
                  Gio::Settings::create("org.gnome.settings-daemon.plugins.color");
    Glib::ustring tempKey = "night-light-temperature";

    //Quick change - free mode (no range)!
    if(argc > 1){
        colorSetting->set_uint(tempKey, (unsigned) atoi(argv[1]));
        //call needed to update before return, otherwise changes won't be made
        g_settings_sync();
        return 0;
    }

    const int MAX = 6500;
    const int MIN = 1000;
    const int STEP = 50;
    unsigned int currentValue = colorSetting->get_uint(tempKey);
    initscr();  //creates the screen
    cbreak();   //action instantly after keypress
    noecho();   //no echo for input variables
    keypad(stdscr, TRUE); //activates keypad for arrow keys -- disables ESC detection

    DimmerCLI dc(MIN, MAX);
    int kb_press, x, y, maxx = getmaxx(stdscr)-1;
    int initialValue = currentValue;
    printInfo();
    dc.drawProgress(initialValue, "Current Temperature: " + to_string(initialValue));
    getyx(stdscr, y, x); //get current cursor position
    y--;
    move(y, maxx); //up a line, last column
    while ((kb_press = getch())){
        if(kb_press == KEY_RIGHT || kb_press == 'd' || kb_press == 'D' || kb_press == KEY_UP || kb_press == '+')
            currentValue = ((currentValue + STEP) < MAX ? currentValue+STEP : MAX);
        else if(kb_press == KEY_LEFT || kb_press == 'a' || kb_press == 'A' || kb_press == '-' || kb_press == KEY_DOWN)
            currentValue = ((currentValue - STEP) > MIN ? currentValue-STEP : MIN);
        else if(kb_press == 'r' || kb_press == 'R'){
            colorSetting->reset(tempKey);
            currentValue = colorSetting->get_uint(tempKey);
        } else if(kb_press == 'l' || kb_press == 'L')
            currentValue = initialValue;
        else if(kb_press == 's' || kb_press == 'S'){
            g_settings_sync();
            endwin();
            return 0;
        } else
            continue; //other keys won't update screen


        move(y, 0); //move at the beginning of line
        clrtoeol(); //clear last line
        dc.drawProgress(currentValue, "Current Temperature: " + to_string(currentValue));
        move(y, maxx); //sets cursor at end of line
        colorSetting->set_uint(tempKey, currentValue);
    }
    endwin(); //closes screen (ncurses)
    return 0;
}