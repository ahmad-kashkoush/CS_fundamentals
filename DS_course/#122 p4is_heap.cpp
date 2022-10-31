
#include<iostream>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
class MinHeap{
private:
    int *arr{ };
    int size{};
    int capacity{1000};
    // some index utility
    int parent(int node){
        return (node==0?-1:(node-1)/2);
    }
    int left(int node){
        int p=2*node+1;
        return p>=size? -1: p;
    }
    int right(int node){
        int p=2*node+2;
        return p>=size? -1:p;
    }
        // utility
    void hepifyUp(int child_pos){
        int par_p=parent(child_pos);
        if(child_pos==0| arr[child_pos]>=arr[par_p])
            return;

        swap(arr[par_p],arr[child_pos]);
        hepifyUp(par_p);
    }
    // return the pos of the smallest element after updating
    void hepifyDown(int pos){
        int child=left(pos);
        int right_=right(pos);

        if(child==-1)// no left then no right-->complete tree
            return;
        if(right_!=-1&&arr[child]>arr[right_])
            child=right_;
        if(arr[pos]>arr[child]){
            swap(arr[pos],arr[child]);
            hepifyDown(child);
        }

    }
public:
    MinHeap(){
        arr= new int[capacity];
        size=0;
    }
    MinHeap(const vector<int>& v){
        assert(v.size()<=capacity);
        arr=new int[capacity];
        size=v.size();
        for(int i=0;i<size;i++)// o(n)
            arr[i]=v[i];
        heapify();//o(n);
    }
    void heapify(){
        for(int i=size/2-1;i>=0;i--)// o(n);
            hepifyDown(i);
    }
    void push(int key){
        assert(size+1<=capacity);
        arr[size++]=key;
        hepifyUp(size-1);

    }
    void pop(){
        assert(!isempty());
        arr[0]=arr[--size];
        hepifyDown(0);

    }
    bool isempty(){
        return size==0;
    }
    int top(){
        assert(!isempty());
        return arr[0];
    }
    bool isHeapIterative(int i){
        bool no_more_allowed=false;
        queue<int> nodes;
        nodes.push(0);
        while(!nodes.empty()){
            int sz=nodes.size();
            while(sz--){
                int par=nodes.front();
                nodes.pop();
                int l=left(par),r=right(par);
                if(l!=-1){
                    if(no_more_allowed)
                        return false;
                    if(arr[par]>arr[l])
                        return false;
                }else no_more_allowed=true;

                if(r!=-1){
                    if(no_more_allowed)
                        return false;
                    if(arr[par]>arr[r])
                        return false;
                }else no_more_allowed=true;

            }
        }
        return true;
    }

    bool isHeapRecursive(int parent){
        if(parent==-1)
            return true;
        int l=left(parent);
        int r=right(parent);

        if(l!=-1&&arr[parent]>arr[l])
            return false;
        if(r!=-1&&arr[parent]>arr[r])
           return false;

        return isHeapRecursive(l)&&isHeapRecursive(r);

    }
    bool is_heap_arr(int *p, int n){
        int *old_arr=arr;
        int old_size=size;

        arr=p;
        size=n;

        bool res=isHeapRecursive(0);
        arr=old_arr, size=old_size;
        return res;
    }

    ~MinHeap(){
        delete [] arr;
        arr=nullptr;
    }
};
// creating heap using push technique
MinHeap createHeap_nlogn(vector<int> &v){
        MinHeap heap;
        for(int i=0;i<v.size();i++)
            heap.push(v[i]);
        return heap;
}

void test1(){
        MinHeap heap;
        int arr[]={2,5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30};
        int n=sizeof(arr)/sizeof(arr[0]);
        cout<<heap.is_heap_arr(arr,n);
}

int main(){
    test1();
    cout<<"\nBye";
    return 0;

}
