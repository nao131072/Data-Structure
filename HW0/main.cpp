#include <iostream>
#include <string>
using namespace std;
// palindromic function

int main()
{
    bool isPalin(long long int num);
    
    long long int num = 0;
    cin>>num;
    if(isPalin(num))
    {
        cout<<num<<" is a palindrome number."<<endl;
    }
    else
    {
        cout<<num<<" is not a palindrome number."<<endl;
    }
    return 0;
}

bool isPalin(long long int num)
{
    string str = to_string(num);
    int len = str.length();
    for(int i = 0; i < len/2; i++)
    {
        if(str[i] != str[len-i-1])
        {
            return false;
        }
    }
    return true;
}