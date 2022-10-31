#include<iostream>
#include<cassert>
#include<vector>
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
    void hepifyDown(int pos){// o(h)
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
    // my way which take more memory
//    void print_less_than(int value, int parent=0){
//            vector<int> deleted;
//            while(!isempty()&& value>top()){//o(nlogn)
//                cout<<top()<<" ";//o(1)
//                deleted.push_back(top());//o(h)
//                pop();//
//            }
//            for(auto i:deleted)push(i);//o(n)
//    }
    void print_less_than(int value, int parent=0){//o(h)
        if(parent==-1||arr[parent]>=value)
            return;
        cout<<arr[parent]<<" ";
        print_less_than(value, left(parent));//o(h)
        print_less_than(value, right(parent));//o(h)
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
    vector<int> v{2,17,22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30  };
    MinHeap heap=createHeap_nlogn(v);// takes o(nlogn);
    MinHeap heap1(v);// takes only o(n)
    while(!heap1.isempty()){
        cout<<heap1.top()<<" ";
        heap1.pop();
    }
}
void test2(){
    vector<int> v{2,17,22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30  };

    MinHeap heap1(v);// takes only o(n)
    heap1.print_less_than(10);
}

int main(){
//    test1();
    test2();
    cout<<"\nBye";
    return 0;

}

