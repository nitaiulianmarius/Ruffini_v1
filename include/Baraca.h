class Baraca:public Obiect
{
public:

    void deseneaza(int);

    Baraca(int a,int b)
    {
        x=a;
        y=b;
    }
}baraca(dim,4*dim);


void Baraca::deseneaza(int dimensiune)
{
    setfillstyle(1,RED);
    bar(x,y,x+dimensiune,y+dimensiune);
    outtextxy(x+2,y+2,"BARACA");
}
