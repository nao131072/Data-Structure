#include <iostream>
using namespace std;

class Stack
{
    public:
        struct stackNode
        {
            int* weightArray=nullptr;
            int size=0;
            stackNode *next=nullptr;
        };
    
        stackNode *top;
        int size;
        Stack();
        void push(stackNode *node);
        stackNode* pop();
        stackNode* peek();
        bool isEmpty();
};

Stack::Stack()
{
    top=nullptr;
    size=0;
}

void Stack::push(stackNode *node)
{
    if(top==nullptr)
    {
        top=node;
        size++;
    }
    else
    {
        node->next=top;
        top=node;
        size++;
    }
}

Stack::stackNode* Stack::pop()
{
    if(top==nullptr)
    {
        return nullptr;
    }
    else
    {
        stackNode *temp=top;
        top=top->next;
        size--;
        return temp;
    }
}

Stack::stackNode* Stack::peek()
{
    if(top==nullptr)
    {
        return nullptr;
    }
    else
    {
        return top;
    }
}

bool Stack::isEmpty()
{
    if(top==nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Stack *taxiStack=new Stack();
    int input=0;
    int *inputArray=new int[100];
    int i=0;
    while(cin>>input)
    {
        inputArray[i]=input;
        i++;
    }
    int *weights=new int[i];

    for(int j=0;j<i;j++)
    {
        weights[j]=inputArray[j];
    }
    delete [] inputArray;
    
    int _200Count=0;
    int weightSum=0;
    int *oneTaxi=nullptr;
    for(int j=0;j<i;j++)
    {
        bool overWeight=weightSum+weights[j]>200;
        if(!overWeight)
        {
           weightSum+=weights[j];
           _200Count++;
        }
        if(overWeight)
        {
            oneTaxi=new int[_200Count];
            for(int k=0;k<_200Count;k++)
            {
                oneTaxi[k]=weights[j-_200Count+k];
                // cout<<oneTaxi[k]<<" ";
            }
            // cout<<endl;
            Stack::stackNode *node=new Stack::stackNode;
            node->weightArray=oneTaxi;
            node->size=_200Count;
            taxiStack->push(node);
            _200Count=1;
            weightSum=weights[j];
        }
    }
    
    if(_200Count>0)
    {
        oneTaxi=new int[_200Count];
        for(int k=0;k<_200Count;k++)
        {
            oneTaxi[k]=weights[i-_200Count+k];
            // cout<<oneTaxi[k]<<" ";
        }
        // cout<<endl;
        Stack::stackNode *node=new Stack::stackNode;
        node->weightArray=oneTaxi;
        node->size=_200Count;
        taxiStack->push(node);
    }
    cout<<taxiStack->size<<endl;
    Stack::stackNode *temp=taxiStack->top;
    while(temp!=nullptr)
    {
        for(int j=0;j<temp->size;j++)
        {
            if(temp->weightArray[j])
                cout<<temp->weightArray[j]<<" ";
        }
        temp=temp->next;
    }
}

