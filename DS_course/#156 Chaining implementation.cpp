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
// what i'm going to do is phone search
/**
  search the phone name*key*, to get the phone number*value or entry*
*/
int hash_string(string name, int n){
    ll nn=n;
    ll sum=0;
    for(int i=0;i<name.size();i++)
       sum=(sum*26+name[i]-'a')%nn ;

    return sum;

}
struct phoneEntry{
    string name, PhoneNum;
    const  static int internal_limit=INT_MAX;

    phoneEntry(string a, string b):
        name(a),PhoneNum(b){}
    void print(){
        cout<<"("<<name<<", "<<PhoneNum<<")";
    }
    int Hash(){
        return hash_string(name, internal_limit);
    }

};
// building our hash table
class PhoneHashTable{
private:
    int table_size;// size of bucket
    vector<vector<phoneEntry> > table;
public:
    PhoneHashTable(int Size){
        table_size=Size;
        table.resize(table_size);
    }
    void put(phoneEntry phone){
        int index=phone.Hash()%table_size;// this way i'm getting the bucket || hash code
        // is we've the same key, then we'll just update, else push
        for(int i=0;i<table[index].size();i++){
            if(table[index][i].name==phone.name){
                table[index][i] = phone;// update and exit
                return;
            }

        }
        // if there's no key like that then push it
        table[index].push_back(phone);
    }
    // if found remove it and return true, else return false
    bool Remove(phoneEntry phone){
        int index=phone.Hash()%table_size;
        for(int i=0;i<table[index].size();i++){
            if(table[index][i].name==phone.name){
                //! make it last element and the pop it from the vector
                swap(table[index][i], table[index].back());
                table[index].pop_back();
                return true;
            }
        }
        return false;
    }
    // get to update the argument if found
    int get(phoneEntry &phone){
        int index=phone.Hash()%table_size;
        for(int i=0;i<table[index].size();i++){
            if(table[index][i].name==phone.name){
                phone=table[index][i];
                return true;
            }
        }
        return false;
    }
    void printAll(){
        for(int i=0;i<table_size;i++){
            if(table[i].size()==0)
                continue;
            cout<<"Hash Code:"<< i<<": ************\n";
            for(auto x:table[i]){
                x.print();
                cout<<el;
            }

        }
    }


};
void simulation(){
    PhoneHashTable table(3);
	table.put(phoneEntry("mostafa", "604-401-120"));
	table.put(phoneEntry("mostafa", "604-401-777"));	// update
	table.put(phoneEntry("ali", "604-401-343"));
	table.put(phoneEntry("ziad", "604-401-17"));
	table.put(phoneEntry("hany", "604-401-758"));
	table.put(phoneEntry("belal", "604-401-550"));
	table.put(phoneEntry("john", "604-401-223"));

    table.Remove(phoneEntry("john", "604-401-223"));
	table.printAll();

}
void solve(){
    simulation();
    cout<<el;
}
int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    solve();
    return 0;


}







