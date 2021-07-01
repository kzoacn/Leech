#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm> 
#include <cmath>
#include "leech_float.hpp"
using namespace std;

 
const int n=24;
void rand_vec(double *p){
    double len=0;
    for(int i=0;i<n;i++){
        int x=rand()%1000-500;
        p[i]=x;
        len+=1.0*x*x;
    }
    len=sqrt(len);
    for(int i=0;i<n;i++)
        p[i]/=len;
}


void rand_bound(double *b){
    double v[n];
    rand_vec(v);

    double l=0,r=100;
    int T=20;
    while(T--){
        double mid=(l+r)/2;
        double tmp[n];
        int out[n];
        for(int i=0;i<n;i++)
            tmp[i]=v[i]*mid;
        
        decode_Leech(out,tmp);
        int zero=1;
        for(int i=0;i<n;i++)if(out[i])
            zero=0;

        if(zero){
            l=mid; 
        }else{
            r=mid; 
        }
    }
    
    cout<<"bound dis to zero "<<l<<endl;
    if(l>4*sqrt(2))
        exit(0);
    
    l-=0.1;

    for(int i=0;i<n;i++)
        b[i]=v[i]*l;
}

int main(){

srand(time(0));
int T=1000;
while(T--){
    cerr<<T<<endl;
    double u[n],v[n];
    int out[n]; 
    rand_bound(u);
    rand_bound(v);


    int L=10;
    for(int i=0;i<=L;i++){

        double p[n];
        for(int j=0;j<n;j++)
            p[j]=u[j]*1.0*i/L+v[j]*(1-1.0*i/L);

        
        decode_Leech(out,p);
        
        int zero=1;
        for(int j=0;j<n;j++)if(out[j])
            zero=0;


        if(zero){
            puts("yes");
        }else{
            puts("no");
            exit(0);
        }
    }
}

// symmtric
while(T--){
    cerr<<T<<endl;
    double u[n],v[n];
    int out[n]; 
    rand_bound(u);
    rand_bound(v);


    int L=10;
    for(int i=0;i<=1;i++){

        double p[n];
        for(int j=0;j<n;j++)
            p[j]=-u[j];

        
        decode_Leech(out,p);
        
        int zero=1;
        for(int j=0;j<n;j++)if(out[j])
            zero=0;


        if(zero){
            puts("yes");
        }else{
            puts("no");
            exit(0);
        }
    }
}
    return 0;
}