class Button
{
public:

	int x1,y1,x2,y2;
	int nr;
	char text[30];


}buton[30];



bool butonPointer(int nr)
{
	if(buton[nr].x1<=mousex()&&buton[nr].x2>=mousex())
		if(buton[nr].y1<=mousey()&&buton[nr].y2>=mousey())
			return true;
	return false;
}




    void butonCreate(int Nr,int X1,int Y1,int X2,int Y2,char *Text)
	{
	    	buton[Nr].nr=Nr;
            buton[Nr].x1=X1;
            buton[Nr].x2=X2;
            buton[Nr].y1=Y1;
            buton[Nr].y2=Y2;
            strcpy(buton[Nr].text,Text);

            setcolor(RED);
            rectangle(X1,Y1,X2,Y2);

            outtextxy((X1+X2)/2-textwidth(Text)/2,(Y1+Y2)/2-textheight(Text)/2,Text);
	}



bool butonClick(int nr)
{
	    	if(buton[nr].x1<=xMouse&&xMouse<=buton[nr].x2)
                if(buton[nr].y1<=yMouse&&yMouse<=buton[nr].y2)
                    return true;
            return false;
}


void butonUpdate(int nr)
{
    setfillstyle(SOLID_FILL,BLACK);
    bar(buton[nr].x1+1,buton[nr].y1+1,buton[nr].x2-1,buton[nr].y2-1);
    setcolor(RED);
    rectangle(buton[nr].x1,buton[nr].y1,buton[nr].x2,buton[nr].y2);
    setbkcolor(BLACK);

    if(butonPointer(nr))
    {
        setfillstyle(SOLID_FILL,BLUE);
        bar(buton[nr].x1+1,buton[nr].y1+1,buton[nr].x2-1,buton[nr].y2-1);
        setbkcolor(BLUE);
    }

    setcolor(WHITE);
    outtextxy((buton[nr].x1+buton[nr].x2)/2-textwidth(buton[nr].text)/2,(buton[nr].y1+buton[nr].y2)/2-textheight(buton[nr].text)/2,buton[nr].text);

}


void butonUpdateAll(int nr)
{
    for(int i=0;i<nr;i++)
        butonUpdate(i);
}



bool AnybutonClick(int nr)
{
    for(int i=0;i<nr;i++)
        if(butonClick(i))
            return true;

    return false;
}
