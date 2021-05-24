#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm> 
#include <cmath>
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


double dis2(int *a,double *b,int len){
    double res=0;
    for(int i=0;i<len;i++){
        res+=1.0*(a[i]-b[i])*(a[i]-b[i]);
    }
    return res;
}

/*void decode_4D8(int *out,double *in){
    int s=0,pos=0;
    double mn=4;
    for(int i=0;i<8;i++){
        out[i]=round(in[i]);
        s+=out[i];
        if(fabs(out[i]-in[i])<=mn){
            mn=fabs(out[i]-in[i]);
            pos=i;
        }
    }
    if(s%2==0){
        return;
    }else{ 
        //cout<<pos<<" "<<mn<<endl;
        if(out[pos]<in[pos])
            out[pos]+=1;
        else
            out[pos]-=1;
    }
}*/

/*long long round(double y,long long a){
    double mn=1e10;
    if(fabs(y)>100*a){throw;}
    int ans=0;
    for(int i=-100;i<=100;i++){
        int t=i*a;
        if(fabs(t-y)<mn){
            mn=fabs(t-y);
            ans=t;
        }
    } 
    return ans;
}
*/
long long round(double y,long long a){
    double mn=1e10;
    int ans=0;
    int approx=round(y/a);
    for(int i=approx-3;i<=approx+3;i++){
        int t=i*a;
        if(fabs(t-y)<mn){
            mn=fabs(t-y);
            ans=t;
        }
    } 
    return ans;
}

void decode_4D8(int *out,double *in){
    int s=0,pos=0;
    double mx=-1;
    for(int i=0;i<8;i++){
        out[i]=round(in[i],4);
        s+=out[i];
        if(fabs(out[i]-in[i])>mx){
            mx=fabs(out[i]-in[i]);
            pos=i;
        }
    }
    if(s%8==0){
        return;
    }else{ 
        if(out[pos]<in[pos])
            out[pos]+=4;
        else
            out[pos]-=4;
    }
}

void decode_4E8(int *out,double *in){
    int out1[8],out2[8];
    double in2[8];
    decode_4D8(out1,in);
    for(int i=0;i<8;i++)
        in2[i]=in[i]-2;
    decode_4D8(out2,in2);
    for(int i=0;i<8;i++)
        out2[i]+=2;
    if(dis2(out1,in,8)<dis2(out2,in,8)){
        memcpy(out,out1,sizeof(out1));
    }else{
        memcpy(out,out2,sizeof(out2));
    }
}  
 
void decode_Leech(int *out,double *in){

    

    int pre[16][16][24];

    for(int a=0;a<16;a++)
        for(int t=0;t<16;t++){
            double in3[24];
            int *out3=pre[a][t];
            for(int i=0;i<8;i++)
                in3[i]=in[i]-A[a][i]-T[t][i];
            for(int i=0;i<8;i++)
                in3[i+8]=in[i+8]-A[a][i]-T[t][i];
            for(int i=0;i<8;i++)
                in3[i+16]=in[i+16]-A[a][i]-T[t][i];
            decode_4E8(out3,in3);
            decode_4E8(out3+8,in3+8);
            decode_4E8(out3+16,in3+16);
            for(int i=0;i<8;i++)
                out3[i]=out3[i]+A[a][i]+T[t][i];
            for(int i=0;i<8;i++)
                out3[i+8]=out3[i+8]+A[a][i]+T[t][i];
            for(int i=0;i<8;i++)
                out3[i+16]=out3[i+16]+A[a][i]+T[t][i];
        }
    



    double mn=1e10;
    for(int a=0;a<16;a++)
    for(int b=0;b<16;b++){
        int c=table[a][b];
        for(int t=0;t<16;t++){
            
            int out3[24];
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
    return 0;
}