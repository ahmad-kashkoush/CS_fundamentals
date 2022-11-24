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

    bool isLeaf{ };
    vector<int> id;
public:
    Trie (){}
    void insert(string str, int index){
            Trie *cur=this;
            for(int idx=0;idx<str.size();idx++){
                char ch=str[idx];
                if(!cur->child.count(ch))
                    cur->child[ch]=new Trie();
                cur->child[ch]->id.push_back(index);
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

        void list_substr(const string &str, vector<string> q){
                for(auto i:q)
                    insert(i, 0);
                int n=str.size();
                string tmp;
                for(int i=0;i<n;i++){
                    Trie *cur=this;
                    tmp.clear();
                    int x=i;
                    bool flag=false;
                    while(cur->child.count(str[x])&&x<n){
                        tmp+=str[x];
                        if(cur->child[str[x]]->isLeaf)
                            cout<<tmp<<" ";
                        cur=cur->child[str[x]];
                        x++;
                        flag=true;
                    }

                    if(flag)i=x-1;


                }


        }
        vector<int> get_positions(const string &str){
                Trie *cur=this;
                for(int i=0;i<str.size();i++){
                    if(!cur->child[str[i]])
                        return vector<int> ();
                    cur=cur->child[str[i]];
                }
                return cur->id;
        }

};
class wordFilter{
public:

    Trie prefix_tree;
    vector<string> words_original;
    set<string>notVisited;
    wordFilter(const vector<string> &words){
        words_original=words;


        for(int i=(int)words.size()-1;i>=0;i--){
            if(notVisited.insert(words[i]).second){// will only insert if not visited
                prefix_tree.insert(words[i], i);
            }
        }
    }

    bool is_suffix(string str, string suf){
        if(suf.size()>str.size())
            return false;

        for(int i=(int)suf.size()-1, s=(int)str.size()-1;i>=0&&s>=0;i--,s--){
            if(suf[i]!=str[s])
                return false;
        }
        return true;
    }

    int f(string pre, string suf){

        vector<int> preList=prefix_tree.get_positions(pre);

        for(int i=0;i<preList.size();i++){
            int pos=preList[i];
            if(is_suffix(words_original[pos], suf))
                return pos;
        }
        return -1;
    }
};



void test3(){
    Trie tree;
    vector<string > dic={"aae", "apple", "bannana"};
    for(int i=0;i<dic.size();i++)
        tree.insert(dic[i], i);
    wordFilter Filter(dic);
    cout<<Filter.f("a", "e")<<el;
    cout<<Filter.f("b", "ae")<<el;

}
void test2(){
    vector<string> q={"xy", "ab", "t", "yz"};
    Trie trie;
    trie.list_substr("heyabcdtwxyw",q);

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

