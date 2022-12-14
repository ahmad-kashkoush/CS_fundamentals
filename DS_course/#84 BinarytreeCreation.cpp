//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;

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
    BinaryTree bt(1), tree(2);
    bt.add({2}, "R");
    bt.add({5}, "L");
//    bt.print_inorder();
    tree.add({3}, "L");
    tree.add({13, 7}, "RR");
    tree.add({13, 8}, "RL");
    tree.print_inorder();


}
