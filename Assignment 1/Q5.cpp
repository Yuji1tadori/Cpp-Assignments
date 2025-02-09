/*

5. Rotate Matrix 90 Degrees
Rotate a square matrix 90 degrees clockwise.

*/

#include <iostream>
using namespace std;
int main()
{
    int  n;
    cout << "Enter number of rows and columns: ";
    cin >> n;

    int arr[n][n];
    cout << "Enter elements of the matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];

    int left = 0, right = n - 1, top = 0, bottom = n - 1;

    cout << "Spiral Order: ";
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++)  
            cout << arr[top][i] << " ";
        top++;

        for (int i = top; i <= bottom; i++)  
            cout << arr[i][right] << " ";
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--)  
                cout << arr[bottom][i] << " ";
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--)  
                cout << arr[i][left] << " ";
            left++;
        }
    }

    return 0;
}