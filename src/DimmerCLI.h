#ifndef DIMMERCLI
#define DIMMERCLI

#include <ncurses.h>
#include <cstdlib>
#include <sys/ioctl.h>
#include <string>

class DimmerCLI {
    int _consoleWidth;
    int _min, _max;

public:
    DimmerCLI(int min, int max);
    void drawDimmer(int value, int dim);
    void drawProgress(int value, std::string text);

};

#endif