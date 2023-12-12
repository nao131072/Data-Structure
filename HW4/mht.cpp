#include <iostream>
#include <string>
using namespace std;

template<class T>
void push_back(T* &arr, int &size, T data){
    T* temp=new T[size+1];
    for(int i=0;i<size;i++) temp[i]=arr[i];
    temp[size]=data;
    delete[] arr;
    arr=temp;
    size++;
}

class Tree{
public:
    struct node{
        int data=0;
        int childAmount=0;
        node** children=new node*[0];
    };
    
    node* root=nullptr;
    int height=0;
    
    Tree(int data=0){
        root=new node;
        root->data=data;
        height=1;
    }
    
    int calHeight(node* root){
        if(root==nullptr) return 0;
        int max=0;
        for(int i=0;i<root->childAmount;i++){
            int temp=calHeight(root->children[i]);
            if(temp>max) max=temp;
        }
        return max+1;
    }
    
    node* search(int data, node* root){
        if(root==nullptr) return nullptr;
        if(root->data==data) return root;
        // cout<<"root: "<<root->data<<endl;
        for(int i=0;i<root->childAmount;i++){
            node* temp=search(data, root->children[i]);
            if(temp!=nullptr) return temp;
        }
        return nullptr;
    }
    
    int insert(int data, int parentData){
        node* temp=search(parentData, root);
        if(temp==nullptr) return -1;
        if(search(data, root)!=nullptr) return -2;
        node* newNode=new node;
        newNode->data=data;
        push_back(temp->children, temp->childAmount, newNode);
        height=calHeight(root);
        // cout<<"root: "<<root->data<<" height: "<<height<<endl;
        // cout<<"insert "<<data<<" to "<<parentData<<endl;
        // cout<<"childAmount: "<<temp->childAmount<<endl;
        return 0;
    }
};

int checkExist(int *arr, int size, int data){
    for(int i=0;i<size;i++)
        if(arr[i]==data) return i;
        else if(arr[i]==-1) return i;
}

int main()
{
    int nodeAmount=0;
    cin>>nodeAmount;
    int *nodes=new int[nodeAmount];
    for(int i=0;i<nodeAmount;i++) nodes[i]=-1;
    
    int nodeData1=0, nodeData2=0;
    int edgeAmount=0;
    int* edges=new int[0];
    while(cin>>nodeData1>>nodeData2){
        push_back(edges, edgeAmount, nodeData1);
        push_back(edges, edgeAmount, nodeData2);
        nodes[checkExist(nodes, nodeAmount, nodeData1)]=nodeData1;
        nodes[checkExist(nodes, nodeAmount, nodeData2)]=nodeData2;
    }
    Tree** trees=new Tree*[nodeAmount];
    
    for(int i=0;i<nodeAmount;i++)
    {
        trees[i]=new Tree(nodes[i]);
        int edgeCount=0;
        while(edgeCount<edgeAmount){
            for(int j=0;j<edgeAmount;j+=2){
                // cout<<"edge1: "<<edges[j]<<" edge2: "<<edges[j+1]<<endl;
                int inserted=trees[i]->insert(edges[j+1], edges[j]);
                // cout<<"inserted: "<<inserted<<endl;
                if(inserted<0) inserted=trees[i]->insert(edges[j], edges[j+1]);
                // cout<<"inserted: "<<inserted<<endl;
                if(inserted>=0) edgeCount+=2;
                // cout<<endl;
            }
        }
        // cout<<endl;
    }
    
    int shortest=100;
    for(int i=0;i<nodeAmount;i++){    
        if(trees[i]->height<shortest) shortest=trees[i]->height;
    }
    
    for(int i=0;i<nodeAmount;i++) if(trees[i]->height==shortest) cout<<trees[i]->root->data<<" ";
}