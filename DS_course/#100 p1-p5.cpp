#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
	int data { };
	BinarySearchTree* left { };
	BinarySearchTree* right { };

public:

	BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
			data(data), left(left), right(right) {
	}

	void get_inorder(vector<int>& values) {
		if (left)
			left->get_inorder(values);
		values.push_back(data);
		if (right)
			right->get_inorder(values);
	}




	// my base case is to get the value , so i don't need to search anymore
	// if (value<data) and there's left then search in the left side
	// else if(value>data) and there's right then serach in the right side
	bool Search(int value){
        if(data==value)
            return true;
        if(value<data)
            return left&& left->Search(value);
        return right&& right->Search(value);


	}
	// it's easy actually
    bool Search_iterative(int value){
           BinarySearchTree *node=this;
           while(node){
                if(node->data==value)
                    return true;
                else if(node->data>value)
                        node=node->left;
                else
                    node=node->right;
           }
           return false;
    }

    bool is_bst(int mn=INT_MIN, int mx=INT_MAX){
        // first of all tree is not BST if it's left>data||right<data
        // if my tree got to it's end then return true because there's nothing stopped it
        // it's ok your solution is correct but it'll be wrong because you didn't apply min,max trick
        bool inPeriod=data>mn&&data<mx;
        if(!inPeriod)
            return false;
        bool left_bst=!left||left->is_bst(mn, data)||left->data<data;
        bool right_bst=!right||right->is_bst(data, mx)||right->data>data;
        return right_bst&&left_bst;


    }
    // this my trivial way
    int kth_smallest(int &k){
       int ans=-1234;
        vector<int> inorder;
        get_inorder(inorder);
        if(k>0&&k<=inorder.size())
            ans=inorder[k-1];
        return ans;
    }
    // doc amazing way but still like mine
    int kth_smallest2(int &k){
        if(k==0)
            return -1234;
        if(left){
            int res=left->kth_smallest2(k);
            if(k==0)// line 90 will minus it
                return res;
        }
        k--;
        if(k==0)
            return data;
        if(right)
            return right->kth_smallest2(k);
        return -1234;
    }
    int lca(int x, int y){
        if(x>data&& y>data)
            return right->lca(x, y);
        if(x<data&& y<data)
            return left->lca(x, y);
        return data;
    }

	void level_order_traversal2() {
		queue<BinarySearchTree*> nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				BinarySearchTree*cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}

	void insert(int target) {
		if (target < data) {
			if (!left) {
				left = new BinarySearchTree(target);
			} else
				left->insert(target);
		} else if (target > data) {
			if (!right)
				right = new BinarySearchTree(target);
			else
				right->insert(target);
		} // else: exists already
	}

};
// p#3 array to balanced binary search tree
// it's idea is just binary search algorithm implementation
BinarySearchTree *build_balanced_bst_tree(vector<int> &v, int start=0, int end=-10){
    if(end==-10)
        end=(int)v.size()-1;

    if(end<start)
        return nullptr;

    int mid=(start+end)/2;
    BinarySearchTree *left=build_balanced_bst_tree(v, start, mid-1);
    BinarySearchTree *right=build_balanced_bst_tree(v, mid+1, end);
    BinarySearchTree *root=new BinarySearchTree(v[mid],  left, right);

    return root;
}
void test1(){
    BinarySearchTree t1(50);
    t1.insert(20);
    t1.insert(45);
    t1.insert(35);
    t1.insert(15);
    t1.insert(60);
    t1.insert(70);
    t1.insert(73);
    int x=5;
    cout<<(t1.is_bst()?"YES":"NO");
}
void test2(){
    // this test is for problem 3 of building balanced BST;
    vector<int> v={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    BinarySearchTree *t2=build_balanced_bst_tree(v);
    int t=5;
    while(t--){
        int x; cin>>x;
        cout<<t2->kth_smallest2(x)<<endl;
    }
//    t2->level_order_traversal2();
}
int main(){
//    test1();
    test2();

}
