
class Calculator:public Obiect
{
public:

    void update();
    void deseneaza(int dimensiune);
    void arataInfo(); // informatiile unui jucator din bara de jos
    bool click();

    Calculator(int a,int b)
    {
        x=a;
        y=b;
        viata=maxViata=100;
        distantaParcursaMaxima=15;
    }
}pc(15*dim,5*dim);




class Jucator:public Obiect
{
public:


    void deseneaza(int);
    bool click();
    void arataInfo();
    void update();

    Jucator(int a,int b)
    {
        x=a;
        y=b;
        viata=maxViata=100;
        distantaParcursaMaxima=15;
        rundeC=rundeP=0;
    };

}eu(4*dim,5*dim);
