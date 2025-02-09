/*

1. Number Manipulation and Prime Numbers
Write a C++ program to take a positive integer n as input and:
1. Check whether n is a prime number.
2. If it is not prime, find all its factors.
3. If it is prime, find the next prime number greater than n.

*/

#include <iostream>
using namespace std;
int main()
{
    int i, n;

start:  
    cout << "\nEnter a Positive Number: ";
    cin >> n;

    if (n < 0)
    {
        cout << n << " is not positive.";
        goto start;
    }
    else if (n == 1)
    {
        cout << "1 is neither Prime nor Composite";
    }
    else
    {
        bool is_prime = true;  //Remember This.
        for (i = 2; i * i <= n; i++)  
        {
            if (n % i == 0)
            {
                is_prime = false;  
                break;  
            }
        }

        if (is_prime && n > 1)  
        {
            cout << n << " is Prime.";
            //For finding next Prime Number
            //Bhai kya hai ye 😭
            int next = n + 1;
            while (true)  
            {
                bool found_prime = true;
                for (i = 2; i * i <= next; i++)  
                {
                    if (next % i == 0)  
                    {
                        found_prime = false;
                        break;
                    }
                }
                if (found_prime)  
                {
                    cout << "\nNext Prime is: " << next;
                    break;
                }
                next++;  
            }
        }
        else
        {
            cout << n << " is NOT Prime.";
            cout << "\nFactors of " << n << " are ";
            for (i = 1; i <= n; i++)  
            {
                if (n % i == 0)  
                {
                    cout << i << " ";
                }
            }
        }
    }
}
