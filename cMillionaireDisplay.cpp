#include "cMillionaire.h"




void cMillionaire::SelectQuestion(int stage)
{
    selectedQuestion = rand()%vData[stage].size();
}
void cMillionaire::DisplayQuestion(int stage)
{

    cout<< vData[stage][selectedQuestion]["question"] <<endl;
}

void cMillionaire::DisplayAnswer(int stage)
{
    int a,c;
    a=vData[stage][selectedQuestion][2].length();
    c=vData[stage][selectedQuestion][4].length();
    cout<<"a ="<<a;
    cout<<"  c ="<<c<<endl;
    for(int i=2;i<COL_COUNT-1;i++)
    {

        switch(i)
        {
        case 2:
            cout<<"A."<<vData[stage][selectedQuestion][i]<<"   ";
            while(a<c)
            {
                cout<<'*';
                a++;
            }
                break;
        case 3:
            cout<<"B."<<vData[stage][selectedQuestion][i]<<endl;
            break;

        case 4:
            cout<<"C."<<vData[stage][selectedQuestion][i]<<"   ";
            while(a>c)
            {
                cout<<'*';
                c++;
            }
            break;

        default:
            cout<<"D."<< vData[stage][selectedQuestion][i]<<endl;
            break;

        }
    }
}
