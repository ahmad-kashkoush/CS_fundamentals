//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
#include<bits/stdc++.h>
#define el '\n'
using namespace std;
class kthNumberProcessor{
    int k{ };
    priority_queue<int> pq;
public:
    kthNumberProcessor(int k):k(k){}

    int next(int num){

        if(pq.size()<k)
            pq.push(num);
        else if(num<pq.top()){
            pq.pop();
            pq.push(num);
        }
        return pq.top();
    }
};
int main() {
    kthNumberProcessor processor(4);
    int num;
    while(cin>>num)
        cout<<processor.next(num)<<endl;
    return 0;


}










