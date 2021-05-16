#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

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
    {3,-1,-1,-1,1,-1,1,1},
    {3,-1,1,-1,1,1,1,-1},
    {3,1,-1,-1,1,1,-1,1},
    {3,1,1,1,1,-1,-1,-1},
    {3,-1,1,1,-1,1,-1,1},
    {3,1,-1,1,-1,1,1,-1},
    {3,1,1,-1,-1,-1,1,1},
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
    if(m<a/2)
        return x-m;
    else
        return x-m+a;    
}

void decode_4D8(int *out,int *in,long long scale){
    int s=0,pos=0,mn=scale*4;
    for(int i=0;i<8;i++){
        out[i]=round(in[i],scale*4);
        s+=out[i];
        if(abs(out[i]-in[i])<=mn){
            mn=abs(out[i]-in[i]);
            pos=i;
        }
    }
    if(s%8==0){
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
bool same(const int *in1,const int *in2){
    for(int i=0;i<8;i++)
        if(in1[i]!=in2[i])
            return false;
    return true;
}
void decode_Leech(int *out,int *in,long long scale){

    long long mn=1LL<<60;

    for(int a=0;a<16;a++)
    for(int b=0;b<16;b++)
    for(int c=0;c<16;c++){
        int tmp[8],oute8[8];
        for(int i=0;i<8;i++)
            tmp[i]=A[a][i]+A[b][i]+A[c][i];
        decode_4E8(oute8,tmp,scale);
        if(!same(oute8,tmp))
            continue;
        for(int t=0;t<16;t++){
            
            int in3[24],out3[24];
            for(int i=0;i<8;i++)
                in3[i]=in[i]-A[a][i]-T[t][i];
            for(int i=0;i<8;i++)
                in3[i+8]=in[i+8]-A[b][i]-T[t][i];
            for(int i=0;i<8;i++)
                in3[i+16]=in[i+16]-A[c][i]-T[t][i];
            decode_4E8(out3,in3,scale);
            decode_4E8(out3+8,in3+8,scale);
            decode_4E8(out3+16,in3+16,scale);
            if(dis2(out3,in,24)<mn){
                mn=dis2(out3,in,24);
                memcpy(out,out3,sizeof(out3));
            }
        }
    }
}

int main(){
    long long scale=1;
    int out[24];
    int in[24]={4,0,4};
    decode_Leech(out,in,scale);
    for(int i=0;i<24;i++)
        cout<<out[i]<<" ";
    cout<<endl;
    return 0;
}