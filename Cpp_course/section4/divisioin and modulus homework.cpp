#include<iostream>
using namespace std;
int main(){
//    int x,s1,e1,s2,e2,s3,e3;
//    cin>>x>>s1>>e1>>s2>>e2>>s3>>e3;
//    int ans=0;
//    ans+=(x>=s1&&x<=e1);
//    ans+=(x>=s2&&x<=e2);
//    ans+=(x>=s3&&x<=e3);
//    cout<<ans;
    int a, b, c, d,s,e;
    cin>>a>> b>> c>> d;
    if(c>b)
        cout<<-1;
    else{
    if(a>c)s=a;
    else   s=c;
    if(b<d)e=b;
    else   e=d;
    }
    cout<<s<<' '<<e;
}
