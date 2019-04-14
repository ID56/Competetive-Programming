#include <bits/stdc++.h>
using namespace std;

/***
** Source: https://community.topcoder.com/stat?c=problem_statement&pm=1259&rd=4493
** --Problem Statement--
** A sequence of numbers is called a zig-zag sequence if the differences between successive numbers
** strictly alternate between positive and negative. The first difference (if one exists) may be either
** positive or negative. A sequence with fewer than two elements is trivially a zig-zag sequence.
**
** For example, 1,7,4,9,2,5 is a zig-zag sequence because the differences (6,-3,5,-7,3) are alternately
** positive and negative. In contrast, 1,4,7,2,5 and 1,7,4,5,5 are not zig-zag sequences, the first
** because its first two differences are positive and the second because its last difference is zero.
**
** Given a sequence of integers, sequence, return the length of the longest subsequence of sequence that
** is a zig-zag sequence. A subsequence is obtained by deleting some number of elements (possibly zero)
** from the original sequence, leaving the remaining elements in their original order.
***/
int zigzag(int a[],int n){
    int pos[n]={};
    int neg[n]={};
    pos[0]=1;
    neg[0]=1;
    for (int i=1;i<n;i++){
        int f=0;
        for (int j=0;j<i;j++){
            if (a[j]<a[i] && neg[j]+1>pos[i]){
                pos[i]=neg[j]+1;
                f=1;
            }
        }
        if (f==0){
            pos[i]=1;
        }

        f=0;
        for (int j=0;j<i;j++){
            if (a[j]>a[i] && pos[j]+1>neg[i]){
                neg[i]=pos[j]+1;
                f=1;
            }
        }
        if (f==0){
            neg[i]=1;
        }
    }
    return max(pos[n-1],neg[n-1]);
}

int main(){
    int n;
    cin>>n;
    int a[n];
    for (int i=0;i<n;i++)
        cin>>a[i];

    cout<<zigzag(a,n);
}

