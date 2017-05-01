#include "DimmerCLI.h"
using namespace std;

DimmerCLI::DimmerCLI(int min, int max){
    //get columns number
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    _consoleWidth = w.ws_col;
    _min = min;
    _max = max;
}

void DimmerCLI::drawDimmer(int value, int dim){
    int colsPrinted = 0; //columns pointer
    printw("[");
    int printUntil =  (float) (value-_min)/(_max-_min) * (dim-1);
    for (; colsPrinted<printUntil; colsPrinted++)
        printw("-");
    for (; colsPrinted<dim-1; colsPrinted++)
        printw(" ");
    printw("]");
}

void DimmerCLI::drawProgress(int value, std::string text){
    int cols = 0;
    printw("%s", text.c_str());
    cols += text.size();
    for (; cols*2<_consoleWidth; cols++)
    {
        printw(" ");
    }
    drawDimmer(value, _consoleWidth-cols-1);
}