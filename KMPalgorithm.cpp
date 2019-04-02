#include <bits/stdc++.h>
using namespace std;

void computeLPS(int *lps, char pat[]){
    int len=0;
    lps[0]=0;
    for (int i=1;i<strlen(pat); ){
        if (pat[i]==pat[len]){
            len++;
            lps[i]=len;
            i++;
        }
        else if (len!=0){
            len=lps[len-1];
        }
        else{
            lps[i]=0;
            i++;
        }
    }
}

void KMPSearch(char pat[], char txt[])
{
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    computeLPS(lps,pat);

    int i = 0;
    int j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            cout<<"Pattern "<<pat<<" found at index "<< i - j <<endl;
            j = lps[j - 1];
        }
        /// mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            ///lps[0..lps[j-1]] characters will match by default
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

int main(){
    char a[]="garykasparovkremarprizkov";
    char b[]="ov";
    cout<<a<<endl;
    KMPSearch(b,a);
}
