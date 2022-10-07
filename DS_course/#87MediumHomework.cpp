
#include<iostream>
#include<vector>
#include<cassert>
#include<stack>
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
    //p#2 Creating print_inorder iterative
    void pirnt_inorder_iterative(){
        stack<pair<BinaryTree*, bool> > node;// boolean for printing
        node.push({this,false}); //pushing the first root node
        while(!node.empty()){
            BinaryTree *current=node.top().first;// storing the values of the top node
            bool is_done=node.top().second;
            node.pop();// deleteing the top node
            // if the top node is done which means the their children are pushed
            // and finished printing them then print this parent
            if(is_done)
                cout<<current->data<<" ";
            else{
                if(current->right)
                    node.push({current->right, false});
                node.push({current, true});
                if(current->left)
                    node.push({current->left, false});

            }
        }

    }
    //p#3 Tree_boundary
    void traverse_left_boundary(){
        cout<<data<<" ";

        if(left)
            left->traverse_left_boundary();
        else if(right)
                right->traverse_left_boundary();

    }
        int treeHeight(){
        int res=0;
        if(left)//o(n^2)
            res=left->treeHeight()+1;
        if(right)
            res=max(res,right->treeHeight()+1);
        return res;
    }
    // p#4 print diamater
//     it's simply creating to functions
//     one to print recursive to the root
//     the other one to print the other side
//     get the highest height form left
//     get the highest height from right
    void print_sub_recursive(BinaryTree *sub){
        if(!sub)
            return;
        if(sub->left&&!sub->right)
                print_sub(sub->left);
        else if(!sub->left&&sub->right)
                print_sub(sub->right);
        else if((sub->left&&sub->right)&&sub->left->treeHeight()>sub->right->treeHeight())
            print_sub(sub->left);
        else
            print_sub(sub->right);
        cout<<sub->data<<" ";


    }
        void print_sub(BinaryTree *sub){
        if(!sub)
            return;
        cout<<sub->data<<" ";
        if(sub->left&&!sub->right)
                print_sub(sub->left);
        else if(!sub->left&&sub->right)
                print_sub(sub->right);
        else if((sub->left&&sub->right)&&sub->left->treeHeight()>sub->right->treeHeight())
            print_sub(sub->left);
        else
            print_sub(sub->right);


    }
    void print_diameter(){
            if(right)print_sub_recursive(right);
            cout<<data<<" ";
            if(left) print_sub(left);

    }

    // tree diametar it's just getting height and add 1 to it from everyside
    pair<int, int> tree_diametar(){// diam&&height
        pair<int, int> res={0, 0};
        if(!left&&!right)
            return res;
        pair<int, int> left_diam={0, 0};
        pair<int, int> right_diam={0, 0};
        // this function gets the height recursively
        if(left)
            left_diam=left->tree_diametar(), res.first+=1+left_diam.second;
        if(right)
            right_diam=right->tree_diametar(), res.first+=1+right_diam.second;

        res.first=max( res.first, max(left_diam.first, right_diam.second) );
        res.second=1+max(res.second, max(left_diam.second, right_diam.second));
        return res;

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
    BinaryTree bt(1), tree(2), p3(2);
//    bt.add({2}, "R");
//    bt.add({5}, "L");
////    bt.print_inorder();
//    tree.add({3}, "L");
//    tree.add({13, 7}, "RR");
//    tree.add({13, 8}, "RL");
//    tree.print_inorder();
//    cout<<el;
//    tree.pirnt_inorder_iterative();

    p3.add({3, 5, 8, 6, 7, 15},"LLRRLR");
    p3.add({13,7}, "RR");
    p3.add({13,8}, "RL");
//    p3.print_inorder();

//   cout<< p3.tree_diametar().second;
    cout<<el;
//    p3.traverse_left_boundary();


}
