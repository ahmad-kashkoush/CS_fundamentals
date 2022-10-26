//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
// in this file i'll call it a binary tree but my operations will BST
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
    void Insert(int value){
        if(value<data){
            if(!left)
                left= new BinaryTree(value);
            else left->Insert(value);

        }else if(value>data){
            if(!right)
                right= new BinaryTree(value);
            else right->Insert(value);
        }
        // else will be found so don't create
        // in this tree we're creating set
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
    // string tree caninosilizing --> means to print your tree with (data(leftdata)(rightdata)) if null print ();
    string parenthsize(){
        string repr='('+to_string(data);
        vector<string> v;
        if(left)
            v.push_back(left->parenthsize());
        else v.push_back("()");
        if(right)
            v.push_back(right->parenthsize());
        else v.push_back("()");

        for(int i=0;i<v.size();i++)
            repr+=v[i];
        repr+=')';
        return repr;

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
// A binary search tree is a tree which it's inorder representation is sorted


int main(){
    BinaryTree test1(50);
    test1.Insert(45);// should automaticly on the left
    test1.Insert(60);
    test1.Insert(55);
    test1.print_level_order();
    test1.print_inorder();


}

