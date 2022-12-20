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
    struct LinkedPhoneEntry{
        phoneEntry item;
        LinkedPhoneEntry *next {};

        LinkedPhoneEntry(phoneEntry item):item(item){}
    };
    int table_size;// size of bucket
    vector<LinkedPhoneEntry*> table;
public:
    PhoneHashTable(int Size){
        table_size=Size;
        table.resize(table_size);
    }
    void put(phoneEntry phone){
        int index=phone.Hash()%table_size;

        if(!table[index]){
            table[index]= new LinkedPhoneEntry(phone);
            return;
        }


        LinkedPhoneEntry *cur=table[index];
        for(;cur->next;cur=cur->next){
            if(cur->item.name==phone.name){
                cur->item = phone;// update and exit
                return;
            }

        }
        if(cur->item.name==phone.name)
            cur->item=phone;
        else
            cur->next=new LinkedPhoneEntry(phone);

        // if there's no key like that then push it

    }

    void printAll(){
        for(int hash=0;hash<table_size;hash++){
            if(!table[hash])
                continue;
            LinkedPhoneEntry *cur=table[hash];
            cout<<"Hash "<<hash<<" : ";
            for(;cur;cur=cur->next)
                cur->item.print();
            cout<<el;
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








