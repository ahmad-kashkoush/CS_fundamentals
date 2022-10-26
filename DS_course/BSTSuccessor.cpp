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
	BinarySearchTree* parent{ };
	// find chain function--> just a function to push the way between the value and root;
	bool findChain(vector<BinarySearchTree*> &ansectors, int target){
        ansectors.push_back(this);

        if(target==data)
            return true;

        if(target<data)
            return left&&left->findChain(ansectors, target);
        return right&&right->findChain(ansectors, target);


	}
	BinarySearchTree *Find(int target){
        if(target==data)
            return this;
       if(target<data){
            if(!left)
                return nullptr;
            return left->Find(target);

       }
       if(!right)
            return nullptr;
       return right->Find(target);


	}

public:

	BinarySearchTree(int data, BinarySearchTree *parent=nullptr) :
			data(data), parent(parent) {
	}

	void print_inorder() {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
	////////////////////////////////////////////

	int min_value(){
        BinarySearchTree *node=this;
        while(node&&node->left)
            node=node->left;
        return node->data;
	}

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
	void insert_parent(int target){
	    if(target<data){
            if(!left){
                left= new BinarySearchTree(target, this);
//                left->parent=this;
            }
            else left->insert_parent(target);
	    }else if(target>data){
            if(!right){
                right= new BinarySearchTree(target, this);
//                right->parent=this;
            }else   right->insert_parent(target);
	    }
	}

	bool search(int target) {	// tail recursion
		if (target == data)
			return true;

		if (target < data)
			return left && left->search(target);

		return right && right->search(target);
	}
    // p#2 Queries of successors
    void successor_queries(deque<int> &queries, vector<int> &answer, vector<int> &traversal){
                    if(queries.empty())
                        return;

                    if(left && queries.front()<data){
                        left->successor_queries(queries, answer, traversal);
                        queries.pop_front();
                        if(queries.empty())
                            return;
                    }

                    if(!traversal.empty()&& queries.front()==traversal.back()){
                        answer.push_back(data);
                        queries.pop_front();
                        if(queries.empty())
                            return;
                    }

                    traversal.push_back(data);

                    if(right && queries.front()>=data)
                        right->successor_queries(queries, answer, traversal);
    }

	///////////////////////////////////////////////////
	// get_next a function that return a node and make the back of ansector vector be it's parent
	BinarySearchTree *get_next(vector<BinarySearchTree *> &ansectors){
            if(ansectors.size()==0)
                return nullptr;
            BinarySearchTree *node=ansectors.back();
            ansectors.pop_back();
            return node;
	}
    // successor code
    pair<bool, int> successor(int target){
        vector<BinarySearchTree *> ansectors;
        // in this condition i've checked if there's a node and filled my ansectors vector in case found
        if(!findChain(ansectors, target))
            return {false, -1};

        BinarySearchTree* child=get_next(ansectors);
        if(child&&child->right)
            return {true, child->right->min_value()};

        BinarySearchTree* parent=get_next(ansectors);

        while(parent&&parent->right==child)
            child=parent, parent=get_next(ansectors);
        if(parent)
            return {true, parent->data};
        return {false, -1};


    }
    pair<bool, int> successor_parent(int target){
            BinarySearchTree *child=Find(target);

            if(!child)
                return {false, -1};

            if(child && child->right)
                return {true, child->right->min_value()};

            BinarySearchTree *Parent=child->parent;

            while(Parent && Parent->right==child)
                child=Parent, Parent=Parent->parent;
            if(Parent)
                return make_pair(true, parent->data);
            return make_pair(false, -1);
    }


};

int main() {
	BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	//tree.print_inorder();
	vector<int> v { 15, 20, 35, 45, 50, 60, 70, 73, 100 };

	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
		pair<bool, int> p = tree.successor_parent(v[i]);

		if (p.first)
			cout << p.second << "\n";
		else
			cout << "NA\n";

	}

	cout << "bye\n";

	return 0;
}
