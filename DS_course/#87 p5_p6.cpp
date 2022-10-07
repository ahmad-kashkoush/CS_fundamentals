#include<iostream>
#include<vector>
#include<cassert>
#include<stack>
#define el "\n"
using namespace std;
// we can do BT using struct of node like linkedlist
class BinaryTree{
private:
    char data{};
    BinaryTree *left{}, *right{};
public:
    // My constructor
    BinaryTree(char value):data(value){}
    void print_inorder(){
        if(left)
            left->print_inorder();
        cout<<data;
        if(right)
            right->print_inorder();
    }

    // p#5 Creating a constructor that makes expression tree from postfix
    BinaryTree(string postfix){
        stack<BinaryTree *> tree;
        for(int i=0;i<(int)postfix.size();i++){
            BinaryTree *cur=new BinaryTree(postfix[i]);
            if(!isdigit(postfix[i])){// this means that we'll have at least 2 numbers stored in the stack before the operator so, dont worry
                    cur->right=tree.top();
                    tree.pop();
                    cur->left=tree.top();
                    tree.pop();
            }
            tree.push(cur);
        }

        // now I've finished creating a tree , I don't make it the (this tree), so just copy it to this
        // my tree is just the top Binarytree in the stack
        this->data=tree.top()->data;
        this->left=tree.top()->left;
        this->right=tree.top()->right;

    }
    bool is_operator(){// means not operator
        return left&&right;
    }
    // p#6 Print inorder expression with parentheses to force right precedence
    void print_inorder_expression(){
        if(left){
            if(left->is_operator())// the beginning of my subtree
                cout<<"(";
            left->print_inorder_expression();//will print number and operator
            if(left->is_operator())
                cout<<")";// the end of my subtree
        }
        cout<<data;
        if(right){
            if(right->is_operator())// doing the same done with left
                cout<<"(";
            right->print_inorder_expression();
            if(right->is_operator())
                cout<<")";

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
    BinaryTree  BT1("534*2^+");
//    BT1.print_inorder();//5+1
    BT1.print_inorder_expression();
    cout<<el;
//    p3.traverse_left_boundary();


}

