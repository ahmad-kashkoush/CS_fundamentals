//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
class Trie{
private:
    map<int, Trie *> child ;
    bool isLeaf{ };
public:
    Trie (){}
    // explanation,
    //1.if idx==str.size(), means complete word
    //2. else get the pointer or child number, if it's empty or equal to zero then create
    //3. if not empty, insert the following character in this path
    void insert(string str){
            Trie *cur=this;
            for(int idx=0;idx<str.size();idx++){
                int ch=str[idx]-'a';
                if(!cur->child.count(ch))
                    cur->child[ch]=new Trie();
                cur=cur->child[ch];
            }
            cur->isLeaf=true;

    }


    bool word_exist(string value){
        Trie *cur=this;
        for(int i=0;i<value.size();i++){
            int ch=value[i]-'a';
            if(!cur->child.count(ch))
                return false;
            cur=cur->child[ch];
        }
        return cur->isLeaf;
    }


      bool  prefix_exist(string value,int idx=0){
        if(idx==(int)value.size())
            return true;
        int cur=value[idx]-'a';
        if(child[cur]==0)
            return false;
        return child[cur]->prefix_exist(value, idx+1);

    }
    string first_word_string(const string &str){
            string ans="";

            Trie *cur=this;
            for(int i=0;i<str.size();i++){
                    int ch=str[i]-'a';
                    if(!cur->child.count(ch))
                        return str;
                    ans+=str[i];
                    if(cur->child[ch]->isLeaf)
                        return ans;

                    cur=cur->child[ch];

            }
            return str;

    }




};

void test(){
    Trie t;
    vector<string> v{"xyz", "xyzeA", "a", "bc"};
    for(auto i:v)
        t.insert(i);

    cout<<t.first_word_string("x")<<el;
    cout<<t.first_word_string("xyzabc")<<el;

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










