#include <bits/stdc++.h>
using namespace std;


int min_coin(int n,int s,int c[]){
    int a[s+1];
    memset(a,127,sizeof(a)); ///sets each byte to maximum value;

    a[0]=0;

    for (int i=1;i<=s;i++){
        for (int j=0;j<n;j++){
            if (c[j]<=i && a[i-c[j]]+1<a[i]){
                a[i]=a[i-c[j]]+1;
            }
        }
    }

    return a[s];
}
int main(){
    int n,s,i;
    cin>>n>>s;
    int c[n];
    for (i=0;i<n;i++)
        cin>>c[i];

    cout<<min_coin(n,s,c);
}
