
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

    // doc way
    void print_level_order(){
        queue<BinaryTree*> nodes;
        nodes.push(this);
        int level=0;
        while(!nodes.empty()){
            int sz=nodes.size();
            cout<<"level "<< level<<": ";
            while(sz--){
                BinaryTree *tmp=nodes.front();
                if(tmp->left)
                    nodes.push(tmp->left);
                if(tmp->right)
                    nodes.push(tmp->right);
                cout<<nodes.front()->data<<" ";
                nodes.pop();
            }
            level++;
            cout<<el;

        }
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
      BT4.add({4, 8}, "LL");
      BT4.add({3, 6}, "RL");
      BT4.add({3, 5}, "RR");
      BT4.print_level_order();
//    cout<<el;
//    p3.traverse_left_boundary();


}

