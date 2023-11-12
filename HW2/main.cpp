// red-black tree
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class RBTree{
    public:
    struct node
    {
        int value=0;
        bool side=0;
        node *left=NULL;
        node *right=NULL;
        node *parent=NULL;
        bool color = 1; // 1 for red, 0 for black
    };
    
    node *root;
    int rotationCount=0;
    enum side{left=bool(0), right=bool(1)};
    
    RBTree()
    {
        root=NULL;
    }
    
    node* insert(int key);
    node* search(int key, bool first=1);
    bool twoRedKids(node *temp);
    void changeColor(node *temp);
    void changeAllColor(node *root);
    bool consequentRed(node *root);
    node* rotate(node *mid);
    void setKid(node *parent, node *kid, bool side);
    
};



void postorderTraversal(RBTree::node *root, string &result) {
    if (root) {
        postorderTraversal(root->left, result);
        postorderTraversal(root->right, result);
        if(root->color==0) result += to_string(root->value);
        // result += to_string(root->value);
        // result += " ";
    }
}

void preorderTraversal(RBTree::node *root, string &result) {
    if (root) {
        if(root->color==1) result += to_string(root->value);
        // result += to_string(root->value);
        // result += " ";
        preorderTraversal(root->left, result);
        preorderTraversal(root->right, result);
    }
}

void inorderTraversal(RBTree::node *root, string &result) {
    if (root) {
        inorderTraversal(root->left, result);
        if(root->color==0) result += to_string(root->value);
        // result += to_string(root->value);
        // result += " ";
        inorderTraversal(root->right, result);
    }
}


int main()
{
    string input="";
    RBTree *tree=new RBTree;
    getline(cin, input);
    stringstream ss(input);
    
    for(string data; ss>>data;)
    {
        // cout<<data<<endl;
        int value=0;
        if(data[0]>='0' && data[0]<='9') value=atoi(data.c_str());
        else { if(data[0]==26) break; 
                else value=data[0];}
        // cout<<value<<endl;
        if(tree->root==nullptr)
        {
            tree->root=new RBTree::node;
            tree->root->value=value;
            tree->root->color=0;
        }
        else tree->insert(value);
    }
    
    // cout<<"----------------------------------------"<<endl;
    string result="";
    postorderTraversal(tree->root, result);
    result+="_";
    preorderTraversal(tree->root, result);
    result+="_";
    result+=to_string(tree->rotationCount);
    cout<<result<<endl;
    return 0;
    
}

RBTree::node* RBTree::insert(int value)
{
    node* searchResult=RBTree::search(value);
    // cout<<"search done"<<endl;
    if(searchResult->value==value) return NULL;
    node *newnode=new node;
    newnode->value=value;
    if(value<searchResult->value) RBTree::setKid(searchResult, newnode, RBTree::side::left);
    else RBTree::setKid(searchResult, newnode, RBTree::side::right);
    RBTree::search(value, false);
    if(RBTree::root->color==1) RBTree::root->color=0;
}

RBTree::node* RBTree::search(int key, bool first)
{
    node *temp=root;
    while(temp!=NULL)
    {
        node *nextnode=NULL;
        if(consequentRed(temp)){
            RBTree::rotate(temp);
            return RBTree::search(key, false);
        }
        if(first && RBTree::twoRedKids(temp)){
            RBTree::changeAllColor(temp);
            return RBTree::search(key, first);
        }
        if(temp->value == key) return temp;
        else if(temp->value > key) nextnode = temp->left;
        else nextnode = temp->right;
        
        if(nextnode==NULL) return temp;
        else temp=nextnode;
    }
    return NULL;
}

bool RBTree::twoRedKids(node *temp)
{
    if(temp->left!=NULL && temp->right!=NULL)
    {
        if(temp->left->color==1 && temp->right->color==1) return true;
    }
    return false;
}

void RBTree::changeColor(node *temp)
{
    if(temp->color==0) temp->color=1;
    else temp->color=0;
}

void RBTree::changeAllColor(node *root)
{
    if(root->left!=NULL) RBTree::changeColor(root->left);
    if(root->right!=NULL) RBTree::changeColor(root->right);
    RBTree::changeColor(root);
}

bool RBTree::consequentRed(node *root)
{
    if(root->color==0) return false;
    if(root->left!=NULL)
    {
        if(root->left->color==1){
            // cout<<"consequentRed"<<endl;
            return true;
        } 
    }
    if(root->right!=NULL)
    {
        if(root->right->color==1) {
            // cout<<"consequentRed"<<endl;
            return true;
        } 
    }
    return false;
}

RBTree::node* RBTree::rotate(node* mid)
{
    if(mid->side==0)
    {
        //LL
        if(mid->left && mid->left->color==1)
        {
            // cout<<"LL: "<<mid->value<<endl;
            node* up=mid->parent;
            node* down=mid->left;
            RBTree::setKid(up, mid->right, RBTree::side::left);
            RBTree::setKid(up->parent, mid, up->side);
            RBTree::setKid(mid, up, RBTree::side::right);
            mid->color=0;
            if(mid->left!=NULL)
                mid->left->color=1;
            if(mid->right!=NULL)
                mid->right->color=1;
        }
        //LR
        else
        {
            // cout<<"LR: "<<mid->value<<endl;
            RBTree::node* up=mid->parent;
            RBTree::node* down=mid->right;
            RBTree::setKid(mid, down->left, RBTree::side::right);
            RBTree::setKid(up, down->right, RBTree::side::left);
            RBTree::setKid(up->parent, down, up->side);
            RBTree::setKid(down, mid, RBTree::side::left);
            RBTree::setKid(down, up, RBTree::side::right);
            down->color=0;
            if(down->left!=NULL)
                down->left->color=1;
            if(down->right!=NULL)
                down->right->color=1;
        }
    }
    else if(mid->side==1)
    {
        //RL
        if(mid->left && mid->left->color==1)
        {
            // cout<<"RL: "<<mid->value<<endl;
            RBTree::node* up=mid->parent;
            RBTree::node* down=mid->left;
            RBTree::setKid(mid, down->right, RBTree::side::left);
            RBTree::setKid(up, down->left, RBTree::side::right);
            RBTree::setKid(up->parent, down, up->side);
            RBTree::setKid(down, mid, RBTree::side::right);
            RBTree::setKid(down, up, RBTree::side::left);
            down->color=0;
            if(down->left!=NULL)
                down->left->color=1;
            if(down->right!=NULL)
                down->right->color=1;
        }
        //RR
        else
        {
            // cout<<"RR: "<<mid->value<<endl;
            node* up=mid->parent;
            node* down=mid->right;
            RBTree::setKid(up, mid->left, RBTree::side::right);
            RBTree::setKid(up->parent, mid, up->side);
            RBTree::setKid(mid, up, RBTree::side::left);
            mid->color=0;
            // cout<<"mid->left: "<<mid->left->value<<endl;
            if(mid->left!=NULL)
                mid->left->color=1;
            // cout<<"mid->right: "<<mid->right->value<<endl;
            if(mid->right!=NULL)
                mid->right->color=1;
        }
    }
    this->rotationCount++;
    return mid;
}

void RBTree::setKid(node *parent, node *kid, bool side)
{
    if(side==0)
    {
        if(parent!=NULL)
            parent->left=kid;
        else this->root=kid;
        if(kid!=NULL){
            kid->parent=parent;
            kid->side=0;
        }
    }
    else
    {
        if(parent!=NULL)
            parent->right=kid;
        else this->root=kid;
        if(kid!=NULL){
            kid->parent=parent;
            kid->side=1;
        }
    }
}