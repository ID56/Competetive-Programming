#include <bits/stdc++.h>
using namespace std;

int LISlen(int a[],int n){
    int state[n]={};

    state[0]=1;
    for (int i=1;i<n;i++){
        int f=0;
        for (int j=0;j<i;j++){
            if (a[j]<a[i] && state[j]+1>state[i]){
                state[i]=state[j]+1;
                f=1;
            }
        }
        if (f==0)
            state[i]=1;
        ///cout<<state[i]<<endl;
    }
    return state[n-1];
}

int main(){
    int n;
    cin>>n;
    int a[n];
    for (int i=0;i<n;i++)
        cin>>a[i];

    cout<<LISlen(a,n);
}
