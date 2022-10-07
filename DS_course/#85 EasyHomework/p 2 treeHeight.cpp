#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>
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
    //p#2
    int treeHeight(){
        int l=0;
        if(left)//o(n^2)
            l=left->treeHeight()+1;
        if(right)
            l=max(l,right->treeHeight()+1);
        return l;
    }
    int countNodes(){
        int res=1;
        if(left)
            res+=left->countNodes();
        if(right)
            res+=right->countNodes();
        return res;


    }
    int countLeafes(){
        int res=!left&&!right;// this way I'll increment only if leaf
        if(left)
            res+=left->countLeafes();
        if(right)
            res+=right->countLeafes();
        return res;

    }
    bool is_exist(int value){
        bool ans=data==value;
        if(left&&!ans)
            ans= left->is_exist(value);

        if(right&&!ans)
            ans= right->is_exist(value);

        return ans;

    }
    bool isPerfectTree(){
        int height=this->treeHeight();
        return(pow(2, height+1)-1==countNodes());
    }
    bool isPerfectTreeRecursive(int h=-1){
        if(h==-1)
            h=treeHeight();
        if(!left&&!right)// to the last level(leaves)
            return h==0;

        if(left&&!right||right&&!left)// to the rest of levels
            return false;


        return left->isPerfectTreeRecursive(h-1)&&
               right->isPerfectTreeRecursive(h-1);

    }
};
int main(){
    BinaryTree bt(1), tree(2);
    bt.add({2}, "R");
    bt.add({5}, "L");
//    cout<<bt.treeHeight();
    tree.add({3}, "L");
    tree.add({13, 7}, "RR");
    tree.add({13, 8}, "RL");
//    cout<<tree.treeHeight();
    cout<<(tree.is_exist(7)?"True":"False")<<el;
    cout<<(tree.isPerfectTreeRecursive()?"True":"False");


}

