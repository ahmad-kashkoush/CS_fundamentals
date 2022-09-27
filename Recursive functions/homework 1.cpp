#include<bits/stdc++.h>
#define ll long long
#define el "\n"
using namespace std;
int factorial(int n){
     cout<<"factorial when n= "<<n<<el;
     if(n==1)
        return 1;// base case
     return factorial(n-1)*n;
}
void print_triangle(int levels){
    if(levels==0)
        return;
    print_triangle(levels-1);
    cout<<string(levels, '*')<<el;

}

//void print_seq(int n, int length_of_seq=0){
////    static int length_of_seq=0;
//    cout<<n<<" ";
//    length_of_seq++;
//    if(n==1){
//        cout<<"length_of_seq: "<<length_of_seq;
//        return;
//    }
//
//    if(n%2==0)
//        print_seq(n/2, length_of_seq);
//    else
//        print_seq(3*n+1, length_of_seq);
//}
int length_3n_1(int n){
    if(n==1)
        return 1;
    if(n%2)
        return 1+length_3n_1(3*n+1);
    return 1+length_3n_1(n/2);
}
// power function
int power(int n, int m){
    if(m==0)
        return 1;
    return n*power(n, m-1);
}
int arr_max(int arr[], int len){
    if(len==0)
        return arr[0];
    int subresult=arr_max(arr, len-1);
    return max(subresult, arr[len-1]);
}
int arr_sum(int arr[], int len){
    cout<<"function call:"<<arr[len-1]<<el;
    if(len==1)
        return  arr[0];
    int sum=arr_sum(arr, len-1)+arr[len-1];
    return sum;
}
double avr(double arr[], int len){
    if(len==1.0)
        return arr[0];
    double avrage=avr(arr, len-1)*(len-1)/len+arr[len-1]/len;
    return avrage;
}
void arr_increment(int arr[], int len){

    if(len==1)
         return;
    arr[len-1]+=len-1;
    arr_increment(arr, len-1);


}
void arr_accumulate(int arr[], int len){
    if(len==1)
        return;
    arr_accumulate(arr, len-1);
    arr[len-1]+=arr[len-2];
}
void left_max(int arr[], int len){
    if(len==1)
        return;
    left_max(arr, len-1);
    arr[len-1]=max(arr[len-1], arr[len-2]);
}
int main(){
   int arr[]={1, 3, 5, 7, 4, 2};
   left_max(arr, 6);
   for(int i=0;i<6;i++)
    cout<<arr[i]<<' ';
    return 0;
}
