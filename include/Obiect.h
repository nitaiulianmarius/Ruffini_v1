#include "graphics.h"
#include "iostream"

class Obiect
{

public:
    int x,y,xDestinatie,yDestinatie,existaDestinatie;
    int viata,maxViata; // jucator & pc
    int rundeC,rundeP; // jucator & pc runde castigate si pierdute
    int difX,difY,pY,pX; // pentru ecuatia dreptei (se deplaseaza pe (x,y) cu ax+by+c=0)
    int speed; // cand foloseste vraja de teleport
    bool lovit[20];
    int distantaParcursa,distantaParcursaMaxima;
    int xUnitate,yUnitate;
    int lastDmg;

    void update();
    void deseneaza(int);
    void arataInfo();
    bool click();

};
