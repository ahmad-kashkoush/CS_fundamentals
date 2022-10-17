#include<iostream>
#include<vector>
#include<cassert>
#include<stack>
#include<queue>
#include<deque>
#include<string>
#include<cstring>
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
    bool is_mirror(BinaryTree *first, BinaryTree *second){
        if(!first&&!second)
            return true;

        if(!first&&second||!second&&first||first->data!=second->data)
            return false;
        return is_mirror(first->left,second->right)&&is_mirror(first->right, second->left);
    }
    bool is_symmetric(){
        return is_mirror(left, right);
    }
      void print_preorder_complete(){
        cout<<data<<" ";
        if(left)
            left->print_preorder_complete();
        else
            cout<<-1<<" ";
        if(right)
            right->print_preorder_complete();
        else    cout<<-1<<" ";
    }
    bool flip_tree(BinaryTree)
    BinaryTree(deque<int> &pre, deque<int> &in, int l=0, int r=-1){
        if(r==-1)
            r=(int)in.size()-1;
        data=pre[0];
        pre.pop_front();
        for(int split=l;split<=r;split++){
            if(in[split]==data){
                if(split>l)left=new BinaryTree(pre, in, l, split-1);
                if(split<r)right=new BinaryTree(pre,in, split+1, r);
                break;
            }
        }


    }
    BinaryTree(queue<pair<int, bool>> &q){
        if(q.empty())
            return;
        data=q.front().first;
        bool leaf=q.front().second;
        q.pop();
        if(!leaf){
            left= new BinaryTree(q);
          //  q.pop();// don't delete because it will be deleted from line 44
            right= new BinaryTree(q);
//            q.pop();
        }
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

int main(){
    deque<int>d1={1, 2, 4, 7, 8, 5, 9, 3, 6, 10};
    deque<int>d2={7, 4, 8, 2, 5, 9, 1, 3, 10, 6};
    queue<pair<int, bool>> q;
    q.emplace(1, 0);
    q.emplace(2, 1);
    q.emplace(3, 1);
    BinaryTree test1(d1, d2);
    BinaryTree test2(q);
    BinaryTree mirrorTree(1);
    mirrorTree.add({2, 3, 5},"LLL");
    mirrorTree.add({2, 4, 7}, "LRL");
    mirrorTree.add({2, 4, 8},"LRR");
    mirrorTree.add({2, 4, 8},"RLL");
    mirrorTree.add({2, 4, 7}, "RLR");
    mirrorTree.add({2, 3, 6},"RRL");
    mirrorTree.add({2, 3, 5},"RRR");
//    test1.print_preorder_complete();
    cout<<el;
//    cout<<test1.parenthsize();
    mirrorTree.print_inorder();
    cout<<el;
//    mirrorTree.print_preorder_complete();
    if(mirrorTree.is_symmetric()){
        cout<<"YES";
    }else
        cout<<"NO";




}


