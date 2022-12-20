// p1, p2, p3
#include<iostream>
#include<vector>
#include<cassert>
#include<stack>
#include<queue>
#define el "\n"
using namespace std;
// we can do BT using struct of node like linkedlist
class BinaryTree{
private:
    int data{};
    BinaryTree *left{}, *right{};
public:
    // My constructor
    BinaryTree(int value):data(value){}
    void print_inorder(){
        if(left)
            left->print_inorder();
        cout<<data<<" ";
        if(right)
            right->print_inorder();
    }
        int treeHeight(){
        int l=0;
        if(left)//o(n^2)
            l=left->treeHeight()+1;
        if(right)
            l=max(l,right->treeHeight()+1);
        return l;
    }

    void print_nodes_by_level(int level){
        if(level==0)
            cout<<data<<" ";
        else if(level){
           if(left) left->print_nodes_by_level(level-1);
           if(right) right->print_nodes_by_level(level-1);
        }


    }
    void print_nodes_by_level_reversed(int level){
        if(level==0)
            cout<<data<<" ";
        else if(level){
           if(right) right->print_nodes_by_level(level-1);
           if(left) left->print_nodes_by_level(level-1);
        }


    }
    void print_nodes_by_level_spiral(){
        int h=treeHeight();
        for(int level=0;level<=h;level++){
            if(level&1)print_nodes_by_level_reversed(level);
            else       print_nodes_by_level(level);
            cout<<el;
        }
    }
    void print_level_order_recursive(){
        int h= treeHeight();
        for(int level=0;level<=h;level++){
            print_nodes_by_level(level);
            cout<<"\n";

        }
    }
        // doc way
        void print_level_order_spiral_doc(){
        deque<BinaryTree*> nodes;
        nodes.push_back(this);
        int level=0;
        while(!nodes.empty()){
            int sz=nodes.size();
            cout<<"level "<< level<<": ";
            if((level&1)==0){
                    while(sz--){
                        BinaryTree *tmp=nodes.back();
                        nodes.pop_back();
                        if(tmp->right)
                            nodes.push_front(tmp->right);
                        if(tmp->left)
                            nodes.push_front(tmp->left);
                        cout<<tmp->data<<" ";

                }
            }
           else{
                while(sz--){
                    BinaryTree *tmp=nodes.front();
                    if(tmp->left)
                        nodes.push_back(tmp->left);
                    if(tmp->right)
                        nodes.push_back(tmp->right);
                    cout<<nodes.front()->data<<" ";
                    nodes.pop_front();
                }
           }

            level++;
            cout<<el;

        }
    }
    // p#3 check complete tree in a recursive way
        int countNodes(int level){
        int res=1;
        if(level==0)
            return res;
        if(left)
            res+=left->countNodes(level-1);
        if(right)
            res+=right->countNodes(level-1);
        return res;


    }
        bool last_level_check(int level){
            bool ans= true;
            if(level==1)
                return !(right&&!left);
            else if (level){
                if(left) left->last_level_check(level-1);
                if(right)right->last_level_check(level-1);
            }


        }
        bool isComplete(){
        int h= treeHeight();
        if( !( ( (1<<h)-1 ) == countNodes(h-1) ) )
            return false;
        return last_level_check(h);
    }
    // p#3 check if complete iterative way
        bool isCompleteIterative(){
        queue<BinaryTree*> nodes;
        nodes.push(this);
        int level=0;
        int h=treeHeight();
        while(!nodes.empty()){
            int sz=nodes.size();
            bool last_level= (level==h);
            if(nodes.size()!=(1<<level) ){
                if(!last_level)
                    return false;
            }
            while(sz--){
                BinaryTree *tmp=nodes.front();
                if(tmp->left)
                    nodes.push(tmp->left);
                if(tmp->right)
                    nodes.push(tmp->right);
                if(tmp->right&&!tmp->left)
                    return false;

                nodes.pop();
            }
            level++;


        }
        return true;
    }
     bool isCompleteIterativeDoc(){
        queue<BinaryTree*> nodes;
        nodes.push(this);

        bool notAllowed=false;// not allowed to have children


        while(!nodes.empty()){
            int sz=nodes.size();
            while(sz--){
                BinaryTree *tmp=nodes.front();
                nodes.pop();

                if(tmp->left){
                    if(notAllowed)
                        return false;
                    nodes.push(tmp->left);
                }else notAllowed=true;

                if(tmp->right){
                    if(notAllowed)
                        return false;
                    nodes.push(tmp->right);
                }

            }
//            cout<<el;
        }
        return true;
//        cout<<el;
    }
	bool is_complete() {
		queue<BinaryTree*> nodes_queue;
		nodes_queue.push(this);

		// Once there is a single missing node (left before right)
		// Nothing else should be there: on this level or next level
		bool no_more_allowed = false;


		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			while (sz--) {
				BinaryTree*cur = nodes_queue.front();
				nodes_queue.pop();

				if (cur->left) {
					if (no_more_allowed)
						return false;
					nodes_queue.push(cur->left);
				} else
					no_more_allowed = true;

				if (cur->right) {
					if (no_more_allowed)
						return false;
					nodes_queue.push(cur->right);
				} else
					no_more_allowed = true;
			}
		}
		return true;

	}


    void add(vector<int> value, string direction){
        assert(value.size()==direction.size());
        BinaryTree *current=this;
        for(int i=0;i<value.size();++i){
            if(direction[i]=='L'){
                if(!current->left)
                    current->left=new BinaryTree(value[i]);
                else
                    assert(current->left->data==value[i]);
                current=current->left;
            }else{
                if(!current->right)
                    current->right=new BinaryTree(value[i]);
                else
                    assert(current->right->data==value[i]);
                current=current->right;
            }
        }
    }
    // p#1 creating destructor
    void Clear(){
        if(left){
            delete left;// this will delete the whole left recursively
            left=nullptr;
        }
        if(right){
            delete right;
            right=nullptr;
        }
    }
    ~BinaryTree(){
        Clear();
    }


};

int main(){
    BinaryTree bt(1), tree(2), p3(2), BT4(2);

//    p3.add({3, 5, 8, 6, 7, 15},"LLRRLR");
//    p3.add({13,7}, "RR");
//    p3.add({13,8}, "RL");
//    p3.print_level_order();
/*
        2
       / \
      4   3
     /   / \
    8   5   6

*/

      BT4.add({4, 8}, "LL");
//      BT4.add({3, 6}, "RR");
      BT4.add({3, 5}, "RL");
//      BT4.print_level_order_recursive();
    cout<<"BT1"<<el;
    bt.add({2, 6}, "LL");
    bt.add({2, 4}, "LR");
    bt.add({3}, "R");
    bt.print_level_order_recursive();
    cout<<bt.isComplete()<<el;

     cout<< BT4.is_complete();
//    cout<<el;
//    p3.traverse_left_boundary();


}


