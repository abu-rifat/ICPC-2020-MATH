#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(v) v.begin(),v.end()

//The digits are always in reverse order
class BigInt{
    public:
    string dgt;
    bool sign;
    BigInt();
    void trim();
    bool isZero();
    void read(const string&);
    BigInt(string); //first dgt is the sign/no sign
    BigInt(ll);
    BigInt(int);
    void operator = (const string); //first dgt is the sign/no sign
    void operator = (const ll);
    void operator = (const int);
    friend istream& operator>>(istream&,BigInt&);
    friend ostream& operator<<(ostream&, const BigInt&);
    //BigInt friend operator + (BigInt,BigInt);
    //BigInt friend operator - (BigInt,BigInt);
    //BigInt friend operator * (BigInt,BigInt);
    //BigInt friend operator / (BigInt,BigInt);



};

///Must have functions --Start--

BigInt::BigInt(){
    sign=true;
    dgt="";
}

void BigInt::trim(){
    while(!dgt.empty()&&dgt.back()=='0')dgt.pop_back();
    if(dgt.empty())sign=true;
}

bool BigInt::isZero()
{
    return dgt.empty()||(dgt.size()==1&&dgt[0]=='0');
}

void BigInt::read(const string &s)
{
    sign=true;
    dgt="";
    ll idx=0,len=s.size();
    if(s[0]=='+'||s[0]=='-'){
        if(s[0]=='-')sign=false;
        idx++;
        len--;
    }
    dgt=s.substr(idx,len);
    reverse(all(dgt));
    trim();
}

///Must have functions --End--

///String Input --Start--

BigInt::BigInt(string s){
    read(s);
}

void BigInt::operator = (const string s){
    read(s);
}

///String input end --End--

///Long Long input --Start--

BigInt::BigInt(ll num){
    string s=to_string(num);
    read(s);
}

void BigInt::operator = (const ll num){
    string s=to_string(num);
    read(s);
}

///Long Long input --End--

///Int Input --Start--

BigInt::BigInt(int num){
    string s=to_string(num);
    read(s);
}

void BigInt::operator = (const int num){
    string s=to_string(num);
    read(s);
}

///Int Input --End--

///Input-Output Stream --Start--

istream& operator>>(istream &stream,BigInt &v){
    string s;
    stream>>s;
    v.read(s);
    return stream;
}

ostream& operator<<(ostream &stream,BigInt &v){
    if(v.isZero()){
        stream<<'0';
        return stream;
    }
    if(v.sign==false)stream<<'-';
    for(ll i=v.dgt.size()-1;i>=0;i--)stream<<v.dgt[i];
    return stream;
}


///Input-Output Stream --End--



int main()
{
    BigInt a;
    cin>>a;
    cout<<a<<endl;
    cout<<a<<endl;
    return 0;
}
