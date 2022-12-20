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
int countUniqueAnagrams(const string &str){
    vector<string> substrings;
    unordered_set<string> s;
    for(int i=0;i<(int)str.size()-1;i++){
        for(int end=i;end<str.size();end++){
            string tmp=str.substr(i, end-i+1);
            sort(all(tmp));
            s.emplace(tmp);
        }
    }
    return s.size();
}
void solve(){
    cout<<countUniqueAnagrams("abba")<<el;
    cout<<countUniqueAnagrams("aaaaa")<<el;
    cout<<countUniqueAnagrams("abcba")<<el;
}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;
  //  cin>>t;
    while(t--)
        solve();
    return 0;


}










