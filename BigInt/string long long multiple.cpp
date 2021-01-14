#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string strMul(string a, ll b)
{
    reverse(a.begin(),a.end());
    ll len=a.size();
    unsigned long long carr=0;
    for(ll i=0;i<len;i++){
        carr=b*(a[i]-'0')+carr;
        a[i]=(carr%10)+'0';
        carr=carr/10;
    }
    while(carr){
        char ch=(carr%10)+'0';
        a=a+ch;
        carr/=10;
    }
    reverse(a.begin(),a.end());
    return a;
}
