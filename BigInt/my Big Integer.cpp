#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(v) v.begin(),v.end()

//The digits are always in reverse order
class BigInt {
  public:
    string dgt;
    bool sign;
    BigInt();
    void trim();
    bool isZero();
    void read(const string&);
    BigInt(string); //first dgt is the sign/no sign /////BigInt b("98");
    BigInt(ll);
    BigInt(int);
    void operator = (const string); //first dgt is the sign/no sign
    void operator = (const ll);
    void operator = (const int);
    friend istream& operator>>(istream&,BigInt&);
    friend ostream& operator<<(ostream&, const BigInt&);
    BigInt friend operator + (BigInt,BigInt);
    BigInt friend operator - (BigInt,BigInt);
    BigInt friend operator * (BigInt,BigInt);
    BigInt friend operator / (BigInt,ll);
};

///Must have functions --Start--

BigInt::BigInt() {
    sign=true;
    dgt="";
}

void BigInt::trim() {

    while(!dgt.empty()&&dgt.back()=='0')dgt.pop_back();
    if(dgt.empty())sign=true;
}

bool BigInt::isZero() {
    return dgt.empty()||(dgt.size()==1&&dgt[0]=='0');
}

void BigInt::read(const string &s) {
    sign=true;
    dgt="";
    ll idx=0,len=s.size();
    if(s[0]=='+'||s[0]=='-') {
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

BigInt::BigInt(string s) {
    read(s);
}

void BigInt::operator = (const string s) {
    read(s);
}

///String input end --End--

///Long Long input --Start--

BigInt::BigInt(ll num) {
    string s=to_string(num);
    read(s);
}

void BigInt::operator = (const ll num) {
    string s=to_string(num);
    read(s);
}

///Long Long input --End--

///Int Input --Start--

BigInt::BigInt(int num) {
    string s=to_string(num);
    read(s);
}

void BigInt::operator = (const int num) {
    string s=to_string(num);
    read(s);
}

///Int Input --End--

///Input-Output Stream --Start--

istream& operator>>(istream &stream,BigInt &v) {
    string s;
    stream>>s;
    v.read(s);
    return stream;
}

ostream& operator<<(ostream &stream,BigInt &v) {
    if(v.isZero()) {
        stream<<'0';
        return stream;
    }
    if(v.sign==false)stream<<'-';
    for(ll i=v.dgt.size()-1; i>=0; i--)stream<<v.dgt[i];
    return stream;
}


///Input-Output Stream --End--

///BigInt Addition and Sunbtruction --Start--

ll dgt_comp(string a, string b) {
    if(a.size()!=b.size())return (a.size()>b.size())?1:-1;
    for(ll i=a.size()-1; i>=0; i--) {
        if(a[i]!=b[i])return (a[i]>b[i])?1:-1;
    }
    return 0;
}

string dgt_add(string a,string b) {
    string ans="";
    ll alen=a.size(),blen=b.size();
    ll sz=min(alen,blen),carry=0,idx=0;
    char tmp;
    for(ll i=0; i<sz; i++) {
        ll curr=(a[i]-'0')+(b[i]-'0');
        tmp=((curr+carry)%10)+'0';
        ans=ans+tmp;
        carry=(curr+carry)/10;
    }
    if(alen<blen) {
        a=b;
        alen=blen;
    }
    for(ll i=sz; i<alen; i++) {
        tmp=((a[i]-'0')+carry)%10;
        tmp=tmp+'0';
        ans=ans+tmp;
        carry=((a[i]-'0')+carry)/10;
    }
    if(carry>0) {
        tmp=carry+'0';
        ans=ans+tmp;
    }
    return ans;
}

string dgt_sub(string a, string b) {
    string ans="";
    ll alen=a.size(),blen=b.size();
    ll sz=min(alen,blen),carry=0,idx=0;
    char tmp;
    for(ll i=0; i<sz; i++) {
        ll x=a[i]-'0',y=b[i]-'0'+carry;
        carry=0;
        if(x<y) {
            x+=10;
            carry=1;
        }
        tmp=(x-y)+'0';
        ans=ans+tmp;
    }
    if(alen<blen) {
        a=b;
        alen=blen;
    }
    for(ll i=sz; i<alen; i++) {
        ll x=a[i]-'0', y=carry;
        carry=0;
        if(x<y) {
            x+=10;
            carry=1;
        }
        tmp=(x-y)+'0';
        ans=ans+tmp;
    }
    return ans;
}

BigInt operator + (BigInt a,BigInt b) {
    BigInt add;
    if(a.isZero())return b;
    else if(b.isZero())return a;
    if(a.sign==b.sign) {
        add.sign=a.sign;
        add.dgt=dgt_add(a.dgt,b.dgt);
        add.trim();
        return add;
    } else {
        int cmp=dgt_comp(a.dgt,b.dgt);
        if(cmp==0) {
            add.sign=true;
            add.dgt="";
            return add;
        } else {

            if(cmp==(-1)) {
                swap(a,b);
            }
            add.sign=a.sign;
            add.dgt=dgt_sub(a.dgt,b.dgt);
            add.trim();
            return add;
        }
    }

}

BigInt operator - (BigInt a,BigInt b) {
    b.sign=!b.sign;
    BigInt sub=a+b;
    return sub;
}

///BigInt Addition and Sunbtruction --End--

///BigInt Multiplication --Start--

string dgt_mul(string a, string b) {
    ll alen=a.size(), blen=b.size(), sz;
    string ans="";
    char tmp;
    for(ll i=0; i<blen; i++) {
        ll x=b[i]-'0', idx=i, carry=0;
        for(ll j=0; j<alen; j++) {
            ll y=a[j]-'0';
            ll curr=0;
            if(ans.size()>idx) {
                curr=ans[idx]+(x*y)+carry;
                tmp=(curr%10)+'0';
                ans[idx]=tmp;
            } else {
                curr=(x*y)+carry;
                tmp=(curr%10)+'0';
                ans=ans+tmp;
            }
            carry=curr/10;
            idx++;
        }
        if(carry>0) {
            tmp=carry+'0';
            ans=ans+tmp;
        }
        sz=idx;
    }
    return ans;
}

BigInt operator * (BigInt a,BigInt b) {
    BigInt mul;
    if(a.sign==b.sign)mul.sign=a.sign;
    else mul.sign=false;
    mul.dgt=dgt_mul(a.dgt,b.dgt);
    mul.trim();
    return mul;
}

///BigInt Multiplication --End--

///BigInt Divition --Start--

string dgt_div(string a, ll b) {
    reverse(a.begin(),a.end());
    ll alen=a.size(),tmp=0,idx=0;
    while(tmp<b && idx<alen){
		tmp=(tmp*10)+a[idx++]-'0';
	}
    string ans="";
	while(tmp>=b){
		ans+=(tmp/b)+'0';
		tmp%=b;
		if(idx>=alen){break;}
		tmp=(tmp*10)+a[idx++]-'0';
	}
	reverse(ans.begin(),ans.end());
	return ans;
}

BigInt operator / (BigInt a,ll b) {
    BigInt div;
    if(b==0) {
        cout<<"Invalid Division: Can't divide by zero\n";
        div.sign=true;
        div.dgt="";
        return div;
    }
    if(a.isZero()) {
        div=0;
        return div;
    }
    if((a.sign==true&&b>=0)||(a.sign==false&&b<0))div.sign=true;
    else div.sign=false;
    b=abs(b);
    div.dgt=dgt_div(a.dgt,b);
    div.trim();
    return div;
}

///Problem End.......................

///Bigint Divition --End--



int main() {
    BigInt a;
    ll b;
    cin>>a;
    cin>>b;
    BigInt div;
    div=a/b;
    cout<<div<<endl;
    return 0;
}

