#include <bits/stdc++.h>
using namespace std;

void LISprint(int a[],int n){
    int state[n]={};
    int prev[n]={};
    state[0]=1;
    prev[0]=0;
    for (int i=1;i<n;i++){
        int f=0;
        for (int j=0;j<i;j++){
            if (a[j]<a[i] && state[j]+1>state[i]){
                state[i]=state[j]+1;
                prev[i]=j;
                f=1;
            }
        }
        if (f==0){
            state[i]=1;
            prev[i]=i;
        }
    }

    int lis[state[n-1]];

    int i=state[n-1]-1;
    int j=n-1;

    while(1){
        lis[i]=a[j];
        if (prev[j]==j) ///LIS started here
            break;
        j=prev[j];
        i--;
    }
    for (i=0;i<state[n-1];i++)
        cout<<lis[i]<<" ";
}

int main(){
    int n;
    cin>>n;
    int a[n];
    for (int i=0;i<n;i++)
        cin>>a[i];

    LISprint(a,n);
}
