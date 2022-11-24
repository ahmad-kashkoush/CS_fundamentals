//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
class Trie{
private:
    map<char, Trie *> child ;//
    /*
    [a, fjd]
    [c,--]
    [b,*/
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
                char ch=str[idx];
                if(!cur->child.count(ch))
                    cur->child[ch]=new Trie();
                cur=cur->child[ch];
            }
            cur->isLeaf=true;

    }


    bool word_exist(string value){
        Trie *cur=this;
        for(int i=0;i<value.size();i++){
            char ch=value[i];
            if(!cur->child.count(ch))
                return false;
            cur=cur->child[ch];
        }
        return cur->isLeaf;
    }


      bool  prefix_exist(string value,int idx=0){
        if(idx==(int)value.size())
            return true;
        int cur=value[idx];
        if(child[cur]==0)
            return false;
        return child[cur]->prefix_exist(value, idx+1);

    }

    void getAllStrings(vector<string> &res, string str=""){
        /*
        1. [need]
            - fill res vector with values of the tree
            - values must be full words
            - I'll search in the map keys as it's sorted

        */
        if(isLeaf)
            res.push_back(str);

            // a->char, b->trie
            for(auto [a, b]:  child){
                if(b)
                 b->getAllStrings(res, str+a);

            }
    }

    void getAutoComplete(string str, vector<string> &res){
            Trie *cur=this;
            for(auto i:str){
                if(!cur->child.count(i))
                    return;
                cur=cur->child[i];
            }
            cur->getAllStrings(res,str);
    }
    bool wordExist1Change(string str){
        vector<string> words;
        getAllStrings(words);
        int x=str.size();
        for(string word: words){
            int change=0;
            if(x!=word.size())
                continue;
            for(int i=0;i<min(x, (int)word.size());i++)
               change+=(word[i]!=str[i]);

            if(change==1)
                return true;
        }
        return false;
    }
    // doc method
    bool wordExistChange(string str){
            for(int i=0;i<str.size();i++){
                char c=str[i];
                for(char x='a';x<='z';x++){
                    if(x==c)
                        continue;
                    str[i]=x;
                   if(word_exist(str))
                        return true;
                }
                str[i]=c;
            }
            return false;
    }

};

Trie getTrie(){
    Trie tree;
    tree.insert("abcd");
    tree.insert("xyz");
    tree.insert("a");
    tree.insert("ab");
    tree.insert("abx");
    tree.insert("xyzw");
    tree.insert("bcd");
    return tree;
}
void test1(){
    Trie tree;tree=getTrie();
    vector<string> res;
    tree.getAllStrings(res);
    for(auto i:res)
        cout<<i<<"\n";

}

void test2(){
    Trie tree=getTrie();
    vector<string> res;
    tree.getAutoComplete("ab", res);
    for(auto i:res)
        cout<<i<<"\n";

}
void test3(){
    Trie tree=getTrie();
    cout<<tree.wordExistChange("yyz")<<el;
    cout<<tree.wordExistChange("xyz")<<el;
}
void solve(){
    test3();

}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;

    while(t--)
        solve();
    return 0;


}

