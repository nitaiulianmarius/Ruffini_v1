#include<time.h>

void Calculator::deseneaza(int dimensiune)
{



            if(dimensiune==dim)
            {

                if(lastclick==2) // eu
                {
                    setcolor(BLACK);
                    circle(pc.x+0.5*dimensiune,pc.y+0.5*dimensiune,0.9*dimensiune);
                }

                // viata
                if(pc.viata>0)
                {
                    setfillstyle(1,WHITE);
                    bar( pc.x+3, pc.y-5, pc.x+(float)pc.viata/pc.maxViata*dim, pc.y-2 );
                }
            }

    if(pc.speed && teleportPc.distantaParcursa<teleportPc.distantaParcursaMaxima && dim==dimensiune && pc.lovit[1])
    {
        setfillstyle(SOLID_FILL,BLACK);
        setcolor(WHITE);
        fillellipse(pc.x+dim/2,pc.y+dim/2,dim,dim);
    }

    else
    {
        setfillstyle(1,BROWN);
        bar(pc.x+0.25*dimensiune,pc.y+0.02*dimensiune,pc.x+0.75*dimensiune,pc.y+0.5*dimensiune);
        setfillstyle(1,BLUE);
        bar(pc.x+0.35*dimensiune,pc.y+0.51*dimensiune,pc.x+0.65*dimensiune,pc.y+0.85*dimensiune);
        setfillstyle(1,RED);
        bar(pc.x+0.35*dimensiune,pc.y+0.1*dimensiune,pc.x+0.65*dimensiune,pc.y+0.21*dimensiune);
        bar(pc.x+0.35*dimensiune,pc.y+0.35*dimensiune,pc.x+0.65*dimensiune,pc.y+0.37*dimensiune);
        setfillstyle(1,YELLOW);
        bar(pc.x+0.16*dimensiune,pc.y+0.51*dimensiune,pc.x+0.35*dimensiune,pc.y+0.75*dimensiune);
        bar(pc.x+0.65*dimensiune,pc.y+0.51*dimensiune,pc.x+0.84*dimensiune,pc.y+0.75*dimensiune);
        setfillstyle(1,WHITE);
        bar(pc.x+0.2*dimensiune,pc.y+0.85*dimensiune,pc.x+0.45*dimensiune,pc.y+0.95*dimensiune);
        bar(pc.x+0.55*dimensiune,pc.y+0.85*dimensiune,pc.x+0.8*dimensiune,pc.y+0.95*dimensiune);
    }
}

bool Calculator::click()
{

    if(pc.x < xMouse && xMouse < pc.x+dim)
        if(pc.y < yMouse && yMouse < pc.y+dim)
            return true;
    return false;
}


void Calculator::arataInfo()
{

    setfillstyle(1,BLACK);
    bar(0,13*dim,20*dim,16*dim);

    int x,y;
    x=pc.x;pc.x=8.5*dim;
    y=pc.y;pc.y=13.5*dim;
    pc.deseneaza(2*dim);
    pc.x=x;
    pc.y=y;

    setcolor(WHITE);

    char v[5],mv[5];
    sprintf(v,"%d",pc.viata);
    sprintf(mv,"%d",pc.maxViata);
    strcat(mv,"   ");
    strcat(v,"/");
    strcat(v,mv);
    outtextxy(8.5*dim,16*dim-15,v);


    outtextxy(dim,14*dim,"La multi ani Cristi !");
    outtextxy(dim,15*dim,"De la Presidente ");

}


