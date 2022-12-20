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
void IsIncreasingArray(){
    int n;cin>>n;
    int arr[n];
    cin>>arr[0];
   int mx=arr[0];
   for(int i=1;i<n;i++){
     cin>>arr[i];
     if(arr[i]>=mx)
        mx=arr[i];
     else {
        cout<<"NO";
        return;
     }
   }
   cout<<"YES";
}
void MinMax(){

    int n; cin>>n;
    int prv;cin>>prv;
    cout<<prv<<" ";
    while(--n){
        int x; cin>>x;
        if(x!=prv)
            cout<<x<<" ";
        prv=x;

    }
}


int main() {
    ios_base::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int t=1;
  //  cin>>t;
    while(t--)
        MinMax();
    return 0;


}










