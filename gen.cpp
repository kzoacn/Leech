#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    long long scale=1;
    int out1[24],out2[24];
    int in[24];
    int T=10;
    double st=clock();
    int s=0;
    while(T--){
        for(int i=0;i<24;i++)
            in[i]=rand()%1000-500;
        for(int i=0;i<24;i++)
            cout<<in[i]<<" ";
        cout<<endl;
    }
    return 0;
}
