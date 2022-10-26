#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

class BinarySearchTree {
private:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };

	// Modified search: Return chain of ancestors from node to target
	bool find_chain(vector<BinarySearchTree*> &ancestors, int target) {
		ancestors.push_back(this);

		if (target == data)
			return true;

		if (target < data)
			return left && left->find_chain(ancestors, target);

		return right && right->find_chain(ancestors, target);
	}

public:

	BinarySearchTree(int data) :
			data(data) {
	}
	// look look
	// you've created a preorder traversal
	// now you should create a vector of next_idx for every value
	// and split without for loop
//	vector<int> next_greater(deque<int> preorder){
//        vector<int> v((int) preorder.size());
//
//        stack<int> st;
//        for(int i=0;i<preorder.size();i++){
//            while(!st.empty()&&preorder[i]>preorder[st.top()]){
//                v[st.top()]=i;
//                st.pop();
//            }
//            st.push(i);
//        }
//
//        while(!st.empty()){
//            v[st.top()]=v.size();
//            st.pop();
//        }
//        return v;
//
//	}
//	BinarySearchTree(deque<int> &preorder,const vector<int>& next_idx, int start=0, int end=-1){
//        if(end==-1)
//            end=(int) preorder.size()-1;
//        data=preorder[start];
//
//        int id=next_idx[start];
//        if(id>end)
//            id=end+1;
//        if(start+1<=id-1)
//            left=new BinarySearchTree(preorder, next_idx, start+1, id-1);
//        if(end>=id)
//            right= new BinarySearchTree(preorder, next_idx, id, end);
//
//
//	}
//	BinarySearchTree(deque<int> &preorder):
//        BinarySearchTree(preorder, next_greater(preorder)){}

    // BinarySearch Tree using min and max method
    bool between(deque<int> preorder, int mn, int mx){
       return (!preorder.empty())&&(preorder[0]>mn&&preorder[0]<mx);
    }
    BinarySearchTree(deque<int> &preorder, int mn=0, int mx=1001){
        data=preorder[0];
        preorder.pop_front();

        // updating the left
        if(between(preorder, mn, data))
            left= new BinarySearchTree(preorder, mn, data);
        if(between(preorder, data, mx))
            right= new BinarySearchTree(preorder, data, mx);

    }

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	////////////////////////////////////////////

	void insert(int target) {
		if (target < data) {
			if (!left)
				left = new BinarySearchTree(target);
			else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new BinarySearchTree(target);
			else
				right->insert(target);
		} // else: exists already
	}

	bool search(int target) {	// tail recursion
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}




};

void test2(){
    deque<int> preorder={50, 20, 15, 45, 35, 60, 70, 73};
    BinarySearchTree b(preorder);
    b.print_inorder();
//    vector<int> n=b.next_greater(preorder);
//    for(auto i:n)
//        cout<<i<<" ";
}

int main() {
    test2();

}


