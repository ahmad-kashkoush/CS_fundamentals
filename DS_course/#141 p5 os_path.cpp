//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
class TrieOs{
private:
    map<string, TrieOs*> child;
public:
    TrieOs(){}
    // insert
    void insert(const vector<string> &v){
        TrieOs *cur=this;
        for(auto i:v){
            if(!cur->child.count(i))
                cur->child[i]=new TrieOs();
            cur=cur->child[i];

        }
    }
    //subPathExist
    bool subpathExist(const vector<string> &sub){
        TrieOs *cur=this;
        for(auto i:sub){
            if(!cur->child.count(i))
                return false;
            cur=cur->child[i];
        }
        return true;
    }

};





void test(){
    vector<string> v{"home", "software", "eclipse", "bin"};

    TrieOs t;
    t.insert(v);
    vector<string> sub{"home", "software"};
   cout<<t.subpathExist(sub)<<el;
}


void solve(){
        test();
}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;
//    cin>>t;
    while(t--)
        solve();
    return 0;


}