void Calculator::update()
{
    int xUnitate,yUnitate;

    if(pc.x+dim/2==pc.xDestinatie && pc.y+dim/2==pc.yDestinatie)
        pc.existaDestinatie=0; // daca a ajuns la destinatie se opreste din update
                        // imediat dupa asta va cauta o alta destinatie apropiata si convenabila

    if((pc.x<dim/2 || pc.x>19*dim-1 || pc.y<dim || pc.y>12*dim-1) && (pc.lovit[1])) // a ajuns la margine, s-a oprit !
    {
        pc.distantaParcursa=0;
        pc.lovit[1]=false;

        pc.y-=dim;
        pc.x-=dim;

    }


            if(pc.lovit[1])
            {
                if(pc.y>12*dim || pc.y<dim || pc.x<dim || pc.x>18*dim)
                    pc.lovit[1]=false;

                pc.existaDestinatie=0;
                xUnitate=fireBall.xUnitate,yUnitate=fireBall.yUnitate;
                pc.distantaParcursa++;

                   if(fireBall.deplasareX)
                   {
                        pc.x+=xUnitate;
                        pc.y=(pc.difY*pc.x-pc.pY+pc.pX)/pc.difX;
                   }
                    else
                    {
                        pc.y+=yUnitate;
                        pc.x=(pc.difX*pc.y-pc.pX+pc.pY)/pc.difY;
                    }
            }





    if(pc.existaDestinatie) // daca exista o destinatie merge cu 1 pixel mai aproape
        {

                pc.x+=dim/2;
                pc.y+=dim/2;

            if(pc.xDestinatie<pc.x) // merge in stanga
                xUnitate=-1; // scade x
            else
                xUnitate=1; // altfel creste x

            if(pc.yDestinatie<pc.y) // merge in  sus
                yUnitate=-1;
            else
                yUnitate=1;

        // cannd este in vraja a 3-a
        if(pc.speed && teleportPc.distantaParcursa<teleportPc.distantaParcursaMaxima && !pc.lovit[1])
        {
            teleportPc.distantaParcursa++;
            xUnitate*=8,yUnitate*=8;
        }

    /* inmultesc cu xUnitate respectiv yUnitate pt ca:
    in cazul in care x sau y trebuie sa scada, rezultatul cu minus va schimba semnul */
            if( (pc.xDestinatie-pc.x)*xUnitate > (pc.yDestinatie-pc.y)*yUnitate ) // are mai mult de mers pe Ox
            {
                pc.x+=xUnitate;
                pc.y=(pc.difY*pc.x-pc.pY+pc.pX)/pc.difX;
            }
            else
            {
                pc.y+=yUnitate;
                pc.x=(pc.difX*pc.y-pc.pX+pc.pY)/pc.difY;
            }
                pc.x-=dim/2;
                pc.y-=dim/2;
        }


    if(!pc.existaDestinatie && !pc.lovit[1]) // daca nu exista destinatie: cauta una
    {
        srand(time(NULL));
        pc.xDestinatie=pc.x+ rand()%(3*dim)-1.5*dim;
        pc.yDestinatie=pc.y+ rand()%(3*dim)-1.5*dim;

            pc.x+= (dim>>1); // jumate
            pc.y+= (dim>>1); // jumate
            pc.difX=pc.xDestinatie-pc.x;
            pc.difY=pc.yDestinatie-pc.y;
            pc.pX=pc.difX*pc.y;
            pc.pY=pc.difY*pc.x;
            pc.x-= (dim>>1);
            pc.y-= (dim>>1);
            pc.existaDestinatie=1;
    }

            if(pc.distantaParcursa>=pc.distantaParcursaMaxima)
            {
                pc.distantaParcursa=0;
                pc.lovit[1]=false;
                pc.lovit[2]=false;
            }
            if(teleportPc.distantaParcursa>=teleportPc.distantaParcursa)
            {
                teleportPc.distantaParcursa=0;
                pc.speed=0;
            }

        if( pow(pc.x-10*dim,2) + pow(pc.y-7*dim,2) > 36*dim*dim && clock()-pc.lastDmg>=300 )
        {
            pc.viata-=5;
            pc.lastDmg=clock();

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
        }



    /// foloseste vraja 1
    if( abs(pc.x-eu.x) + abs(pc.y-eu.y) <= 7*dim-3 && clock()-fireBallPc.timpIncarcare>fireBallPc.timpIncarcareMaxim)
       {

            if(sound)
            {

                vraja1Pc->play2D("music/fireBall.ogg",true);
                timesoundvraja1Pc=clock();
                soundvraja1Pc=true;
            }

            eu.x+=dim/2;
            eu.y+=dim/2;
            fireBallPc.x=pc.x+dim/2;
            fireBallPc.y=pc.y+dim/2;
            fireBallPc.difX=eu.x-fireBallPc.x;
            fireBallPc.difY=eu.y-fireBallPc.y;
            fireBallPc.pX=fireBallPc.difX*fireBallPc.y;
            fireBallPc.pY=fireBallPc.difY*fireBallPc.x;
            fireBallPc.xDestinatie=eu.x;
            fireBallPc.yDestinatie=eu.y;
            fireBallPc.existaDestinatieVraja1=1;
            fireBallPc.timpIncarcare=clock();
            eu.x-=dim/2;
            eu.y-=dim/2;
       }

    /// foloseste vraja 2
    if(pow(pc.x-fireBall.x,2)+pow(pc.y-fireBall.y,2)<=40*dim*dim && clock()-powerZonePc.timpIncarcare>powerZonePc.timpIncarcareMaxim)
    {
        powerZonePc.existaDestinatieVraja2=1;
        powerZonePc.timpIncarcare=clock();
    }


    /// foloseste vraja 3
    if( pow(pc.x-10*dim,2) + pow(pc.y-7*dim,2) > 36*dim*dim  && clock()-teleportPc.timpIncarcare>teleportPc.timpIncarcareMaxim)
    {
            if(sound)
            {
                vraja3Pc->play2D("music/teleport.wav",true);
                timesoundvraja3Pc=clock();
                soundvraja3Pc=true;
            }

            pc.x+= (dim>>1); // jumate
            pc.y+= (dim>>1); // jumate
            pc.difX=10*dim-pc.x;
            pc.difY=7*dim-pc.y;
            pc.pX=pc.difX*pc.y;
            pc.pY=pc.difY*pc.x;
            pc.xDestinatie=10*dim;
            pc.yDestinatie=7*dim;
            pc.x-= (dim>>1);
            pc.y-= (dim>>1);
            pc.existaDestinatie=1;
            pc.speed=1;
            teleportPc.timpIncarcare=clock();
    }
}
