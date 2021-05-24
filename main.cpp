#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "leech.hpp"
using namespace std;



int main(){
 
    long long scale=1;
    int out1[24],out2[24];
    int in[24];
    int T=10;
    while(T--){
        for(int i=0;i<24;i++)
            cin>>in[i];
 
        decode_Leech(out1,in,scale);
        //decode_Leech2(out2,in,scale);
        for(int i=0;i<24;i++)
            cout<<out1[i]<<" ";
        cout<<endl;
    }
    return 0;
}
