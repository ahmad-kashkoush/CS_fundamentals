#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include<utility>
using namespace std;

class BinarySearchTree {
private:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };



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
    bool between(deque<int> level, int mn, int mx){
       return (!level.empty())&&(level[0]>mn&&level[0]<mx);
    }
    BinarySearchTree(deque<int> &level){

                queue<pair<int, pair<int, int>> > nodes;
                queue<BinarySearchTree *> n;
                nodes.push({level[0],{0, 1001} });
                data=level[0];
                BinarySearchTree *tree=new BinarySearchTree(data);

                level.pop_front();
                while(!nodes.empty()){
                        int sz=nodes.size();
                        while(sz--){
                            BinarySearchTree *cur=new BinarySearchTree(nodes.front().first);
                            int mn=nodes.front().second.first;
                            int mx=nodes.front().second.second;
                            int data=cur->data;
                            nodes.pop();

                            // update the left
                            if(between(level,mn, data)){
                                int new_data=level[0];
                                cur->left= new BinarySearchTree(new_data);
                                level.pop_front();
                                nodes.push( {new_data, {mn, data} } );
                            }

                            if(between(level, data, mx)){
                                int new_data=level[0];
                                level.pop_front();
                                cur->right=new BinarySearchTree(new_data);
                                nodes.push({new_data, {data, mx} });
                            }
                        }


                }

                data=n.front()->data;
                left=n.front()->left;
                right=n.front()->right;

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

void buildTree(BinarySearchTree b, deque<int> d){
    for(int i=1;i<d.size();i++)
        b.insert(d[i]);
}

void test2(){
    deque<int> level_order={50, 20, 60, 15, 45, 70, 35, 73};
    BinarySearchTree b(level_order[0]);
    buildTree(b, level_order);
    b.print_inorder();
//    vector<int> n=b.next_greater(preorder);
//    for(auto i:n)
//        cout<<i<<" ";
}

int main() {
    test2();

}



