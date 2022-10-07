#include<iostream>
#include<vector>
#include<cassert>
#define el "\n"
using namespace std;
// we can do BT using struct of node like linkedlist
class BinaryTree{
private:
    int data{};
    BinaryTree *left{}, *right{};
public:

    // My constructor
    BinaryTree(int value):data(value){
    }
    void print_inorder(){
        if(left)
            left->print_inorder();
        cout<<data<<" ";
        if(right)
            right->print_inorder();
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

    int tree_max(){
       int mx=data;
       if(left)
            mx=max(mx,left->tree_max());
       if(right)
            mx=max(mx,right-> tree_max());
       return mx;

    }
};
int main(){
    BinaryTree bt(1), tree(2);
    bt.add({2}, "R");
    bt.add({5}, "L");
//    bt.print_inorder();
    tree.add({3}, "L");
    tree.add({13, 7}, "RR");
    tree.add({13, 8}, "RL");
//    tree.print_inorder();
    cout<<tree.tree_max()<<" "<<bt.tree_max();

}

