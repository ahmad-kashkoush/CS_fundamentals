//والله يابني مانا عارف ادينا بنهبد
//كود بلا هدف, تكبييييير
// Problem Link -->
#include<bits/stdc++.h>
#define el '\n'
#define ll long long
#define all(s)  s.begin(), s.end()
using namespace std;
class BinarySearchTree{
private:
    struct BinaryNode{
         int data{ };
         BinaryNode* left { };
         BinaryNode* right { };

         BinaryNode(int data) : data(data){}
    };
    BinaryNode *root{ };


    // utilities
    BinaryNode *minNode(BinaryNode *cur){
        BinaryNode *node=cur;
        while(node&&node->left)
            node=node->left;
        return node;
    }
    void specialDelete(BinaryNode *node,BinaryNode *child){
        node->data=child->data;
        node->left=child->left;
        node->right=child->right;
        delete child;
    }

    BinaryNode *deleteNode(int target, BinaryNode *node){
            if(!node)
                return nullptr;

            if(target<node->data)
                node->left=deleteNode(target, node->left);
            else if(target>node->data)
                node->right=deleteNode(target, node->right);
            else{
                    if(!node->right&&!node->left){
                        delete node;
                        node=nullptr;
                    }
                    else if(!node->left)
                         specialDelete(node, node->right);
                    else if(!node->right)
                        specialDelete(node, node->left);
                    else{
                        BinaryNode *mn=minNode(node->right);
                        node->data=mn->data;

                        node=deleteNode(node->data, node->right);
                    }
            }
            return node;

    }
public:
    BinarySearchTree(int target):root(new BinaryNode(target)){}
    void insertValue(int target){
        if(!root)
            root= new BinaryNode(target);
        BinaryNode *cur= root;

        while(cur){
            if(target<cur->data){
                if(!cur->left){
                    cur->left= new BinaryNode(target);
                    break;
                }else
                    cur=cur->left;

            }else if(target>cur->data){
                if(!cur->right){
                    cur->right= new BinaryNode(target);
                    break;
                }else
                    cur=cur->right;
            }

        }
    }
    void deleteValue(int target){
        if(target==root->data&&!root->left&&!root->right)
            return;
        deleteNode(target, root);
    }

    bool Search(int target){
        BinaryNode *cur=root;
        while(cur){
            if(cur->data==target)
                return true;
            if(cur->data<target)
                cur=cur->left;
            else
                cur=cur->right;
        }
        return false;
    }
    void print_inorder(BinaryNode *cur){
        if(!cur)
            return;
        print_inorder(cur->left);
        cout<<cur->data<<" ";
        print_inorder(cur->right);
    }
    void print_inorder(){
         print_inorder(root)  ;

    }
    void level_order(){
         queue<BinaryNode *> nodes;
         BinaryNode *cur=root;
         nodes.push(cur);
         int level=0;
         while(!nodes.empty()){
                int sz = nodes.size();
                cout<<"level "<<level<<" : ";
                while(sz--){
                   BinaryNode *tmp=nodes.front();
                   nodes.pop();
                   cout<<tmp->data<<" ";
                   if(tmp->left)
                        nodes.push(tmp->left);
                   if(tmp->right)
                        nodes.push(tmp->right);

                }
                level++;
                cout<<el;


         }



    }
};
BinarySearchTree* GetTree1() {
	BinarySearchTree* tree = new BinarySearchTree(50);
	tree->insertValue(20);
	tree->insertValue(60);
	tree->insertValue(15);
	tree->insertValue(45);
	tree->insertValue(70);
	tree->insertValue(35);
	tree->insertValue(73);

	tree->insertValue(14);
	tree->insertValue(16);
	tree->insertValue(36);
	tree->insertValue(58);
	return tree;
}

BinarySearchTree* GetTree2() {
	BinarySearchTree* tree = new BinarySearchTree(10);
	tree->insertValue(5);
	return tree;
}

void test1() {
	BinarySearchTree* tree = GetTree2();

	tree->deleteValue(10);
	tree->insertValue(7);
	tree->insertValue(15);
}
void test3(){
    BinarySearchTree *tree= GetTree1();
    tree->deleteValue(14);
	// this removed = RTE
	tree->print_inorder();
}

int main() {
    test3();
    return 0;


}










