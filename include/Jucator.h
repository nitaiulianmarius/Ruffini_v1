#ifndef PC
#define PC 2
#endif // PC
#include<iostream.h>


void Jucator::deseneaza(int dimensiune)
{
    if(eu.speed && teleport.distantaParcursa<teleport.distantaParcursaMaxima && dimensiune==dim)
    {
        setfillstyle(SOLID_FILL,BLACK);
        setcolor(WHITE);
        fillellipse(eu.x+dim/2,eu.y+dim/2,dim,dim);
    }

    else
    {

            if(dimensiune==dim)
            {

                if(lastclick==1) // eu
                {
                    setcolor(BLACK);
                    circle(eu.x+0.5*dimensiune,eu.y+0.5*dimensiune,0.9*dimensiune);
                }

                // viata
                if(eu.viata>0)
                {
                    setfillstyle(1,WHITE);
                    bar( eu.x+3, eu.y-5, eu.x+(float)eu.viata/eu.maxViata*dim, eu.y-2 );
                }
            }

        setfillstyle(1,YELLOW);
        bar(eu.x+0.25*dimensiune,eu.y+0.02*dimensiune,eu.x+0.75*dimensiune,eu.y+0.5*dimensiune);
        setfillstyle(1,LIGHTCYAN);
        bar(eu.x+0.35*dimensiune,eu.y+0.51*dimensiune,eu.x+0.65*dimensiune,eu.y+0.85*dimensiune);
        setfillstyle(1,MAGENTA);
        bar(eu.x+0.35*dimensiune,eu.y+0.1*dimensiune,eu.x+0.65*dimensiune,eu.y+0.21*dimensiune);
        bar(eu.x+0.35*dimensiune,eu.y+0.35*dimensiune,eu.x+0.65*dimensiune,eu.y+0.37*dimensiune);
        setfillstyle(1,LIGHTRED);
        bar(eu.x+0.16*dimensiune,eu.y+0.51*dimensiune,eu.x+0.35*dimensiune,eu.y+0.75*dimensiune);
        bar(eu.x+0.65*dimensiune,eu.y+0.51*dimensiune,eu.x+0.84*dimensiune,eu.y+0.75*dimensiune);
        setfillstyle(1,DARKGRAY);
        bar(eu.x+0.2*dimensiune,eu.y+0.85*dimensiune,eu.x+0.45*dimensiune,eu.y+0.95*dimensiune);
        bar(eu.x+0.55*dimensiune,eu.y+0.85*dimensiune,eu.x+0.8*dimensiune,eu.y+0.95*dimensiune);



    }


}


bool Jucator::click()
{
    if(eu.x < xMouse && xMouse < eu.x+dim)
        if(eu.y < yMouse && yMouse < eu.y+dim)
            return true;
    return false;
}


void Jucator::arataInfo()
{
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,13.25*dim,20*dim,16*dim);

    int x,y;
    x=eu.x;eu.x=8.5*dim;
    y=eu.y;eu.y=13.5*dim;
    eu.deseneaza(2*dim);
    eu.x=x;
    eu.y=y;

    settextstyle(8,0,1);
    setcolor(WHITE);
    outtextxy(0.5*dim,14*dim-7,"Runde castigate:");
    outtextxy(0.5*dim,15*dim-15,"Runde pierdute:");

    char rc[5],rp[5];

    itoa(eu.rundeC,rc,5); outtextxy(0.5*dim+textwidth("Runde castigate: "),14*dim-7,rc);
    itoa(eu.rundeP,rp,5); outtextxy(0.5*dim+textwidth("Runde pierdute: "),15*dim-15,rp);


    char v[5],mv[5];
    sprintf(v,"%d",eu.viata);
    sprintf(mv,"%d",eu.maxViata);
    strcat(mv,"   ");
    strcat(v,"/");
    strcat(v,mv);
    outtextxy(8.5*dim,16*dim-15,v);

    fireBall.deseneazaButon();
    powerZone.deseneazaButon();
    teleport.deseneazaButon();
}



