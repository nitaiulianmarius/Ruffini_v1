#define EU 1
#define PC 2
#define VRAJA1 3
#define VRAJA2 4
#define VRAJA3 5
#include "irrKlang.h"
using namespace irrklang;
using namespace std;

char state='p';
int lastPointer=0;

void afisazaFundal()
{
    if( (eu.rundeC + eu.rundeP)%2 )
        setfillstyle(SOLID_FILL,LIGHTBLUE);
    else
        setfillstyle(HATCH_FILL,RED);

	bar(0,0,20*dim,13*dim);

	setfillstyle(SOLID_FILL,GREEN);
	setcolor(BLACK);
	fillellipse(10*dim,6.5*dim,6*dim,6*dim);

    setfillstyle(SOLID_FILL,BLUE);
	bar(0,13*dim,20*dim,13.25*dim);
}


void verificaClickStanga()
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        xMouse=mousex();
        yMouse=mousey();

        if(pc.click()&&lastclick!=VRAJA1&&lastclick!=VRAJA3)
        {
            pc.arataInfo();
            lastclick=PC;
        }

        if(lastclick==VRAJA1 && yMouse<12.5*dim) // Vraja 1 - fireBall
        {
            if(sound)
            {
                vraja1->play2D("music/fireBall.ogg",true);
                timesoundvraja1=clock();
                soundvraja1=true;
            }

            lastclick=EU;
            fireBall.x=eu.x+(dim>>1);
            fireBall.y=eu.y+(dim>>1);
            fireBall.difX=xMouse-fireBall.x;
            fireBall.difY=yMouse-fireBall.y;
            fireBall.pX=fireBall.difX*fireBall.y;
            fireBall.pY=fireBall.difY*fireBall.x;
            fireBall.xDestinatie=xMouse;
            fireBall.yDestinatie=yMouse;
            fireBall.existaDestinatieVraja1=1;
            fireBall.timpIncarcare=clock();
        }

        if(lastclick==VRAJA2)
        {
            if(sound)
            {
                vraja2->play2D("music/powerZone.ogg",true);
                timesoundvraja2=clock();
                soundvraja2=true;
            }

            lastclick=EU;
            powerZone.existaDestinatieVraja2=1;
            powerZone.timpIncarcare=clock();
        }

        if(lastclick==VRAJA3 && yMouse<12.3*dim)
        {
            if(sound)
            {
                vraja3->play2D("music/teleport.wav",true);
                timesoundvraja3=clock();
                soundvraja3=true;
            }


            lastclick=EU;
            eu.x+= (dim>>1); // jumate
            eu.y+= (dim>>1); // jumate
            eu.difX=xMouse-eu.x;
            eu.difY=yMouse-eu.y;
            eu.pX=eu.difX*eu.y;
            eu.pY=eu.difY*eu.x;
            eu.xDestinatie=xMouse;
            eu.yDestinatie=yMouse;
            eu.x-= (dim>>1);
            eu.y-= (dim>>1);
            eu.existaDestinatie=1;
            eu.speed=1;
            teleport.timpIncarcare=clock();
        }

        else if(fireBall.click() && clock()-fireBall.timpIncarcare>fireBall.timpIncarcareMaxim)
            lastclick=VRAJA1;

        else if(powerZone.click() && clock()-powerZone.timpIncarcare>powerZone.timpIncarcareMaxim)
        {
            lastclick=EU;
            powerZone.existaDestinatieVraja2=1;
            powerZone.timpIncarcare=clock();
        }

        else if(teleport.click() && clock()-teleport.timpIncarcare>teleport.timpIncarcareMaxim && !eu.lovit[1])
            lastclick=VRAJA3;

        else if(eu.click())
        {
            eu.arataInfo();
            lastclick=EU; // click pe mine
        }



        clearmouseclick(WM_LBUTTONDOWN);
    }
}



void verificaClickDreapta()
{
    if(ismouseclick(WM_RBUTTONDOWN))
    {
        xMouse=mousex();
        yMouse=mousey();

        if(lastclick==EU && yMouse<12.3*dim)
        {
            eu.x+= (dim>>1); // jumate
            eu.y+= (dim>>1); // jumate
            eu.difX=xMouse-eu.x;
            eu.difY=yMouse-eu.y;
            eu.pX=eu.difX*eu.y;
            eu.pY=eu.difY*eu.x;
            eu.xDestinatie=xMouse;
            eu.yDestinatie=yMouse;
            eu.x-= (dim>>1);
            eu.y-= (dim>>1);
            eu.existaDestinatie=1;
        }

        else if(lastclick==VRAJA1 || lastclick==VRAJA2 || lastclick==VRAJA3)
        {
            lastclick=EU;
        }

        clearmouseclick(WM_RBUTTONDOWN);
    }
}

void verificaPointer()
{
int x=dim,y=13.5*dim;

setfillstyle(SOLID_FILL,BLACK);

if(lastclick==1)//eu
{
    if(fireBall.pointer())
            bar(0,y,x+ 7.5*dim,y+75),fireBall.arataInfo(2,13.5*dim),lastPointer=1;

    else
        if(powerZone.pointer())
                bar(0,y,x+ 7.5*dim,y+75),powerZone.arataInfo(2,13.5*dim),lastPointer=2;

        else
            if(teleport.pointer())
                    bar(0,y,x+ 7.5*dim,y+75),teleport.arataInfo(2,13.5*dim),lastPointer=3;
            else
                if(lastPointer)
                {
                    eu.arataInfo();
                    lastPointer=0;
                }
}

}

void verificaKeyBoardHit()
{
    if(kbhit())
    {
        char c;
        c=getch();

        if(lastclick==EU)
        {

            if(c=='s') // s = te opreste pe loc
                eu.existaDestinatie=0;

            if(c=='q'  && clock()-fireBall.timpIncarcare>fireBall.timpIncarcareMaxim) // fireBall vraja 1
                fireBall.existaDestinatieVraja1=1,lastclick=VRAJA1,fireBall.distantaParcursa=99999;

            if(c=='w' && clock()-powerZone.timpIncarcare>powerZone.timpIncarcareMaxim) // powerZone vraja 2
            {
                lastclick=EU;
                powerZone.existaDestinatieVraja2=1;
                powerZone.timpIncarcare=clock();
            }

            if(c=='e' && clock()-teleport.timpIncarcare>teleport.timpIncarcareMaxim) // teleport vraja 3
                teleport.existaDestinatieVraja3=1,lastclick=VRAJA3;

        }

        if(c=='1') // tab: player
        {
            lastclick=EU;
            eu.arataInfo();
        }

        if(c=='2')
        {
            lastclick=PC;
            pc.arataInfo();
        }

        if(c==27)
        {
            state==c ? state=0 : state=c;
        }



    }

}


void animatieFinal(Obiect& o)
{

    vraja1->stopAllSounds();
    vraja2->stopAllSounds();
    vraja3->stopAllSounds();
    vraja1Pc->stopAllSounds();
    vraja2Pc->stopAllSounds();
    vraja3Pc->stopAllSounds();

   int posX,posY,timp,timpDelay=100;
   posX=o.x;
   posY=o.y;

   timp=clock();
   do
   {
       o.x=posX+rand()%(2*dim)-dim;
       o.y=posY+rand()%(2*dim)-dim;

        afisazaFundal();
        eu.deseneaza(dim);
        pc.deseneaza(dim);

       delay(timpDelay);
       if(timpDelay>3)
            timpDelay-=2;

   }while(clock()-timp<4000);

}

