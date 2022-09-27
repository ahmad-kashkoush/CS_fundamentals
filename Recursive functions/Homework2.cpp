#include<bits/stdc++.h>
#include <ext/rope>
#define ll long long
#define el "\n"
using namespace std;
using namespace __gnu_cxx;
void right_max(int arr[], int len, int start=0) {
    if(len==start+1)
        return;
    arr[len-2]=max(arr[len-1], arr[len-2]);
    right_max(arr, len-1, start);
}
int suffix(int arr[], int len, int n) {
    if(n==1)
        return arr[len-1];
    return suffix(arr, len-1, n-1)+arr[len-1];
}
int prefix(int arr[], int len, int n) {
    if(n==0)
        return 0;
    return prefix(arr, n-1,n-1)+arr[n-1];

}
bool is_palindrome(int arr[], int len, int start=0, int sub=true) {
    if(!sub)
        return false;
    sub=arr[start]==arr[len-1];
    if(len==start+1)
        return sub;
    return is_palindrome(arr, len-1, start+1, sub);
}
bool is_palindromev2(int arr[], int end) {
    if(end<=0)
        return true;
    if(arr[0]!=arr[end])
        return false;
    return is_palindromev2(arr+1, end-2);
}
bool is_prefix(string main, string prefix) {
    if(prefix.empty())
        return true ;
    if(main[0]!=prefix[0])
        return false;

    prefix=prefix.substr(1);
    main=main.substr(1);
    return is_prefix(main, prefix);
}
bool is_prime(int num, int divisor=2) {
    if(divisor>=num&&num>=2)
        return true;
    if(num%divisor==0||num<2)
        return false;
    return is_prime(num, divisor+1);
}
int count_primes(int start, int end) {
    if(start==end)
        return is_prime(end);
    return count_primes(start+1, end)+is_prime(start);

}
int fib(int n) {
    if(n==0||n==1)
        return 1;
    return fib(n-1)+fib(n-2);
}
int path_sum(int arr[3][3],int Row, int Col, int row, int col){
    if(row==Row&&col==Col)
        return 0;
    bool r=row<Row-1,c=col<Col-1;
    int mx=0;
    int idx, idy;
    if(r&&mx<arr[row+1][col])
        mx=arr[row+1][col],
        idx=row+1, idy=col;
    if(c&&mx<arr[row][col+1])
        mx=arr[row][col+1],
        idx=row, idy=col+1;
    if(c&&r&&mx<arr[row+1][col+1])
        mx=arr[row+1][col+1],
        idx=row+1, idy=col+1;
    return path_sum(arr, idx, idy, Row, Col)+arr[row][col];


}
int main() {
    int arr[3][3]= {{1, 7, 8},{2, 10, 11},{20, 5, 9}};
    cout<<path_sum(arr,3, 3, 0, 0);
    return 0;
}