void Jucator::update()
{

    if((eu.x<dim/2 || eu.x>19*dim-1 || eu.y<1 || eu.y>12*dim-1) && (eu.lovit[1] || eu.lovit[2])) // a ajuns la margine, s-a oprit !
    {
        eu.existaDestinatie=0;
        eu.distantaParcursa=0;
        eu.lovit[1]=false;
        eu.lovit[2]=false;
    }

    if((abs(eu.x+dim/2-eu.xDestinatie)<7 && abs(eu.y+dim/2-eu.yDestinatie)<7))
        eu.existaDestinatie=0,eu.speed=0;

    /// lovit de vraja 1
            if(eu.distantaParcursa>eu.distantaParcursaMaxima)
            {
                eu.distantaParcursa=0;
                eu.lovit[1]=false;
            }
            if(eu.lovit[1])
            {
                if(eu.y>11*dim || eu.y<dim || eu.x<dim || eu.x>18*dim)
                    eu.lovit[1]=false;
                eu.existaDestinatie=0;
                eu.xUnitate=fireBallPc.xUnitate,eu.yUnitate=fireBallPc.yUnitate;
                eu.distantaParcursa++;

                   if(fireBallPc.deplasareX)
                   {
                        eu.x+=eu.xUnitate;
                        eu.y=(eu.difY*eu.x-eu.pY+eu.pX)/eu.difX;
                   }
                    else
                    {
                        eu.y+=eu.yUnitate;
                        eu.x=(eu.difX*eu.y-eu.pX+eu.pY)/eu.difY;
                    }
            }

    if(eu.existaDestinatie)
        {
            int xUnitate,yUnitate;

                eu.x+=dim/2;
                eu.y+=dim/2;

            if(eu.xDestinatie<eu.x) // merge in stanga
                xUnitate=-1; // scade x
            else
                xUnitate=1; // altfel creste x

            if(eu.yDestinatie<eu.y) // merge in  sus
                yUnitate=-1;
            else
                yUnitate=1;



        if(eu.speed && teleport.distantaParcursa<teleport.distantaParcursaMaxima && !eu.lovit[1] && !eu.lovit[2])
        {
            teleport.distantaParcursa++;
            xUnitate*=8,yUnitate*=8;
        }

    /* inmultesc cu xUnitate respectiv yUnitate pt ca:
    in cazul in care x sau y trebuie sa scada, rezultatul cu minus va schimba semnul */
            if( (eu.xDestinatie-eu.x)*xUnitate > (eu.yDestinatie-eu.y)*yUnitate ) // are mai mult de mers pe Ox
            {
                eu.x+=xUnitate;
                eu.y=(eu.difY*eu.x-eu.pY+eu.pX)/eu.difX;
            }
            else
            {
                eu.y+=yUnitate;
                eu.x=(eu.difX*eu.y-eu.pX+eu.pY)/eu.difY;
            }
                eu.x-=dim/2;
                eu.y-=dim/2;
        }

        if( pow(eu.x-10*dim,2) + pow(eu.y-7*dim,2) > 36*dim*dim && clock()-eu.lastDmg>=300 )
        {
            eu.viata-=5;
            eu.lastDmg=clock();
            if(lastclick!=2)
            {
                char v[5],mv[5];
                sprintf(v,"%d",eu.viata);
                sprintf(mv,"%d",eu.maxViata);
                strcat(mv,"   ");
                strcat(v,"/");
                strcat(v,mv);
                setcolor(WHITE);
                outtextxy(8.5*dim,16*dim-15,v);
            }
        }




// couldown la vraja 1
    timp=clock()-fireBall.timpIncarcare;
    if(timp<fireBall.timpIncarcareMaxim && lastclick!=PC && lastclick)
    {
        char couldown[6];
        sprintf(couldown,"%dx",(fireBall.timpIncarcareMaxim-timp)/10);
        setcolor(WHITE);
        settextstyle(11,0,1);
        outtextxy(15.5*dim,15.5*dim-textheight(couldown),couldown);
        settextstyle(8,0,1);
    }
    else if(lastclick!=PC && lastclick)
    {
        fireBall.deseneazaButon();
        powerZone.deseneazaButon();
    }

// couldown la vraja 2
    timp=clock()-powerZone.timpIncarcare;
    if(timp<powerZone.timpIncarcareMaxim && lastclick!=PC && lastclick)
    {
        char couldown[6];
        sprintf(couldown,"%dx",(powerZone.timpIncarcareMaxim-timp)/10);
        setcolor(WHITE);
        settextstyle(11,0,1);
        outtextxy(16.5*dim,15.5*dim-textheight(couldown),couldown);
        settextstyle(8,0,1);
    }
    else if(lastclick==1)
        powerZone.deseneazaButon();


// couldown la vraja 3
    timp=clock()-teleport.timpIncarcare;
    if(timp<teleport.timpIncarcareMaxim && lastclick!=PC && lastclick)
    {
        char couldown[6];
        sprintf(couldown,"%dx ",(teleport.timpIncarcareMaxim-timp)/10);
        setcolor(WHITE);
        settextstyle(11,0,1);
        outtextxy(17.5*dim+2,15.5*dim-textheight(couldown),couldown);
        settextstyle(8,0,1);
    }
    else if(lastclick!=PC && lastclick)
    {
        teleport.deseneazaButon();
        teleport.distantaParcursa=0;
        eu.speed=0;
    }
}
