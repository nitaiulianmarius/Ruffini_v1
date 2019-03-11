int dim=30; // pixeli/patrat
int xMouse,yMouse; // pt maus
int lastclick,timp; // ultimul click, couldown la vraji
int midX,midY; // jumatatea ecranuli in pixeli
int sound=0; // sunet pornit/oprit
bool saveSlot=true;
bool princSound=true;
#include "irrKlang.h"
using namespace irrklang;
ISoundEngine* xFiles= createIrrKlangDevice();
ISoundEngine* engine = createIrrKlangDevice();
ISoundEngine* vraja1= createIrrKlangDevice();
ISoundEngine* vraja2= createIrrKlangDevice();
ISoundEngine* vraja3= createIrrKlangDevice();
ISoundEngine* vraja1Pc= createIrrKlangDevice();
ISoundEngine* vraja2Pc= createIrrKlangDevice();
ISoundEngine* vraja3Pc= createIrrKlangDevice();
ISoundEngine* defeat= createIrrKlangDevice();

int timesoundvraja1,timesoundvraja2,timesoundvraja3;
int timesoundvraja1Pc,timesoundvraja2Pc,timesoundvraja3Pc;
int timesounddefeat;
bool soundvraja1,soundvraja2,soundvraja3;
bool soundvraja1Pc,soundvraja2Pc,soundvraja3Pc;
bool soundDefeat;
bool runSaveGame;

#include "Obiect.h"
#include "Baraca.h"
#include "structEuPc.h" // declar mai intai structurile jucatorului si calculatorului
#include "Vraja.h"
#include "Calculator.h"
#include "Jucator.h"
#include "Functii.h"
#include "Buton.h"

int meniuPrincipal();
    int startGameMenu();
        int loadGameMenu();
        int commandKeyMenu();
        int productionTeamMenu();
    int readStory();
    int optionsMenu();
        int resolutionOptionsMenu();

void saveGame();

class gameEngine
{
public:

    void update();
    void render();
    void playerInput();
    void afisazaLogo(int,int);
    void init();
    void setFPS(int,int);
    void adjustSound();
    int START();

}GAME;


int gameEngine::START()
{
    int timestart,timestop;

xFiles->stopAllSounds();

        GAME.init();


    while(state!='q')
    {

        if(state=='p')
        {

            GAME.render();

            timestart=GetTickCount();
                GAME.playerInput();
                GAME.update();
                GAME.adjustSound();

                    if(!sound)
                        engine->setAllSoundsPaused(1);
                    else
                        engine->setAllSoundsPaused(0);

            timestop=GetTickCount();

            GAME.setFPS(40,timestop-timestart);

        }

        if(state==27)
        {
            escMenu:

            xMouse=yMouse=-1;
            setfillstyle(SOLID_FILL,BLACK);
            bar(5*dim,2*dim,15*dim,11.5*dim);

                char s[30];
                if(sound)
                    sprintf(s,"Sound is: on");
                else
                    sprintf(s,"Sound is: off");

            char saveText[20]="Save game";
            if(!saveSlot)
                strcpy(saveText,"Nr maxim de salvari!");

            butonCreate(0,6*dim,3*dim,14*dim,4.5*dim,"Resume");
            butonCreate(1,6*dim,5*dim,14*dim,6.5*dim,saveText);
            butonCreate(2,6*dim,7*dim,14*dim,8.5*dim,s);
            butonCreate(3,6*dim,9*dim,14*dim,10.5*dim,"Return to main menu");

            while(!AnybutonClick(4) || butonClick(2))
            {
                butonUpdateAll(4);

                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                    if(butonClick(0))
                        state='p';

                    if(butonClick(1))
                    {
                        saveGame();
                        goto escMenu;
                    }

                    if(butonClick(2)) // Sound options
                    {
                        if(!strcmp(buton[2].text,"Sound is: on"))
                        {
                            sound=0;
                            strcpy(buton[2].text,"Sound is: off");
                        }
                        else
                        {
                            sound=1;
                            strcpy(buton[2].text,"Sound is: on");
                        }
                    }

                    if(butonClick(3))
                    {
                        xMouse=-1;
                        state='p';
                        engine->stopAllSounds();
                        vraja1->stopAllSounds();vraja1Pc->stopAllSounds();
                        vraja3->stopAllSounds();vraja3Pc->stopAllSounds();
                        xFiles->stopAllSounds();

                        closegraph();
                        meniuPrincipal();
                    }

                }

                delay(50);
            }
            if(state=='p')
            {
                xMouse=-1;
                yMouse=-1;
            }
        }


    }
}

