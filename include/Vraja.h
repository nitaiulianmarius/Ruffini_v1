#include<math.h>
#include<iostream.h>
class Vraja:public Obiect
{
public:
    int raza;
    int distantaParcursa,distantaParcursaMaxima;
    int timpIncarcare,timpIncarcareMaxim;
    bool deplasareX,deplasareY;

    void deseneazaButon();
    void deseneazaVraja();
    void update();
    bool click(); // pe buton

    Vraja()
    {
        raza=0.35*dim;
    }


};



class _1_FIREBALL:public Vraja{
public:

    int existaDestinatieVraja1;
    int xUnitate,yUnitate;

    void deseneazaButon();
    void deseneazaVraja();
    void update();
    bool click(); // pe buton
    bool pointer();
    void arataInfo(int,int);

    void deseneazaVrajaPc();
    void updatePc();

    _1_FIREBALL()
    {
        distantaParcursaMaxima=0.75*dim;
        timpIncarcareMaxim=2000;
    }

    }fireBall,fireBallPc; // dmg + impinge



class _2_POWERZONE:public Vraja{
public:

    int existaDestinatieVraja2;
    int xUnitate,yUnitate;

    void deseneazaButon();
    void deseneazaVraja();
    void update();
    bool click(); // pe buton
    bool pointer();
    void arataInfo(int,int);

    void deseneazaVrajaPc();
    void updatePc();

    _2_POWERZONE()
    {
        distantaParcursaMaxima=2.5*dim;
        distantaParcursa=0.5*dim;
        timpIncarcareMaxim=5000;
    }

    }powerZone,powerZonePc; // impinge



class _3_TELEPORT:public Vraja{
public:

    int existaDestinatieVraja3;

    void deseneazaButon();
    bool click(); // pe buton

    void deseneazaVrajaPc();
    void updatePc();
    bool pointer();
    void arataInfo(int,int);

    _3_TELEPORT()
    {
        distantaParcursaMaxima=0.5*dim;
        timpIncarcareMaxim=1000;
    }

    }teleport,teleportPc; // teleporteaz dint-un punct in altul





void _1_FIREBALL::deseneazaButon()
{

    setfillstyle(1,0);
    bar(15.5*dim,14.5*dim,176*dim,15.5*dim);


    setcolor(MAGENTA);
	setfillstyle(SOLID_FILL,MAGENTA);
	fillellipse(16*dim,15*dim,0.49*dim,0.49*dim);
	setcolor(BLUE);
	setfillstyle(1,BLUE);
	fillellipse(16*dim,15*dim,0.35*dim,0.35*dim);
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	fillellipse(16*dim,15*dim,0.2*dim,0.2*dim);
	setcolor(DARKGRAY);
	setfillstyle(1,DARKGRAY);
	fillellipse(16*dim,15*dim,0.1*dim,0.1*dim);
};



void _1_FIREBALL::deseneazaVraja()
{
    setfillstyle(SOLID_FILL,RED);
    setcolor(YELLOW);
    fillellipse(fireBall.x,fireBall.y,fireBall.raza,fireBall.raza);

}



bool _1_FIREBALL::click()
{
    if(15.5*dim < xMouse && xMouse < 16.5*dim)
        if(14.5*dim < yMouse && yMouse < 15.5*dim)
            return true;
    return false;
}

bool _1_FIREBALL::pointer()
{
    if(15.5*dim<mousex() && mousex() < 16.5*dim)
		if(14.5*dim<mousey() && mousey() < 15.5*dim)
			return true;
	return false;
}


