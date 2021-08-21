// Author: Francisco Affonso
/*
Primeira contato com códigos de sistemas evolutivos,
contento funções básicas para efetuar a evolução
*/

#include <iostream>
#include <math.h>
using namespace std;

#define TamPop 20
#define maxx 1000
float TaxMut = 2;

double ind[TamPop + 1];
double indtemp[TamPop + 1];
double fit[TamPop + 1];
double maxfit = 0.0;
double media = 0.0;
int gen, maxi = 0;


void initpop () {
    for (int i=1; i<=TamPop; i++) {
        ind[i] = (double) (rand() % maxx);
    }
}

void avalia () {
    float x;
    cout << "Generation: " << gen << endl;
    
    for (int i=1; i<=TamPop; i++) {
        x = ind[i];
        float y = x;
        
        if (x>500) 
            y = 1000 - x;
        
        fit[i] = y;
        cout << "\tFitness " << i << " (" << ind[i] << ") = " << fit[i] << endl; 
    }
}

void elitismo () {
    maxfit = fit[1];
    maxi = 1;

    for (int i=2;i<=TamPop;i++) {
        if (fit[i]>maxfit) {
            maxfit = fit[i];
            maxi = i;
        }
    }

    for (int i=1;i<=TamPop;i++) {
        if (i==maxi)
            continue;

        ind[i] = (ind[i] + ind[maxi])/ 2.0;

        ind[i] = ind[i] + ((double) (rand()%maxx)-maxx/2)*TaxMut/100.0f;
		if(ind[i]>maxx)
			ind[i]=maxx;
		if(ind[i]<0)
			ind[i]=ind[i]*-1.0;
    }
}

void torneio () {
    int a, b, pai1, pai2;
    maxfit = fit[1];
    maxi   = 1;
    for (int i=2;i<=TamPop;i++) {
        if (fit[i]>maxfit) {
            maxfit = fit[i];
            maxi = i;
        }
    }

    for (int i=1;i<=TamPop;i++)
        indtemp[i] = ind[i];
    for (int i=1;i<=TamPop;i++) {
        if (i==maxi)
            continue;

        a = (rand() %TamPop) + 1;
        b = (rand() %TamPop) + 1;
        if (fit[a] > fit[b])
            pai1 = a;
        else
            pai1 = b;

        a = (rand() %TamPop) + 1;
        b = (rand() %TamPop) + 1;
        
        if (fit[a] > fit[b])
            pai2 = a;
        else
            pai2 = b;

        ind[i] = (indtemp[pai1] + indtemp[pai2])/ 2.0;

        ind[i] = ind[i] + (double) (((rand() %maxx - (maxx/2.0))/100.0) * TaxMut);
    }
}

void ag () {
    elitismo();
    avalia ();

    gen++;
}


int main () {
    initpop ();

    for (int i=0; i<100000; i++)
        ag ();
}