void gameEngine::adjustSound()
{
    xFiles->stopAllSounds();

    int T=clock();
    if(T-timesoundvraja1>1000 && soundvraja1)
    {
        vraja1->stopAllSounds();
        soundvraja1=false;
    }
    if(T-timesoundvraja1Pc>1000 && soundvraja1Pc)
    {
        vraja1Pc->stopAllSounds();
        soundvraja1Pc=false;
    }

    if(T-timesoundvraja2>600 && soundvraja2)
    {
        vraja2->stopAllSounds();
        soundvraja2=false;
    }
    if(T-timesoundvraja2Pc>1000 && soundvraja2Pc)
    {
        vraja2Pc->stopAllSounds();
        soundvraja2Pc=false;
    }

    if(T-timesoundvraja3>900 && soundvraja3)
    {
        vraja3->stopAllSounds();
        soundvraja3=false;
    }
    if(T-timesoundvraja3Pc>900 && soundvraja1Pc)
    {
        vraja3Pc->stopAllSounds();
        soundvraja3Pc=false;
    }

    if( (T-timesounddefeat>4000 && soundDefeat)  )
    {
        defeat->stopAllSounds();
        soundDefeat=false;
    }
}


void gameEngine::render()
{
    afisazaFundal();
    eu.deseneaza(dim);
    pc.deseneaza(dim);

    if(fireBall.existaDestinatieVraja1)
        fireBall.deseneazaVraja();

    if(fireBallPc.existaDestinatieVraja1)
        fireBallPc.deseneazaVrajaPc();



    if( (lastclick==VRAJA1 || lastclick==VRAJA3) && mousey()<12.3*dim)
    {
        setcolor(WHITE);
        circle(mousex(),mousey(),0.3*dim);
    }

}


void gameEngine::update()
{
    settextstyle(8,0,1);
    eu.update();
    pc.update();

    if(fireBall.existaDestinatieVraja1)
        fireBall.update();

    if(powerZone.existaDestinatieVraja2)
        powerZone.update();

    if(fireBallPc.existaDestinatieVraja1)
        fireBallPc.updatePc();

    if(powerZonePc.existaDestinatieVraja2)
        powerZonePc.updatePc();

    if(eu.viata<=0 || pc.viata<=0)
    {

        if(sound)
        {
            defeat->play2D("music/defeat.mp3",true);
            timesounddefeat=clock();
            soundDefeat=true;
        }

        if(eu.viata<=0)
        {
            eu.rundeP++;
            animatieFinal(eu);
        }
        else
        {
            eu.rundeC++;
            animatieFinal(pc);
        }

        eu.viata=eu.maxViata;
        pc.viata=pc.maxViata;

        pc.x=14*dim;
        pc.y=5*dim;
        eu.x=5*dim;
        eu.y=5*dim;

        eu.lovit[1]=pc.lovit[1]=0;
        eu.speed=pc.speed=0;
        fireBall.existaDestinatieVraja1=fireBallPc.existaDestinatieVraja1=0;
        powerZone.existaDestinatieVraja2=powerZonePc.existaDestinatieVraja2=0;
        eu.existaDestinatie=pc.existaDestinatie=0;

        if(lastclick!=2)
            eu.arataInfo();

        if(lastclick==2)
            pc.arataInfo();
    }

}


void gameEngine::playerInput()
{
    verificaClickStanga();
    verificaPointer();
    if(!eu.lovit[1])
        verificaClickDreapta();
    verificaKeyBoardHit();
}



void gameEngine::afisazaLogo(int x,int y)
{
    setlinestyle(SOLID_LINE,1,3);
    settextstyle(8,0,3);
    setcolor(WHITE);
    outtextxy(x+12,y,"uffini");
    setcolor(RED);
    line(x,y-20,x,y+15);
    arc(x,y-10,270,90,11);
    line(x,y-2,x+12,y+18);
    setlinestyle(SOLID_LINE,1,1);
    settextstyle(8,0,1);
    setcolor(WHITE);
}



