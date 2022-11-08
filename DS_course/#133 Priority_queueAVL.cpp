#include <iostream>
#include <cassert>
#include <queue>
using namespace std;


class PriorityQueue {
private:
	struct BinaryNode {
		int priority { };
		vector<int> taskId;
		int height { };
		BinaryNode* left { };
		BinaryNode* right { };

		BinaryNode(int  task, int priority) :
				priority(priority) {
				    taskId.push_back(task);
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

		if (target == node->priority)
			return true;

		if (target < node->priority)
			return search(target, node->left);

		return search(target, node->right);
	}

	BinaryNode* right_rotation(BinaryNode* Q) {
		cout << "right_rotation " << Q->priority << "\n";
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) {
		cout << "left_rotation " << P->priority << "\n";
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

	BinaryNode* insert_node(int task, int priority,BinaryNode* node) {
		if (priority < node->priority) {
			if (!node->left)
				node->left = new BinaryNode(task, priority);
			else	// change left. update left as it might be balanced
				node->left = insert_node(task,priority, node->left);
		} else if (priority > node->priority) {
			if (!node->right)
				node->right = new BinaryNode(task, priority);
			else
				node->right = insert_node(task,priority, node->right);
		}else
                node->taskId.push_back(task);

		node->update_height();
		return balance(node);
	}

	BinaryNode* min_node(BinaryNode* cur) {
		while (cur && cur->left)
			cur = cur->left;
		return cur;
	}
	BinaryNode *max_node(BinaryNode *cur){
        while(cur&&cur->right)
            cur=cur->right;
        return cur;
	}

	BinaryNode* delete_node(int target, BinaryNode* node) {
		if (!node)
			return nullptr;

		if (target < node->priority)
			node->left = delete_node(target, node->left);
		else if (target > node->priority)
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
				node->priority = mn->priority;	// copy & go delete
				node->right = delete_node(node->priority, node->right);
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
		bool left_bst = !node->left || node->priority > node->left->priority && is_bst(node->left);

		if (!left_bst)
			return false;

		bool right_bst = !node->right || node->priority < node->right->priority && is_bst(node->right);
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
		cout << node->priority << " ";
		print_inorder(node->right);
	}


public:
	void enqueue(int task,int priority) {
		if (!root)
			root = new BinaryNode(task, priority);
		else
			root = insert_node(task, priority, root);

		verify();
	}

	int dequeue() {
        assert(!isempty());

        BinaryNode *mx=max_node(root);
        int ret=mx->taskId.back();
        if(mx->taskId.size()==1)
                root=delete_node(mx->priority, root);
        else
            mx->taskId.pop_back();
        return ret;
	}

	bool search(int target) {
		return search(target, root);
	}
    bool isempty(){
        return root==nullptr;
    }


};


void test1(){
    	PriorityQueue tasks;

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);
	tasks.enqueue(7761, 7);

	cout << tasks.dequeue() << "\n";	// 7761
	cout << tasks.dequeue() << "\n";	// 3161

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);

	// 3145 3845 3111 2815 2211 1535 1131
	while (!tasks.isempty())
		cout << tasks.dequeue() << " "<<flush;
}
int main() {
    test1();

	cout << "bye\n";

	return 0;
}
