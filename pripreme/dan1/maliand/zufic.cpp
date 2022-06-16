#include <bits/stdc++.h>

#define FOR(a,b,c) for (int a=(b);a<(c);++a)
#define REP(i,n) FOR(i,0,n)
#define ll long long
#define pii pair<int,int>
#define x first
#define y second
#define pb push_back
#define lf double

using namespace std;

const int MAX = (int)1e6+5;

int n,k,l;
char outA[MAX];
char outB[MAX];

void gena(){
    REP(i,n) outA[i]=!!(i<k)+'0';
}

void genb(){
    REP(i,n) outB[i]='0';
    int pos=0,cnt=0;
    while(cnt<l){
        if (outB[pos]=='0'){
            outB[pos]='1';
            cnt++;
            pos=(pos+k)%n;
        }
        else pos=(pos+1)%n;
    }
}

int sol(){
    int cnt=0,ret=0;
    REP(i,n*2){
        cnt+=outB[i%n]-'0';
        if (i>=k) cnt-=outB[(i-k)%n]-'0';
        ret=max(ret,cnt);
    }
    return ret;
}

int main(){
    scanf ("%d%d%d",&n,&k,&l);
    gena();
    genb();
    
    printf ("%d\n%s\n%s\n",sol(),outA,outB);
    
    return 0;
}