void gameEngine::init()
{
    xFiles->stopAllSounds();
    engine->play2D("music/whileIsRunning.mp3", true);

    pc.x=14*dim;
    pc.y=5*dim;
    eu.x=5*dim;
    eu.y=5*dim;

    eu.lovit[1]=pc.lovit[1]=0;
    eu.speed=pc.speed=0;
    fireBall.existaDestinatieVraja1=fireBallPc.existaDestinatieVraja1=0;
    powerZone.existaDestinatieVraja2=powerZonePc.existaDestinatieVraja2=0;

    if(!runSaveGame)
    {
        eu.rundeC=eu.rundeP=0;
        eu.existaDestinatie=pc.existaDestinatie=0;
    }

    initwindow(20*dim,16*dim,"Ruffini",midX-10*dim,midY-8*dim);
    settextstyle(8,0,1);
    afisazaFundal();
}



void gameEngine::setFPS(int fps,int timp)
{
    if(timp < 1000/fps)
        delay(1000/fps-timp);
}


void saveGame()
{
    FILE *f;
    int n=0;

    f=fopen("load/game.ruff","r");

    fscanf(f,"%d",&n);

    if(n>4)
        saveSlot=false;


    if(saveSlot)
    {
        int i,rundec[10],rundep[10],m=0;
        char titlu[7][20];
        char name[30];

// citeste ce e in fisier
        for(i=0;i<n;i++)
            fscanf(f,"%s %d %d",titlu[i],&rundec[i],&rundep[i]);

        fclose(f);
        f=fopen("load/game.ruff","w");
        fprintf(f,"%d\n",n+1); // baga in fisier n+1
// baga restul datelor iar la final ultima savare de acum
        for(i=0;i<n;i++)
            fprintf(f,"%s %d %d\n",titlu[i],rundec[i],rundep[i]);


        setfillstyle(SOLID_FILL,BLACK);
        bar(5*dim,5*dim,15*dim,10*dim);
        outtextxy(10*dim-textwidth("Enter name")/2,5*dim+10,"Enter name");

        char c;
        do
        {
            c=getch();
            if(m<9)
                if( (c>='0'&&c<='9') || (c>='a' && c<='z') )
                    name[m++]=c,name[m]='\0';

            if(c==8 && !n) //backspace
                name[m--]='\0';

            outtextxy(10*dim-textwidth(name)/2,6*dim,name);
        }while(c!=13 || !m) ; // enter


        fprintf(f,"%s %d %d",name,eu.rundeC,eu.rundeP);
        fclose(f);
    }



fclose(f);

}






