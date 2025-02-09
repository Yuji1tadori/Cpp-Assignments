/*

2. Array Operations
Write a program that performs the following operations on an array:
a. Accept an integer array from the user (size determined at runtime).
b. Reverse the array and display it.
c. Find and display the second largest and second smallest elements in the array.

*/

#include <iostream>
using namespace std;
int main()
{
    int num;
    cout<<"Enter the size of the array : ";
    cin>>num;
    int arra[num];
    cout<<"Enter the numbers of the array : ";
    for (int i=0;i<num;i++)
    {
        cin>>arra[i];
    }
    cout<<endl<<"The reversed array : ";
    for (int i=num-1;i>=0;i--)
    {
        cout<<arra[i]<<" ";
    }
    cout<<endl<<endl;
    int n = sizeof(arra)/sizeof(arra[0]);
    sort(arra,arra+n);
    int second_small = 0, second_large = 0;
    for (int i=0;i<num;i++)
    {
        if (arra[i]!=arra[0])
        {
            second_small = arra[i];
            break;
        }
    }

    for (int i=num-2;i>=0;i--)
    {
        if (arra[i]!=arra[num-1])
        {
            second_large = arra[i];
            break;
        }
    }

    if (second_small != 0)
    {
        cout<<"The second smallest number in the array is : "<<second_small<<endl<<endl;
    }
    else
    {
        cout<<"All elements are equal!"<<endl<<endl;
    }

    if(second_large != 0)
    {
        cout<<"The second largest number in the array is : "<<second_large<<endl;
    }
    else
    {
        cout<<"All elements are equal!"<<endl<<endl;
    }

    return 0;
}