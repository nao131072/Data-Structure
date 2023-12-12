#include <iostream>
using namespace std;

int insertionSort(int arr[], string& symbols, string keyString) {
    int step=1;
    bool found=false;
    for(int i=1;i<keyString.length();i++) {
        int temp=arr[i];
        char tempChar=symbols[i];
        int j=i-1;
        while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j];
            symbols[j+1]=symbols[j];
            j--;
        }
        arr[j+1]=temp;
        symbols[j+1]=tempChar;
        if(!found) step++;
        if(keyString == symbols) found=true;
    }
    if(found) return step;
    else return -1;
}

int selectionSort(int arr[], string& symbols, string keyString) {
    int step = 0;
    bool found=false;
    int n=keyString.length();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        swap(arr[i], arr[min]);
        swap(symbols[i], symbols[min]);
        if(!found) step++;
        if(symbols==keyString) found=true;
    }
    if(found) return step;
    else return -1;
}

int main() {
    string keyString="";
    cin>>keyString;
    int size=keyString.length();
    int arr1[size];
    int arr2[size];
    string symbols1;
    string symbols2;
    
    for(int i=0;i<size;i++){
        int n=0;
        cin>>n;
        arr1[i]=n;
        arr2[i]=n;   
    }
    for(int i=0;i<size;i++) {
        char c;
        cin>>c;
        symbols1+=c;
        symbols2+=c;
    }
    
    int insStep=insertionSort(arr1, symbols1, keyString);
    int selStep=selectionSort(arr2, symbols2, keyString);
    
    if(insStep==-1 && selStep==-1) cout<<"Word not found."<<endl;
    else if(insStep==-1) cout<<"Word found in selection sort step "<<selStep<<"."<<endl;
    else if(selStep==-1) cout<<"Word found in insertion sort step "<<insStep<<"."<<endl;
    else cout<<"Word found in insertion sort step "<<insStep<<" and selection sort step "<<selStep<<"."<<endl;
    cout<<symbols1<<endl;
    return 0;
}