void _1_FIREBALL::update()
{

    if(fireBall.xDestinatie<fireBall.x) // merge in stanga
        fireBall.xUnitate=-5; // scade x
    else
        fireBall.xUnitate=5; // altfel creste x

    if(fireBall.yDestinatie<fireBall.y) // merge in  sus
        fireBall.yUnitate=-5;
    else
        fireBall.yUnitate=5;



    if( (abs(fireBall.x-fireBall.xDestinatie)<6 && abs(fireBall.y-fireBall.yDestinatie)<6) || fireBall.distantaParcursa>fireBall.distantaParcursaMaxima)
    {
        fireBall.existaDestinatieVraja1=0;
        fireBall.distantaParcursa=0;
        fireBall.x=-1;
        fireBall.y=-1;
    }


    if(fireBall.existaDestinatieVraja1)
    {
    /* inmultesc cu xUnitate respectiv yUnitate pt ca:
    in cazul in care x sau y trebuie sa scada, rezultatul cu minus va schimba semnul */
        if( (fireBall.xDestinatie-fireBall.x)*fireBall.xUnitate > (fireBall.yDestinatie-fireBall.y)*fireBall.yUnitate ) // are mai mult de mers pe Ox
        {
            fireBall.x+=fireBall.xUnitate;
            fireBall.y=(fireBall.difY*fireBall.x-fireBall.pY+fireBall.pX)/fireBall.difX;
            fireBall.distantaParcursa++;
            fireBall.deplasareX=true;
            fireBall.deplasareY=false;
        }

        else
        {
            fireBall.y+=fireBall.yUnitate;
            fireBall.x=(fireBall.difX*fireBall.y-fireBall.pX+fireBall.pY)/fireBall.difY;
            fireBall.distantaParcursa++;
            fireBall.deplasareX=false;
            fireBall.deplasareY=true;
        } // folosesc deplasareX si deplasareY pt a sti ce se moifica in deplasarea mingii
            // mai tarziu ma folosesc de asta pt a sti cum deplasez calculator in caz de coliziune

        // verifica coliziune
        pc.x+=(dim>>1);
        pc.y+=(dim>>1);

        if( pow(abs(fireBall.x-pc.x),2) + pow(abs(fireBall.y-pc.y),2) <= pow(fireBall.raza+dim/2,2) )
        {
            pc.viata--;

            if(lastclick==2)
            {
                char v[5],mv[5];
                sprintf(v,"%d",pc.viata);
                sprintf(mv,"%d",pc.maxViata);
                strcat(mv,"   ");
                strcat(v,"/");
                strcat(v,mv);
                setcolor(WHITE);
                outtextxy(8.5*dim,16*dim-15,v);
            }

            pc.x-=(dim>>1);
            pc.y-=(dim>>1);
            pc.difX=fireBall.difX;
            pc.difY=fireBall.difY;
            pc.pX=pc.difX*pc.y;
            pc.pY=pc.difY*pc.x;
            pc.existaDestinatie=0;
            pc.lovit[1]=true;
        }

        else
        {
            pc.x-=(dim>>1);
            pc.y-=(dim>>1);
        }

    }

}


void _1_FIREBALL::arataInfo(int x,int y)
{
    setcolor(RED);
    rectangle(x,y,x+ 7.5*dim,y+75);
    setcolor(WHITE);
    settextstyle(11,0,1);
    outtextxy(x+10 , y+5 , " Fire Ball (     ) " );
    setcolor(YELLOW);
    outtextxy(x+10+textwidth(" Fire Ball ( "),y+5,"Q" );
    setcolor(WHITE);
    outtextxy(x+5 , y+25 , "Impinge jucatorul in spate si ii scade");
    outtextxy(x+5 , y+40 , "din viata in functie de cat de departe" );
    outtextxy(x+5 , y+55 , "aruncati vraja (max 15 dmg)");
}

void _1_FIREBALL::deseneazaVrajaPc()
{
    setfillstyle(SOLID_FILL,BLUE);
    setcolor(RED);
    fillellipse(fireBallPc.x,fireBallPc.y,fireBallPc.raza,fireBallPc.raza);
}


