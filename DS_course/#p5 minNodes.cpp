#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		int data { };
		int height { };
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(int data) :
				data(data) {
		}

		int ch_height(BinaryNode* node) {	// child height
			if (!node)
				return -1;			// -1 for null
			return node->height;	// 0 for leaf
		}
		int update_height() {	// call in end of insert function
			return height = 1 + max(ch_height(left), ch_height(right));
		}
		int balance_factor() {
			return ch_height(left) - ch_height(right);
		}
	};

	BinaryNode *root { };

	///////////////////////////
	bool search(int target, BinaryNode* node) {
		if(!node)
			return false;

		if (target == node->data)
			return true;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode* right_rotation(BinaryNode* Q) {
		cout << "right_rotation " << Q->data << "\n";
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) {
		cout << "left_rotation " << P->data << "\n";
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}

	BinaryNode* balance(BinaryNode* node) {
		if (node->balance_factor() == 2) { 			// Left
			if (node->left->balance_factor() == -1)	// Left Right?
				node->left = left_rotation(node->left);	// To Left Left

			node = right_rotation(node);	// Balance Left Left
		} else if (node->balance_factor() == -2) {
			if (node->right->balance_factor() == 1)
				node->right = right_rotation(node->right);

			node = left_rotation(node);
		}
		return node;
	}

	BinaryNode* insert_node(int target, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target);
			else
				node->right = insert_node(target, node->right);
		}
		node->update_height();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(int target, BinaryNode* node) {
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			BinaryNode* tmp = node;

			if (!node->left && !node->right)	// case 1: no child
				node = nullptr;
			else if (!node->right) 	// case 2: has left only
				node = node->left;		// connect with child
			else if (!node->left)	// case 2: has right only
				node = node->right;
			else {	// 2 children: Use successor
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data;	// copy & go delete
				node->right = delete_node(node->data, node->right);
				tmp = nullptr;	// Don't delete me. Successor will be deleted
			}
			if (tmp)
				delete tmp;
		}
		if (node) {
			node->update_height();
			node = balance(node);
		}
		return node;
	}

	bool is_bst(BinaryNode* node) {
		bool left_bst = !node->left || node->data > node->left->data && is_bst(node->left);

		if (!left_bst)
			return false;

		bool right_bst = !node->right || node->data < node->right->data && is_bst(node->right);
		return right_bst;
	}

	void verify() {
		assert(abs(root->balance_factor()) <= 1);
		assert(is_bst(root));
	}

	void print_inorder(BinaryNode* node) {
		if(!node)
			return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}


public:
	void insert_value(int target) {
		if (!root)
			root = new BinaryNode(target);
		else
			root = insert_node(target, root);

		verify();
	}

	void delete_value(int target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}
	int AVLHeight(int value){
        if(value==0)
            return 1;
      if(value==1)
            return 2;
      return 1+AVLHeight(value-1)+AVLHeight(value-2);
	}


};


void print(vector<int> v){
    for(auto i:v)
        cout<<i<<" ";
    cout<<"\n";
}
void test2(){
    AVLTree tree;
    vector<int> v(20);
    for(int i=0;i<20;i++)
        v[i]=i+1;

    print(v);
    for(auto i:v)
        cout<<tree.AVLHeight(i)<<" ";

}

int main() {
//	test1();
    test2();

	cout << "bye\n";

	return 0;
}
