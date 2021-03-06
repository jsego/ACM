/*
*  Javier Segovia
*  Accepted in 0.008
*/
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include<climits>
#include<algorithm>
#include<cassert>
#include<sstream>
using namespace std;
#define SL size()
#define LE length()
#define PB push_back
#define MP make_pair
#define BASE 1000000000
#define LI long long
#define SZ size()
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

struct big {
	vector<int> V;
	big(): V(1,0){}
	big(int n):V(1,n){}
	big(const big &b): V(b.V){}
	
	bool operator==(const big &b) const{ return V==b.V;}
	int &operator[](int i){return V[i];}
	int operator[](int i)const{return V[i];}
	int size() const{ return V.SZ;}
	void resize(int i) {V.resize(i);}
	
	bool operator<(const big &b) const{
		for (int i=b.SZ-1; SZ==b.SZ && i>=0; i--) {
			if(V[i] == b[i])continue;
			else return (V[i] < b[i]);
		}
		return SZ < b.SZ;
	}
	
	void add_digit(int l){
		if(l>0) V.PB(l);
	}
};

inline big suma(const big &a, const big &b,int k){
	LI l=0;
	int size = MAX(a.SZ,b.SZ+k);
	big c; c.resize(size);
	for (int i=0; i<size; ++i) {
		l += i<a.SZ ? a[i]:0;
		l += (k<=i && i<k+b.SZ)?b[i-k]:0;
		c[i] = l%BASE;
		l/=BASE;
	}
	c.add_digit(int(l));
	return c;
}

inline big operator+(const big &a,const big &b){
	return suma(a,b,0);
}

inline big operator+(const big &a,int b){return a+big(b);}
inline big operator+(int b,const big &a){return a+big(b);}

inline big operator-(const big &a,const big &b){
	assert(b<a || a==b);
	LI l=0,m=0;
	big c; c.resize(a.SZ);
	for (int i=0; i<a.SZ; ++i ) {
		l+=a[i];
		l-=i<b.SZ?b[i]+m:m;
		if(l<0){l+=BASE; m=1;}
		else m=0;
		c[i] = l%BASE;
		l/=BASE;
	}
	if(c[c.SZ-1]==0&&c.SZ>1) c.resize(c.SZ-1);
	return c;
}
inline big operator-(const big &a,int b){return a-big(b);}

inline big operator*(const big &a,int b){
	if(b==0) return big(0);
	big c; c.resize(a.SZ);
	LI l=0;
	for (int i=0; i<a.SZ; ++i ) {
		l +=(LI)b*a[i];
		c[i] = l%BASE;
		l/=BASE;
	}
	c.add_digit(int(l));
	return c;
}
inline big operator*(int b,const big &a){return a*b;}
inline big operator*(const big &a,const big &b){
	big res;
	for(int i=0;i<b.SZ;++i)
		res = suma(res,a*b[i],i);
	return res;
}

inline void divmod(const big &a,int b,big &div,int &mod){
	div.resize(a.SZ);
	LI l=0;
	for (int i=a.SZ-1; i>=0; --i) {
		l*=BASE;
		l+=a[i];
		div[i]=l/b;
		l%=b;
	}
	if(div[div.SZ-1]==0&&div.SZ>1)
		div.resize(div.SZ-1);
	mod = int(l);
}

inline big operator/(const big &a,int b){
	big div; int mod;
	divmod(a,b,div,mod);
	return div;
}

inline int operator%(const big &a,int b){
	big div; int mod;
	divmod(a,b,div,mod);
	return mod;
}

inline big operator^(const big &a,int k){
	big base(1),orig(a);
	while (k) {
		if (k&1) {
			base = base*orig;
		}
		orig = orig*orig;
		k>>=1;
	}
	return base;	
}

inline istream &operator>>(istream &is, big &b){
	string s;
	if (is >> s ) {
		b.resize((s.SZ-1)/9 +1);
		for (int n=s.SZ,k=0; n>0; n-=9,k++) {
			b[k]=0;
			for (int i=MAX(n-9,0); i<n ; i++) {
				b[k] = 10*b[k]+s[i]-'0';
			}
		}
	}
	return is;
}

inline ostream &operator<<(ostream &os,const big &b){
	os<<b[b.SZ-1];
	for (int k=b.SZ-2; k>=0; k--) {
		os<<setw(9)<<setfill('0')<<b[k];
	}
	return os;
}

int main(){
	int k; int a,pos;
	string b;
	while (cin>>b>>k) {
		a=0;
		for (int i=0; i<6; i++) {
			if(b[i]=='.')pos=5-i;
			else a=(a*10)+b[i]-'0';
		}
		//cout<<a<<" "<<b <<endl;
		pos = pos*k;
		big A(a);
		A=A^k;
		ostringstream os; os<<A;
		string s=os.str();
		pos = (int)s.LE-pos;
		if(pos<=0){
			//cout<<"POS:"<<(int)s.find_last_not_of('0')<<endl;
			cout<<"."; while(pos){cout<<"0";pos++;} 
			cout<<s.substr(0,(int)s.find_last_not_of('0')+1)<<endl;
		}
		else{
			cout<<s.substr(0,pos)<<(pos==(int)s.LE?"":".")<<s.substr(pos,(int)s.find_last_not_of('0')+1-pos)<<endl;
		}
	}
}