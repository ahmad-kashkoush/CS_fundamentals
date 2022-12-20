//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
/**symbols
    @!  --> important and and write it down
*/
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
int countDitinctSubstrings(string a){
    unordered_set<string> s;
    for(int start=0;start<a.size();start++){

        for(int end=start;end<a.size();end++)
            s.insert(a.substr(start, end-start+1));

    }
    return s.size();
}
void countDistinctSubstrings(string a,  unordered_set<string> &s, bool is_second=false){
    unordered_set<string> s2;
    for(int start=0;start<a.size();start++){
        for(int end=start;end<a.size();end++){
           string tmp= a.substr(start, end-start+1);
           if(s.count(tmp)&&is_second&&!s2.count(tmp))
                cout<<tmp<<", ";
            s.insert(tmp);
            s2.insert(tmp);
        }

    }
    cout<<el;

}

void commonSubstrings(const string &str1, const string &str2){
    unordered_set<string> s;
    countDistinctSubstrings(str1, s);
    countDistinctSubstrings(str2, s, true);
}
void p1(){
    cout<<countDitinctSubstrings("aaaaa")<<el;
    cout<<countDitinctSubstrings("aaaba")<<el;
    cout<<countDitinctSubstrings("abcdef")<<el;
}
void p2(){
    commonSubstrings("aaaab","aa");
    commonSubstrings("aaaab","ab");
}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;
  //  cin>>t;
    while(t--)
        p2();
    return 0;


}