void _1_FIREBALL::updatePc()
{
    if(fireBallPc.xDestinatie<fireBallPc.x) // merge in stanga
        fireBallPc.xUnitate=-5; // scade x
    else
        fireBallPc.xUnitate=5; // altfel creste x

    if(fireBallPc.yDestinatie<fireBallPc.y) // merge in  sus
        fireBallPc.yUnitate=-5;
    else
        fireBallPc.yUnitate=5;



    if( (abs(fireBallPc.x-fireBallPc.xDestinatie)<6 && abs(fireBallPc.y-fireBallPc.yDestinatie)<6) || fireBallPc.distantaParcursa>fireBallPc.distantaParcursaMaxima)
    {
        fireBallPc.existaDestinatieVraja1=0;
        fireBallPc.distantaParcursa=0;
    }


    if(fireBallPc.existaDestinatieVraja1)
    {
    /* inmultesc cu xUnitate respectiv yUnitate pt ca:
    in cazul in care x sau y trebuie sa scada, rezultatul cu minus va schimba semnul */
        if( (fireBallPc.xDestinatie-fireBallPc.x)*fireBallPc.xUnitate > (fireBallPc.yDestinatie-fireBallPc.y)*fireBallPc.yUnitate ) // are mai mult de mers pe Ox
        {
            fireBallPc.x+=fireBallPc.xUnitate;
            fireBallPc.y=(fireBallPc.difY*fireBallPc.x-fireBallPc.pY+fireBallPc.pX)/fireBallPc.difX;
            fireBallPc.distantaParcursa++;
            fireBallPc.deplasareX=true;
            fireBallPc.deplasareY=false;
        }

        else
        {
            fireBallPc.y+=fireBallPc.yUnitate;
            fireBallPc.x=(fireBallPc.difX*fireBallPc.y-fireBallPc.pX+fireBallPc.pY)/fireBallPc.difY;
            fireBallPc.distantaParcursa++;
            fireBallPc.deplasareX=false;
            fireBallPc.deplasareY=true;
        } // folosesc deplasareX si deplasareY pt a sti ce se moifica in deplasarea mingii
            // mai tarziu ma folosesc de asta pt a sti cum deplasez calculator in caz de coliziune

        // verifica coliziune
        eu.x+=(dim>>1);
        eu.y+=(dim>>1);

        if( pow(abs(fireBallPc.x-eu.x),2) + pow(abs(fireBallPc.y-eu.y),2) <= pow(fireBallPc.raza+dim/2,2) )
        {
            eu.viata--;
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

            eu.difX=fireBallPc.difX;
            eu.difY=fireBallPc.difY;
            eu.pX=fireBallPc.pX;
            eu.pY=fireBallPc.pY;
            eu.existaDestinatie=0;
            eu.lovit[1]=true;
            eu.x-=(dim>>1);
            eu.y-=(dim>>1);
        }

        else
        {
            eu.x-=(dim>>1);
            eu.y-=(dim>>1);
        }

    }
}





void _2_POWERZONE::deseneazaButon()
{
    setfillstyle(1,0);
    bar(16.5*dim,14.5*dim,17.5*dim,15.5*dim);

    setcolor(LIGHTCYAN);
	setfillstyle(1,LIGHTCYAN);
	fillellipse(17*dim+1,15*dim,0.35*dim,0.35*dim);
	setcolor(RED);
	line(16.55*dim+1,15*dim,17.45*dim,15*dim);
	line(17*dim+1,14.55*dim,17*dim+1,15.45*dim);
	line(16.6*dim+1,14.6*dim,17.4*dim+1,15.4*dim);
	line(17.4*dim+1,14.6*dim,16.6*dim+1,15.4*dim);

	line(16.97*dim+1,14.59*dim,17*dim+1,14.55*dim);
	line(17.03*dim+1,14.59*dim,17*dim+1,14.55*dim);

	line(16.97*dim+1,15.41*dim,17*dim+1,15.45*dim);
	line(17*dim+1,15.45*dim,17.03*dim+1,15.41*dim);

	line(16.55*dim+1,15*dim,16.59*dim+1,14.97*dim);
    line(16.55*dim+1,15*dim,16.59*dim+1,15.03*dim);

    line(17.45*dim+1,15*dim,17.42*dim+1,15.03*dim);
    line(17.45*dim+1,15*dim,17.42*dim+1,14.97*dim);

    line(16.6*dim+1,14.6*dim,16.62*dim+1,14.66*dim);
    line(16.6*dim+1,14.6*dim,16.65*dim+1,14.61*dim);

    line(17.4*dim+1,14.6*dim,17.38*dim+1,14.67*dim);
    line(17.4*dim+1,14.6*dim,17.35*dim+1,14.62*dim);

    line(16.6*dim+1,15.4*dim,16.62*dim+1,15.35*dim);
    line(16.6*dim+1,15.4*dim,16.65*dim+1,15.39*dim);

    line(17.4*dim+1,15.4*dim,17.34*dim+1,15.38*dim);
    line(17.4*dim+1,15.4*dim,17.38*dim+1,15.33*dim);
}


void _2_POWERZONE::deseneazaVraja()
{
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    setcolor(YELLOW);
    fillellipse(eu.x+dim/2,eu.y+dim/2,powerZone.raza,powerZone.raza);
}


bool _2_POWERZONE::click()
{
    if(16.5*dim+1 < xMouse && xMouse < 17.5*dim+1)
        if(14.5*dim < yMouse && yMouse < 15.5*dim)
            return true;
    return false;
}

