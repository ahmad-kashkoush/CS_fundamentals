#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;
bool is_degenerate(vector<int> &preorder){
    int n=preorder.size();
    // loop to n-2;
    int mn=0, mx=1000;
    for(int i=1;i<n;i++){
     if(preorder[i]<mn||preorder[i]>mx)
        return false;
     if(preorder[i]>preorder[i-1])
        mn=preorder[i-1]+1;
     else
        mx=preorder[i-1]-1;

    }
    return true;


}

void test1(){
    int n; cin>>n;
    vector<int> preorder(n);
    for(auto &i:preorder)cin>>i;
    cout<<(is_degenerate(preorder)?"YES":"NO")<<endl;
}

int main() {
    test1();

}