int meniuPrincipal()
{
    initwindow(10*dim,11.5*dim,"Ruffini - Main menu",midX-5*dim,midY-6*dim);
    settextstyle(8,0,1);
    GAME.afisazaLogo(5*dim-50,1.5*dim);
    butonCreate(0,dim,3*dim,9*dim,4.5*dim,"Start game");
    butonCreate(1,dim,5*dim,9*dim,6.5*dim,"Read story");
    butonCreate(2,dim,7*dim,9*dim,8.5*dim,"Options");
    butonCreate(3,dim,9*dim,9*dim,10.5*dim,"Exit");

    while(!AnybutonClick(4))
    {
        butonUpdateAll(4);

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

            if(butonClick(0)) // start game
            {
                xMouse=-1;
                closegraph();
                return startGameMenu();
            }

            if(butonClick(1)) // read story
            {
                xMouse=-1;
                closegraph();
                return readStory();
            }

            if(butonClick(2)) // Options
            {
                xMouse=-1;
                closegraph();
                return optionsMenu();
            }

            if(butonClick(3)) // exit
            {
                closegraph();
                return 0;
            }

        }

    delay(50);
    }
}



            int startGameMenu()
            {
                initwindow(10*dim,13.5*dim,"Ruffini - Start game",midX-5*dim,midY-6*dim);
                settextstyle(8,0,1);
                GAME.afisazaLogo(5*dim-50,1.5*dim);
                butonCreate(0,dim,3*dim,9*dim,4.5*dim,"Start new game");
                butonCreate(1,dim,5*dim,9*dim,6.5*dim,"Load game");
                butonCreate(2,dim,7*dim,9*dim,8.5*dim,"Command key");
                butonCreate(3,dim,9*dim,9*dim,10.5*dim,"Production team");
                butonCreate(4,dim,11*dim,9*dim,12.5*dim,"Back");

                while(!AnybutonClick(5))
                {
                    butonUpdateAll(5);

                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                        if(butonClick(0)) // start new game
                        {
                            xMouse=-1;
                            closegraph();
                            runSaveGame=false;
                            return GAME.START();
                        }

                        if(butonClick(1)) // load game
                        {
                            xMouse=-1;
                            closegraph();
                            return loadGameMenu();
                        }

                        if(butonClick(2)) // command key
                        {
                            xMouse=-1;
                            closegraph();
                            return commandKeyMenu();
                        }

                        if(butonClick(3)) // production team
                        {
                            xMouse=-1;
                            closegraph();
                            return productionTeamMenu();
                        }

                        if(butonClick(4)) // back - main menu
                        {
                            xMouse=-1;
                            closegraph();
                            return meniuPrincipal();
                        }

                    }

                delay(50);
                }
            }

                        int loadGameMenu()
                        {

                            int n,i,rundec[10],rundep[10];
                            bool exista[10];
                            char titlu[7][20];
                            int x1=dim,y1=3*dim,x2=14*dim,y2=4.5*dim;

                            initwindow(15*dim,15*dim,"Ruffini - Load game",midX-8*dim,midY-8*dim);
                            GAME.afisazaLogo(7.5*dim-50,1.5*dim);
                            settextstyle(8,0,1);


                            FILE *f=fopen("load/game.ruff","r");

                            fscanf(f,"%d",&n);
                            for(i=0;i<n;i++)
                            {
                                fscanf(f,"%s %d %d",titlu[i],&rundec[i],&rundep[i]);

                                butonCreate(i,x1,y1,x2,y2,titlu[i]);
                                exista[i]=true;
                                y1+=2*dim;
                                y2+=2*dim;
                            }

                            fclose(f);

                            butonCreate(5,dim,13*dim,6.5*dim,14.5*dim,"Delete");
                            butonCreate(6,7*dim,13*dim,14*dim,14.5*dim,"Back");

                            int action=1; // 1 - load
                                            // 0 - delete
                            while(1)
                            {
                                for(i=0;i<n;i++)
                                    butonUpdate(i);
                                butonUpdate(5);
                                butonUpdate(6);


                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                                    if(butonClick(5))
                                        action=0;

                                    for(i=0;i<n;i++)
                                        if(butonClick(i))
                                            if(action)
                                            {
                                                eu.rundeC=rundec[i];
                                                eu.rundeP=rundep[i];
                                                xMouse=-1;
                                                closegraph();
                                                runSaveGame=true;
                                                return GAME.START();
                                            }
                                            else
                                            {

                                                f=fopen("load/game.ruff","w");
                                                fprintf(f,"%d\n",n-1);
                                                for(int j=0;j<n;j++)
                                                    if(j!=i)
                                                        fprintf(f,"%s %d %d\n",titlu[j],rundec[j],rundep[j]);
                                                fclose(f);
                                                xMouse=-1;
                                                closegraph();
                                                return loadGameMenu();

                                            }
                                    if(butonClick(6))
                                    {
                                        xMouse=-1;
                                        closegraph();
                                        return startGameMenu();
                                    }
                                }




                                delay(50);
                            }
                        }

                        int commandKeyMenu()
                        {
                            initwindow(21*dim,13*dim,"Ruffini - Command key",getmaxwidth()/2-10*dim,getmaxheight()/2-8*dim);

                            GAME.afisazaLogo(10*dim-50,1.5*dim);
                            settextstyle(8,0,1);
                            setcolor(WHITE);
                            outtextxy(dim,4*dim,"Selecteaza vrajitorul tau");
                            outtextxy(dim,4*dim+18,"Selecteaza vrajitorul oponent");
                            outtextxy(dim,4*dim+36,"Intoarcere la meniu");
                            outtextxy(dim,4*dim+54,"Deplasare jucator");
                            outtextxy(dim,4*dim+72,"Anulare vraja");
                            outtextxy(dim,4*dim+90,"Opreste vrajitorul(din mers)");
                            setcolor(YELLOW);
                            outtextxy(15*dim,4*dim,"1");
                            outtextxy(15*dim,4*dim+18,"2");
                            outtextxy(15*dim,4*dim+36,"Esc");
                            outtextxy(15*dim,4*dim+54,"click dreapta");
                            outtextxy(15*dim,4*dim+72,"click dreapta");
                            outtextxy(15*dim,4*dim+90,"S");


                            butonCreate(0,12.5*dim,11*dim,20.5*dim,12.5*dim,"Back");

                            while(!butonClick(0))
                            {
                                butonUpdate(0);

                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                                    if(butonClick(0))
                                    {
                                        xMouse=-1;
                                        closegraph();
                                        return startGameMenu();
                                    }
                                }

                                delay(50);
                            }
                        }

                        int productionTeamMenu()
                        {
                            initwindow(20*dim,13*dim,"Ruffini - Production team",midX-10*dim,midY-5*dim);
                            GAME.afisazaLogo(10*dim-50,1.5*dim);

                            settextstyle(8,0,1);
                            outtextxy(1.3*dim,6.3*dim,"Nita Iulian");
                            outtextxy(14.3*dim,6.3*dim,"Stefan Vlad");
                            outtextxy(1.7*dim,8*dim,"-algoritmul jocului");
                            outtextxy(1.7*dim,8*dim+20,"-diagrama UML");
                            outtextxy(11*dim,8*dim,"-grafica joc");
                            outtextxy(11*dim,8*dim+20,"-text");

                            settextstyle(11,0,1);
                            outtextxy(1.3*dim,11.2*dim,"Data incepere proiect: 08.03.2014");
                            outtextxy(1.3*dim,12*dim,"Durata proiect: 5 saptamani");

                            setfillstyle(1,BLUE);
                            bar(1*dim,7.3*dim,19*dim,7.4*dim);
                            bar(10*dim,6*dim,10.2*dim,10*dim);
                            setfillstyle(1,RED);
                            bar(1*dim,11*dim,8*dim,11.1*dim);
                            bar(8*dim,11*dim,8.1*dim,13*dim);

                            settextstyle(8,0,1);

                            butonCreate(0,11.5*dim,11*dim,19.5*dim,12.5*dim,"Back");

                            while(!butonClick(0))
                            {
                                butonUpdate(0);

                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                                    if(butonClick(0))
                                    {
                                        xMouse=-1;
                                        closegraph();
                                        return startGameMenu();
                                    }
                                }

                                delay(50);
                            }

                        }


            int readStory()
            {

                initwindow(24*dim,14*dim,"Ruffini - Story",midX-10*dim,midY-10*dim);
                settextstyle(8,0,1);
                GAME.afisazaLogo(12*dim-50,1.5*dim);

                outtextxy(2*dim,3*dim,"In toamna anului 1992 Marele Hudini impreuna cu fiul sau,");
                outtextxy(dim,3*dim+20,"Ruffini, a fost la un simpozion vrajitoresc.");
                outtextxy(2*dim,3*dim+40,"Marii vrajitori din toata lumea s-au adunat aici");
                outtextxy(dim,3*dim+60,"pentru a arata ce stiu mai bine. Din pacate Ruffini");
                outtextxy(dim,3*dim+80,"a pierdut in competitie in nenumarate randuri in fata altor");
                outtextxy(dim,3*dim+100,"vrajitori. Marele Hudini, enervat la culme, l-a alungat pe");
                outtextxy(dim,3*dim+120,"fiul sau de acasa din cauza rusinii aduse familiei sale.");
                outtextxy(2*dim,3*dim+140,"Acum Ruffini este hotarat sa recapete prestanta familiei");
                outtextxy(dim,3*dim+160,"si sa se intoarca in arena pentru a se antrena.");
                outtextxy(dim,3*dim+180,"Abia dupa 100 de reusite impotriva celor mai temuti");
                outtextxy(dim,3*dim+200,"vrajitori se va putea intoarce acasa cu capul sus");
                outtextxy(2*dim,3*dim+220,"Va reusi Ruffini sa dovedeasca ca este demn pentru a");
                outtextxy(dim,3*dim+240,"purta numele familiei Marelui Hudini ?");

                butonCreate(0,15.5*dim,12*dim,23.5*dim,13.5*dim,"Back");

                while(!AnybutonClick(1))
                {
                    butonUpdate(0);

                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                        if(butonClick(0))
                        {
                            xMouse=-1;
                            closegraph();
                            return meniuPrincipal();
                        }
                    }

                    delay(50);
                }
            }



            int optionsMenu()
            {
                initwindow(10*dim,11.5*dim,"Ruffini - Options",midX-5*dim,midY-6*dim);
                settextstyle(8,0,1);
                GAME.afisazaLogo(5*dim-50,1.5*dim);

                char s[30];

                if(sound)
                    sprintf(s,"Sound is: on");
                else
                    sprintf(s,"Sound is: off");

                butonCreate(0,dim,3*dim,9*dim,4.5*dim,s);
                butonCreate(1,dim,5*dim,9*dim,6.5*dim,"Resolution");
                butonCreate(2,dim,7*dim,9*dim,8.5*dim,"FPS");
                butonCreate(3,dim,9*dim,9*dim,10.5*dim,"Back");

                while(!AnybutonClick(4) || butonClick(0))
                {
                    butonUpdateAll(4);

                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                        if(butonClick(0)) // Sound options
                        {
                            if(!strcmp(buton[0].text,"Sound is: on"))
                            {
                                sound=0;
                                strcpy(buton[0].text,"Sound is: off");
                            }
                            else
                            {
                                sound=1;
                                strcpy(buton[0].text,"Sound is: on");
                            }
                        }

                        if(butonClick(1)) // resolution options
                        {
                            xMouse=-1;
                            closegraph();
                            return resolutionOptionsMenu();
                        }

                        if(butonClick(2)) // fps options
                        {
                            ;
                        }

                        if(butonClick(3)) // back - main menu
                        {
                            xMouse=-1;
                            closegraph();
                            return meniuPrincipal();
                        }

                    }
                delay(50);
                }
            }



                        int resolutionOptionsMenu()
                        {
                            dim=30;
                            initwindow(19*dim,8.5*dim,"Ruffini - Resolution options",midX-10*dim,midY-5*dim);
                            settextstyle(8,0,1);
                            GAME.afisazaLogo(8*dim,1.5*dim);

                            outtextxy(dim+10,3*dim,"Ferestrele jocului sunt impartite in patrate,");
                            outtextxy(dim,3*dim+15,"un patrat este caracterizat de un numar de pixeli.");
                            outtextxy(dim,3*dim+30,"Alegeti numarul de pixeli al unui patrat");
                            outtextxy(dim,3*dim+45,"[intre 28 si 45]: ");
                            butonCreate(0,dim,6*dim,9*dim,7.5*dim,"Apply");
                            butonCreate(1,10*dim,6*dim,18*dim,7.5*dim,"Back");

                            int nr=0;

                            while(!butonClick(1))
                            {
                                butonUpdate(1);

                                if(nr>=28&&nr<=45)
                                    butonUpdate(0);


                                if(kbhit())
                                {
                                    char c;
                                    c=getch();

                                    if(c>='0' && c<='9' && nr<100)
                                        nr=nr * 10 + c-48;

                                    if(c==8) // backspace
                                        nr/=10;

                                    char nrchar[10];
                                    sprintf(nrchar,"%d    ",nr);
                                    outtextxy(dim+textwidth("[intre 28 si 45]: "),3*dim+45,nrchar);
                                }


                                if(ismouseclick(WM_LBUTTONDOWN))
                                {

                                    getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                                    if(butonClick(0) && nr<=45 && nr>=22)
                                    {
                                        dim=nr;
                                        xMouse=-1;
                                        closegraph();
                                        return optionsMenu();
                                    }

                                    if(butonClick(1))
                                    {
                                        xMouse=-1;
                                        closegraph();
                                        return optionsMenu();
                                    }
                                }

                                delay(50);
                            }
                        }




