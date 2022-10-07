#include<iostream>
using namespace std;
struct Queue{
    int arr[100];
    int idx=0;
    Queue(){
        idx=0;
    }
    void add_front(int val){
        for(int i=idx;i>=1;i--)
            arr[i]=arr[i-1];
        arr[0]=val;
        idx++;
    }
    void add_back(int val){
        arr[idx++]=val;
    }
    int remove_front(){
        int val=arr[0];
        for(int i=0;i<idx-1;i++)
            arr[i]=arr[i+1];
        idx--;
        return val;
    }
    void print(){
        for(int i=0;i<idx;i++)
            cout<<arr[i]<<" ";
        cout<<"\n";
    }
};
