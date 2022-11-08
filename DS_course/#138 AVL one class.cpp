#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class AVLTree {
private:


		int data { };
		int height { };
		AVLTree* left { };
		AVLTree* right { };
		AVLTree(int data) :
				data(data) {
		}
        // no need for a parameter here
		int ch_height() {	// child height// -1 for null

			return height;	// 0 for leaf
		}
		// needs to be rewritten
		int update_height() {	// call in end of insert function
		    int mx=-1;
		    if(left)
                mx=left->ch_height();
            if(right)
                mx=max(mx, right->ch_height());
			return height = 1 + mx;
		}
		// rewrite
		int balance_factor() {
			return left->ch_height() - right->ch_height();
		}

    // no need


	///////////////////////////
	// rewritten

    // rewrite
	AVLTree* right_rotation() {
		cout << "right_rotation " << data << "\n";
		AVLTree* P = left;
		left = P->right;
		P->right = this;
		update_height();
		P->update_height();
		return P;
	}
    // re
	AVLTree* left_rotation() {
		cout << "left_rotation " << data << "\n";
		AVLTree* Q =right;
		right = Q->left;
		Q->left = this;
		update_height();
		Q->update_height();
		return Q;
	}

	AVLTree* balance() {
	    AVLTree *node;
		if (balance_factor() == 2) { 			// Left
			if (left->balance_factor() == -1)	// Left Right?
				left = left->left_rotation();	// To Left Left

			node= right_rotation();	// Balance Left Left
		} else if (balance_factor() == -2) {
			if (right->balance_factor() == 1)
				right = right->right_rotation();

			node = left_rotation();
		}
		return node;
	}

	AVLTree* insert_node(int target) {
		if (target < data) {
			if (!left)
				left = new AVLTree(target);
			else	// change left. update left as it might be balanced
				left = left->insert_node(target);
		} else if (target >data) {
			if (!right)
				right = new AVLTree(target);
			else
				right = right->insert_node(target);
		}
		update_height();
		return balance();
	}

	AVLTree* min_node(AVLTree* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}
    void special_delete(AVLTree *child){
        data=child->data;
        left=child->left;
        right=child->right;
        delete child;
	}
    // rewrite your special delete
	AVLTree* delete_node(int target, AVLTree* node) {
		if (!node)
			return nullptr;

		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else {
			AVLTree* tmp = node;

			if (!node->left && !node->right)	// case 1: no child
				node = nullptr;
			else if (!node->right) 	// case 2: has left only
				node->special_delete(node->left);	// connect with child
			else if (!node->left)	// case 2: has right only
				node->special_delete(node->right);
			else {	// 2 children: Use successor
				AVLTree* mn = min_node(node->right);
				node->data = mn->data;	// copy & go delete
				node->right = delete_node(node->data, node->right);
				tmp = nullptr;	// Don't delete me. Successor will be deleted
			}
			if (tmp)
				delete tmp;
		}
		if (node) {
			node->update_height();
			node = node->balance();
		}
		return node;
	}
    // rewrite
	bool is_bst() {
		bool left_bst = !left || data > left->data && left->is_bst();

		if (!left_bst)
			return false;

		bool right_bst = !right || data < right->data && right->is_bst();
		return right_bst;
	}

	void verify() {
		assert(abs(balance_factor()) <= 1);
		assert(is_bst());
	}




public:
	void insert_value(int target) {
		if (this==nullptr){
            AVLTree *node=new AVLTree(target);
            data=node->data;
            left=node->left;
            right=node->left;
		}

		else{

			insert_node(target);

		}

		verify();
	}

	void delete_value(int target) {
		if(target==data&&!left&&!right)
            return;



        delete_node(target, this);

	}

	bool search(int target) {

		if (target == data)
			return true;
		if ( target < data)
			return left&&left->search(target);
        return right&&right->search(target);
	}

	void print_inorder() {

        if(left)
            left->print_inorder();
		cout <<data << " ";
		if(right)
            right->print_inorder();

	}

	void level_order_traversal() {
		queue<AVLTree*> nodes_queue;
		nodes_queue.push(this);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout<<"Level "<<level<<": ";
			while(sz--) {
				AVLTree*cur = nodes_queue.front();
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
};


void test1() {
	AVLTree *tree(0);

	for (int i = 0; i <= 32; ++i) {	// degenerate
		tree->insert_value(i);
		tree->level_order_traversal();
	}
}

int main() {
	test1();
//    test2();

	cout << "bye\n";

	return 0;
}




/*


 Level 0: 0
 Level 1: 1
 ******************
 Level 0: 1
 Level 1: 0 2
 ******************
 Level 0: 1
 Level 1: 0 2
 Level 2: 3
 ******************
 Level 0: 1
 Level 1: 0 3
 Level 2: 2 4
 ******************
 Level 0: 3
 Level 1: 1 4
 Level 2: 0 2 5
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 Level 3: 7
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 7
 Level 3: 6 8
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 8
 Level 3: 4 6 9
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 9
 Level 3: 4 6 8 10
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 10
 Level 3: 0 2 4 6 11
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 11
 Level 3: 0 2 4 6 10 12
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 12
 Level 3: 0 2 4 6 8 10 13
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 Level 4: 15
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 15
 Level 4: 14 16
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 16
 Level 4: 12 14 17
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 17
 Level 4: 12 14 16 18
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 18
 Level 4: 8 10 12 14 19
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 19
 Level 4: 8 10 12 14 18 20
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 20
 Level 4: 8 10 12 14 16 18 21
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 21
 Level 4: 8 10 12 14 16 18 20 22
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 22
 Level 4: 0 2 4 6 8 10 12 14 23
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 23
 Level 4: 0 2 4 6 8 10 12 14 22 24
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 24
 Level 4: 0 2 4 6 8 10 12 14 20 22 25
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 25
 Level 4: 0 2 4 6 8 10 12 14 20 22 24 26
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 26
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 27
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 27
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 26 28
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 28
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 29
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 Level 5: 31
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 31
 Level 5: 30 32


 */

