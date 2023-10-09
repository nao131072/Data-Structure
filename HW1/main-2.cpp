#include <iostream>
#include <string>

using namespace std;

// 定义二叉树节点结构
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

struct queueNode{
    TreeNode* data;
    queueNode* next;
    queueNode(TreeNode* val):data(val),next(nullptr){}
};

void pushQueue(queueNode* head, TreeNode* val)
{
    queueNode* temp=head;
    while(temp->next) temp=temp->next;
    temp->next=new queueNode(val);
}

TreeNode* buildTree(string infix, string traversal, string traversalOrder) {
    if(infix.empty()) 
        return nullptr;
    char rootVal;
    if(traversal=="prefix") rootVal=traversalOrder[0];
    else rootVal=traversalOrder[traversalOrder.size()-1];
    
    int rootIndex=infix.find(rootVal);
    TreeNode* root=new TreeNode(rootVal);
    
    string leftInfix=infix.substr(0,rootIndex);
    string rightInfix=infix.substr(rootIndex+1);
    int leftSize=leftInfix.size();
    int rightSize=rightInfix.size();
    
    string leftTraversalOrder;
    string rightTraversalOrder;
    if(traversal=="prefix"){
        leftTraversalOrder=traversalOrder.substr(1,leftSize);
        rightTraversalOrder=traversalOrder.substr(leftSize+1);
    }
    else {
        leftTraversalOrder=traversalOrder.substr(0,leftSize);
        rightTraversalOrder=traversalOrder.substr(leftSize,rightSize);
    }
    
    // cout<<"rootVal:"<<rootVal<<endl;
    // cout<<"leftInfix:"<<leftInfix<<endl;
    // cout<<"rightInfix:"<<rightInfix<<endl;
    // cout<<"leftTraversalOrder:"<<leftTraversalOrder<<endl;
    // cout<<"rightTraversalOrder:"<<rightTraversalOrder<<endl;
    // cout<<endl;
    
    root->left=buildTree(leftInfix,traversal,leftTraversalOrder);
    root->right=buildTree(rightInfix,traversal,rightTraversalOrder);
    
    return root;
        
}

// 后序遍历并输出结果
void postorderTraversal(TreeNode* root, string& result) {
    if (root) {
        postorderTraversal(root->left, result);
        postorderTraversal(root->right, result);
        result += root->data;
    }
}

void preorderTraversal(TreeNode* root, string& result) {
    if (root) {
        result += root->data;
        preorderTraversal(root->left, result);
        preorderTraversal(root->right, result);
    }
}

// 层序遍历并输出结果
void levelOrderTraversal(TreeNode* root, string& result) {
    queueNode* head=new queueNode(root);
    int tempCount=0;
    
    while(head)
    {
        result+=root->data;
        if(root->left) pushQueue(head, root->left);
        if(root->right) pushQueue(head, root->right);
        
        if(!head->next) break;
        root=head->next->data;
        head=head->next;
    }
}

int main() {
    string infix, traversal, traversalOrder, newTraversal;
    cin >> infix >> traversal >> traversalOrder >> newTraversal;

    TreeNode* root = buildTree(infix, traversal, traversalOrder);
    // cout<<"traversal:" <<traversal<<endl;
    string newTraversalResult = "";
    if(newTraversal=="prefix") preorderTraversal(root, newTraversalResult);
    else if(newTraversal=="postfix") postorderTraversal(root, newTraversalResult);
    cout << newTraversalResult << endl;
    
    string levelOrderResult = "";
    levelOrderTraversal(root, levelOrderResult);
    cout << levelOrderResult << endl;

    return 0;
}