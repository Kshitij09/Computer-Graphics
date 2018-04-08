#include "epoint.h"

Epoint::Epoint()
{

}

Epoint::Epoint(int x, int y)
{
    this->x = x;
    this->y = y;
}
int* Epoint::getOutcode(int xL, int yL, int xH, int yH) {
    //Left edge
    outcode[3] = (x < xL) ? 1 : 0;
    //Right edge
    outcode[2] = (x > xH) ? 1 : 0;

    /*conditions for y-axis will change
     * as we're working in 4th quadrant
     */
    //Below edge
    outcode[1] = (y > yL) ? 1 : 0;
    //Above edge
    outcode[0] = (y < yH) ? 1 : 0;
    return outcode;
}
