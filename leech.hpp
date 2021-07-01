#ifndef LEECH__HPP_
#define LEECH_HPP_

#include <cstring>
#include <cmath>
#include <algorithm>

const int A[16][8]={
    {0,0,0,0,0,0,0,0},
    {4,0,0,0,0,0,0,0},
    {2,2,2,2,0,0,0,0},
    {-2,2,2,2,0,0,0,0},
    {2,2,0,0,2,2,0,0},
    {-2,2,0,0,2,2,0,0},
    {2,2,0,0,0,0,2,2},
    {-2,2,0,0,0,0,2,2},
    {2,0,2,0,2,0,2,0},
    {-2,0,2,0,2,0,2,0},
    {2,0,2,0,0,2,0,2},
    {-2,0,2,0,0,2,0,2},
    {2,0,0,2,2,0,0,2},
    {-2,0,0,2,2,0,0,2},
    {2,0,0,2,0,2,2,0},
    {-2,0,0,2,0,2,2,0}
};

const int T[16][8]={
    {0,0,0,0,0,0,0,0},
    {2,2,2,0,0,2,0,0},
    {2,2,0,2,0,0,0,2},
    {2,0,2,2,0,0,2,0},
    {0,2,2,2,2,0,0,0},
    {2,2,0,0,2,0,2,0},
    {2,0,2,0,2,0,0,2},
    {2,0,0,2,2,2,0,0},
    {-3,1,1,1,1,1,1,1},
    {3,-1,-1,1,1,-1,1,1},
    {3,-1,1,-1,1,1,1,-1},
    {3,1,-1,-1,1,1,-1,1},
    {3,1,1,1,1,-1,-1,-1},
    {3,-1,1,1,-1,1,-1,1},
    {3,1,-1,1,-1,1,1,-1},
    {3,1,1,-1,-1,-1,1,1},
};
const int table[16][16]={
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14},
    {2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13},
    {3,2,1,0,7,6,5,4,11,10,9,8,15,14,13,12},
    {4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11},
    {5,4,7,6,1,0,3,2,13,12,15,14,9,8,11,10},
    {6,7,4,5,2,3,0,1,14,15,12,13,10,11,8,9},
    {7,6,5,4,3,2,1,0,15,14,13,12,11,10,9,8},
    {8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7},
    {9,8,11,10,13,12,15,14,1,0,3,2,5,4,7,6},
    {10,11,8,9,14,15,12,13,2,3,0,1,6,7,4,5},
    {11,10,9,8,15,14,13,12,3,2,1,0,7,6,5,4},
    {12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3},
    {13,12,15,14,9,8,11,10,5,4,7,6,1,0,3,2},
    {14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1},
    {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0}
};


long long dis2(int *a,int *b,int len){
    long long res=0;
    for(int i=0;i<len;i++){
        res+=1LL*(a[i]-b[i])*(a[i]-b[i]);
    }
    return res;
}

long long round(long long y,long long a){
    long long x=y;
    long long m=(x%a+a)%a;
    if(m<=a/2)
        return x-m;
    else
        return x-m+a;    
}

void decode_4D8(int *out,int *in,long long scale){
    long long s=0;
    int pos=0,mx=-1;
    for(int i=0;i<8;i++){
        out[i]=round(in[i],scale*4);
        s+=out[i];
        if(abs(out[i]-in[i])>mx){
            mx=abs(out[i]-in[i]);
            pos=i;
        }
    }
    if(s%(8*scale)==0){
        return;
    }else{
        if(out[pos]<in[pos])
            out[pos]+=scale*4;
        else
            out[pos]-=scale*4;
    }
}
void decode_4E8(int *out,int *in,long long scale){
    int out1[8],out2[8],in2[8];
    decode_4D8(out1,in,scale);
    for(int i=0;i<8;i++)
        in2[i]=in[i]-2*scale;
    decode_4D8(out2,in2,scale);
    for(int i=0;i<8;i++)
        out2[i]+=2*scale;
    if(dis2(out1,in,8)<dis2(out2,in,8)){
        memcpy(out,out1,sizeof(out1));
    }else{
        memcpy(out,out2,sizeof(out2));
    }
}  
 
void decode_Leech(int *out,int *in,long long scale){


    int pre[16][16][24];

    for(int a=0;a<16;a++)
        for(int t=0;t<16;t++){
            int in3[24],*out3=pre[a][t];
            for(int i=0;i<8;i++)
                in3[i]=in[i]-A[a][i]*scale-T[t][i]*scale;
            for(int i=0;i<8;i++)
                in3[i+8]=in[i+8]-A[a][i]*scale-T[t][i]*scale;
            for(int i=0;i<8;i++)
                in3[i+16]=in[i+16]-A[a][i]*scale-T[t][i]*scale;
            decode_4E8(out3,in3,scale);
            decode_4E8(out3+8,in3+8,scale);
            decode_4E8(out3+16,in3+16,scale);
            for(int i=0;i<8;i++)
                out3[i]=out3[i]+A[a][i]*scale+T[t][i]*scale;
            for(int i=0;i<8;i++)
                out3[i+8]=out3[i+8]+A[a][i]*scale+T[t][i]*scale;
            for(int i=0;i<8;i++)
                out3[i+16]=out3[i+16]+A[a][i]*scale+T[t][i]*scale;
        }
    



    long long mn=1LL<<60;
    for(int a=0;a<16;a++)
    for(int b=0;b<16;b++){
        int c=table[a][b];
        for(int t=0;t<16;t++){
            
            int in3[24],out3[24];
            memcpy(out3,pre[a][t],sizeof(int)*8);
            memcpy(out3+8,pre[b][t]+8,sizeof(int)*8);
            memcpy(out3+16,pre[c][t]+16,sizeof(int)*8);

            if(dis2(out3,in,24)<mn){ 
                mn=dis2(out3,in,24);
                memcpy(out,out3,sizeof(out3));
            }
        }
    }


}



void decode(double *out,double *in,long long scale){
    const int n=512;
    const int num=22;
    int in_[num*24],out_[num*24];
    memset(in_,0,sizeof(in_));

    for(int i=0;i<n;i++){
        in_[i]=in[i];
    }
    for(int i=0;i<num;i++){
        decode_Leech(out_+i*24,in_+i*24,scale);
    }
    for(int i=0;i<n;i++){
        out[i]=out_[i];
    }
}

#endif