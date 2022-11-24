//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
const int m=26;
class Trie{
private:
    Trie *child[m] {};

public:
    Trie (){
        memset(child, 0, sizeof(child));
    }
    // explanation,
    //1.if idx==str.size(), means complete word
    //2. else get the pointer or child number, if it's empty or equal to zero then create
    //3. if not empty, insert the following character in this path
    void insert(string str){
            Trie *cur=this;
            string strr=str;
            reverse(all(strr));
            for(int idx=0;idx<(int)strr.size();idx++){
                int ch=strr[idx]-'a';
                if(!cur->child[ch])
                    cur->child[ch]=new Trie();
                cur=cur->child[ch];
            }


    }


    bool suffix_exist(string value){
        Trie *cur=this;
        reverse(all(value));
        for(int i=0;i<value.size();i++){
            int ch=value[i]-'a';
            if(!cur->child[ch])
                return false;
            cur=cur->child[ch];
        }
        return true;
    }






};

void test(){
    Trie t;
    vector<string> v{"xyz", "xyzeA", "a", "bc"};
    for(auto i:v)
        t.insert(i);

    cout<<t.suffix_exist("yz")<<el;

}
void solve(){
    test();

}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;

    while(t--)
        solve();
    return 0;


}











