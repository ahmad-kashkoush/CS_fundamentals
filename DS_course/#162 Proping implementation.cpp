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
const int mod=65407;
using namespace std;
// what i'm going to do is phone search
/**
  search the phone name*key*, to get the phone number*value or entry*
*/
int getNum(char c){
    if(c>='0'&&c<='9')return c-'0'+2*26;
    if(c>='a'&&c<='z') return c-'a';
    if(c>='A'&&c<='Z') return c-'Z'+26;
}
int hash_num(int value, int n=65407){
    ll nn=n;
    return (ll)(value%nn+nn)%nn;
}
int hash_string(string str, int n=mod) {
	long long nn = n;
	long long sum = 0;
	for (int i = 0; i < (int) str.size(); ++i)
		sum = (sum * 62 + getNum(str[i])) % nn;
	return sum % nn;
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
        return hash_string(name, mod);
    }

};
// building our hash table
class PhoneHashTable{
private:
    int table_size;// size of bucket
    vector<phoneEntry *> table;
    phoneEntry  *deleted= new phoneEntry("","");
public:
    PhoneHashTable(int Size){
        table_size=Size;
        table.resize(table_size);
    }

    bool  put(phoneEntry phone){
        int idx=phone.Hash()%table_size;


        for(int step=0;step<table_size;step++){
            if(table[idx]==deleted||!table[idx]){
                table[idx]=new phoneEntry(phone.name, phone.PhoneNum);
                return true;
            }else if(table[idx]->name==phone.name){
                table[idx]->PhoneNum=phone.PhoneNum;
                return true;
            }

            idx=(idx+1)%table_size;

        }
        return false;
    }

    bool Remove(phoneEntry phone){
        int idx=phone.Hash()%table_size;

        for(int step=0;step<table_size;step++){
            if(!table[idx])
                return false;
            if(table[idx]->name==phone.name){
                delete table[idx];
                table[idx]=deleted;
                return true;
            }


            idx=(idx+1)%table_size;

        }
        return true;
    }


    void printAll(){
        for(int i=0;i<table_size;i++){

            if(table[i]==deleted)
                cout<<"X";
            else if(!table[i])
                cout<<"E";
            else
                table[i]->print();
            cout<<el;
        }

    }


};
void simulation(){
    PhoneHashTable table(10);
	table.put(phoneEntry("mostafa", "604-401-120"));
	table.put(phoneEntry("mostafa", "604-401-777"));	// update
	table.put(phoneEntry("ali", "604-401-343"));
	table.put(phoneEntry("ziad", "604-401-17"));
	table.put(phoneEntry("hany", "604-401-758"));
	table.put(phoneEntry("belal", "604-401-550"));
	table.put(phoneEntry("john", "604-401-223"));

//	table.Remove(phoneEntry("mostafa", "604-401-120"));
//    table.Remove(phoneEntry("john", "604-401-223"));
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







