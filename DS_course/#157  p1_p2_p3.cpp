#include<iostream>
#include <vector>
#include<cassert>
#define ll long long
using namespace std;
const int mod=65407;
int getNum(char c){
    if(c>='0'&&c<='9')return c-'0'+2*26;
    if(c>='a'&&c<='z') return c-'a';
    if(c>='A'&&c<='Z') return c-'Z'+26;
}
int hash_num(int value, int n=65407){
    ll nn=n;
    return (ll)(value%nn+nn)%nn;
}
int hash_string(string str, int n=mod) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum * 62 + getNum(str[i])) % nn;
	return sum % nn;
}
int  foldingHashString(string str, int n=65407){
    int len=str.size();
    long long nn=n;
    long long sum=0;
    for(int i=0;i<len;i+=4){
        string tmp="";
        if(i+4>=n)tmp=str.substr(i);
        else      tmp=str.substr(i, 4);
        sum+=hash_string(tmp, n);
        sum%=nn;
    }
    return sum;
}

struct someObject{
    int number;
    string str1, str2;
    int Hash(){
        ll res=hash_string(str1+str2);
        res+=hash_num(number);
        return res%mod;
    }
};




void p2(){
    string str="aabcdefgAxT334gfg";
    cout<<foldingHashString(str);
}
int main() {
    p2();



	return 0;
}

