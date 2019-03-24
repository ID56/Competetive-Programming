#include <bits/stdc++.h>

using namespace std;

typedef vector<int> BigInt;

void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());   ///printing 1st digit or zero
    for(int i=a.size()-2;i>=0;i--)
        printf("%09d", a[i]);
}

BigInt BigInteger(string s) {
    BigInt ans;
    if (s[0] == '-') return ans; ///won't work for negative numbers

    if (s.size() == 0){
        ans.push_back(0);
        return ans;
    }
    while (s.size()%9 != 0){     ///size of string is now a multiple of nine, that is, they
        s = '0'+s;               ///are separate discrete numbers having nine digits each.
    }
    for (int i=0;i<s.size();i+=9){
        int v = 0;
        for (int j=i;j<i+9;j++)
            v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}


#define base (int)1e9
BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    for(int i=0;i<max(a.size(), b.size());i++){
        if (i < a.size())
            carry += a[i];
        if (i < b.size())
            carry += b[i];
        ans.push_back(carry%base);
        carry=carry/base;
    }
    if (carry)
        ans.push_back(carry);
    Set(ans);
    return ans;
}

int main(){
    string a,b;
    cin>>a>>b;
    BigInt p=BigInteger(a);
    BigInt q=BigInteger(b);

    Print(p+q);
}

