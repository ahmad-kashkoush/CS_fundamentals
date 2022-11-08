#include <iostream>
#include <cassert>
#include <queue>
#define el "\n"
using namespace std;


class AVLTree {
private:
	struct BinaryNode {
		string data { };
		bool isFull{};
		int height { };
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(string data, bool isFull) :
				data(data), isFull(isFull) {
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
	// return if full
	int search(string target, BinaryNode* node) {
		if(!node)
			return -1;

		if (target == node->data)
			return node->isFull;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}
//    bool pre_compare(string a, string b){
//        if(b.size()<a.size())
//            return false;
//        for(int i=0;i<a.size();i++){
//            if(a[i]!=b[i])
//                return false;
//        }
//        return true;
//    }
//    bool prefix_exist(string target, BinaryNode *node){
//        		if(!node)
//                    return false;
//
//		if (node->data==target)
//			return true;
//
//		if (target < node->data)
//			return prefix_exist(target, node->left);
//
//		return prefix_exist(target, node->right);
//    }
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

	BinaryNode* insert_node(string target, bool ifFull, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target, ifFull);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, ifFull, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target, ifFull);
			else
				node->right = insert_node(target, ifFull, node->right);
		}else{
            node->isFull=ifFull;
		}
		node->update_height();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}

	BinaryNode* delete_node(string target, BinaryNode* node) {
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
	void insert_value(string target, bool isFull) {
		if (!root)
			root = new BinaryNode(target, isFull);
		else
			root = insert_node(target, isFull, root);

		verify();
	}
	void insert_string(string target){
	    string cur;
        for(int i=0;i<target.size();i++){
           cur+=target[i];
           insert_value(cur, i==(int)target.size()-1);

        }
	}

	void delete_value(string target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool word_exist(string target) {
		return search(target, root)==1;
	}

    bool prefix_exist(string target) {
		return search(target, root)!=-1;
	}

	void print_inorder() {
		print_inorder(root);
	}

	void level_order_traversal() {
		if (!root)
			return;

		cout << "******************\n";
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryNode*cur = nodes_queue.front();
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
	AVLTree tree;

    tree.insert_string("abcd");
    tree.insert_string("xyz");

    cout<<tree.word_exist("abcd")<<el;//1
    cout<<tree.word_exist("ab")<<el;//0
    cout<<tree.prefix_exist("ab")<<el;//1

    tree.insert_string("ab");

    cout<<tree.word_exist("ab")<<el;
    cout<<tree.word_exist("cd")<<el;
    cout<<tree.word_exist("abcde")<<el;

}

int main() {
	test1();

	cout << "bye\n";

	return 0;
}


