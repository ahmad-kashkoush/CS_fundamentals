#include<bits\stdc++.h>
#define ll long long

#define el "\n"
using namespace std;
//Homework
//problem 1
int Max(int a, int b){
    if(a>=b)
        return a;
    return b;
}
int Max(int a, int b, int c){
    return Max(Max(a, b), c);
}
int Max(int a, int b, int c, int d){
    return Max(Max(a, b, c),d);
}
int Max(int a, int b, int c, int d, int e){
    return Max(Max(a, b, c), d, e);
}
int Max(int a, int b, int c, int d, int e, int f){
    return Max(Max(a, b, c, d, e), f);
}
// Problem 2
string reverse(const string &s){
        string reversed;
        for(int i=(int)s.size()-1;i>=0;i--)
            reversed+=s[i];
        return reversed;
}
// Problem 3 calculator
int operations;
void read_num(double &a, double &b){
    cin>>a>>b;
}
double add(double a=0, double b=0){
    return a+b;
}
double sub(double a=0, double b=0){
    return a-b;
}
double mul(double a=0, double b=0){
    return a*b;
}
double div(double a=0, double b=1){
    if(b==0)
       return -1;
    return a/b;
}
void menu(){
    cout<<"1) read 2 numbers"<<el;
    cout<<"2) add"<<el;
    cout<<"3) sub"<<el;
    cout<<"4) mul"<<el;
    cout<<"5) div"<<el;
    cout<<"Enter your option: ";

}
void Start(){
    double x, y;
    cout<<"choose 6 to display menu\n";
    while(true){
        int my_option;cin>>my_option;
        if(my_option==1) read_num(x, y);
        else if(my_option==2) cout<<add(x, y);
        else if(my_option==3) cout<<sub(x, y);
        else if(my_option==4) cout<<mul(x, y);
        else if(my_option==5) cout<<div(x, y);
        else if(my_option==6) menu();
        else return;
        cout<<endl;
    }


}
// problem 3
void set_powers(int arr[], int len=5, int m=2){
    int x=1;
    for(int i=0;i<5;i++){
        arr[i]=x;
        x*=m;
    }
    for(int i=0;i<len;i++)cout<<arr[i]<<' ';
}
bool is_pattern(string input, string pattern, int pos){
    if(pos+(int)pattern.size()>(int)input.size())
        return false;

    for(int i=pos, x=0;x<pattern.size();i++,x++){
            if(input[i]!=pattern[x])
                return false;
    }
    return true;

}
string replace_str(string input, string pattern, string to){
    string ans;
    for(int i=0;i<input.size();i++){
        if(is_pattern(input, pattern, i)){
            i+=(int)pattern.size();
            ans+=to;
        }
        ans+=input[i];
    }
    return ans;
}

 int main(){
    cout<<replace_str("aabcabaaad", "aa","x")<<el;
    cout<<replace_str("aabcabaaad", "aa", "aaaa")<<el;
    cout<<replace_str("aabcabaaad", "aa", "")<<el;
    return 0;
}
