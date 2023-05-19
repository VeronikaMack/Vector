#include "mylib.h"
#include "funkcijos.h"
#include "vector.h"


int main()
{

char uzkl, kont;
int kiekstudentu = 0;
while(kont!='v'&&kont!='V'&&kont!='l'&&kont!='L'&&kont!='d'&&kont!='D')
{
cout<<"Koki konteineri naudosite?(v - vector, l - list, d - deque)"<<endl;
cin>>kont;
}
if(kont=='v'||kont=='V')
{
   Vector<studentas> grupe;
   pagr1(grupe);
}
else if(kont=='l'||kont=='L')
{
   list<studentas> grupe;
   pagr2(grupe);
}
else 
{
deque<studentas> grupe;
pagr3(grupe);
}


}