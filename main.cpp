// 4 03 2014
// game ruffini
#include "include/gameEngine.h"
#include<windows.h>
using namespace std;

int main()
{


HWND stealth; //creating stealth (window is not visible)
AllocConsole();
stealth=FindWindowA("ConsoleWindowClass",NULL);
ShowWindow(stealth,0);


midX=getmaxwidth()/2;
midY=getmaxheight()/2;

initwindow(9*dim,8*dim,"Sound",midX-5*dim,midY-4*dim);
GAME.afisazaLogo(4.5*dim-50,1.5*dim);
settextstyle(8,0,1);
outtextxy(3*dim+20,3*dim,"Sound");
butonCreate(0,0.5*dim,4*dim,8.5*dim,5.5*dim,"Yes");
butonCreate(1,0.5*dim,6*dim,8.5*dim,7.5*dim,"No");

while(!AnybutonClick(2))
{
    butonUpdateAll(2);
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
        if(butonClick(0))
            princSound=true;
        else
            princSound=false;
    }
    delay(100);
}

    xMouse=-1;
if(princSound)
{
    ISoundEngine* xFiles= createIrrKlangDevice();
    xFiles->play2D("music/xFiles.mp3",true);
}

meniuPrincipal();

system("exit");
}