bool _2_POWERZONE::pointer()
{
    if(16.5*dim+1 < mousex() && mousex() < 17.5*dim+1)
        if(14.5*dim < mousey() && mousey() < 15.5*dim)
            return true;
    return false;
}


void _2_POWERZONE::update()
{

    if(powerZone.distantaParcursa>powerZone.distantaParcursaMaxima)
    {
        powerZone.distantaParcursa=dim/2;
        powerZone.existaDestinatieVraja2=0;
    }

    if(powerZone.existaDestinatieVraja2)
    {
        powerZone.distantaParcursa+=3;
        powerZone.raza=powerZone.distantaParcursa;
        powerZone.deseneazaVraja();
        if(lastclick!=2)
            eu.arataInfo();
    }

    if( pow(abs(eu.x-fireBallPc.x),2) + pow(abs(eu.y-fireBallPc.y),2) <= pow(powerZone.distantaParcursa,2) )
        fireBallPc.existaDestinatieVraja1=0;


}

void _2_POWERZONE::arataInfo(int x,int y)
{
    setcolor(RED);
    rectangle(x,y,x+ 7.5*dim,y+75);
    setcolor(WHITE);
    settextstyle(11,0,1);
    outtextxy(x+10 , y+5 , " Power Zone (      ) " );
    setcolor(YELLOW);
    outtextxy(x+10+textwidth(" Power Zone ( "),y+5,"W" );
    setcolor(WHITE);
    outtextxy(x+5 , y+25 , "Formeaza in jur un scut de protectie ");
    outtextxy(x+5 , y+40 , "care blocheaza vraja oponentului" );
}

void _2_POWERZONE::deseneazaVrajaPc()
{
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    setcolor(WHITE_BRUSH);
    fillellipse(pc.x+dim/2,pc.y+dim/2,powerZonePc.raza,powerZonePc.raza);
}

void _2_POWERZONE::updatePc()
{

    if(powerZonePc.distantaParcursa>powerZonePc.distantaParcursaMaxima)
    {
        powerZonePc.distantaParcursa=dim/2;
        powerZonePc.existaDestinatieVraja2=0;
    }

    if(powerZonePc.existaDestinatieVraja2)
    {
        powerZonePc.distantaParcursa+=3;
        powerZonePc.raza=powerZonePc.distantaParcursa;
        powerZonePc.deseneazaVrajaPc();
    }

    if( pow(abs(eu.x-fireBall.x),2) + pow(abs(eu.y-fireBall.y),2) <= pow(powerZonePc.distantaParcursa,2) )
        fireBall.existaDestinatieVraja1=0;


}




void _3_TELEPORT::deseneazaButon()
{

    setfillstyle(1,0);
    bar(17.5*dim,14.5*dim,18.5*dim,15.5*dim);

    setcolor(BLUE);
	setfillstyle(1,BLUE);
	fillellipse(18*dim+2,15*dim,0.49*dim,0.49*dim);
	setcolor(LIGHTBLUE);
	setfillstyle(1,LIGHTBLUE);
	fillellipse(18*dim+2,15*dim,0.3*dim,0.3*dim);
    setcolor(WHITE);
	setfillstyle(1,WHITE);
	fillellipse(18*dim+2,15*dim,0.1*dim,0.1*dim);
}



bool _3_TELEPORT::click()
{
    if(17.5*dim+2 < xMouse && xMouse < 18.5*dim+2)
        if(14.5*dim < yMouse && yMouse < 15.5*dim)
            return true;
    return false;
}

bool _3_TELEPORT::pointer()
{
    if(17.5*dim+2 < mousex() && mousex() < 18.5*dim+2)
        if(14.5*dim < mousey() && mousey() < 15.5*dim)
            return true;
    return false;
}

void _3_TELEPORT::arataInfo(int x,int y)
{
    setcolor(RED);
    rectangle(x,y,x+ 7.5*dim,y+75);
    setcolor(WHITE);
    settextstyle(11,0,1);
    outtextxy(x+10 , y+5 , " Teleport (     ) " );
    setcolor(YELLOW);
    outtextxy(x+10+textwidth(" Teleport ( "),y+5,"E" );
    setcolor(WHITE);
    outtextxy(x+5 , y+25 , " Da viteza eroului spre o destinatie ");
    outtextxy(x+5 , y+40 , " pentru o distanta limitata" );
}

