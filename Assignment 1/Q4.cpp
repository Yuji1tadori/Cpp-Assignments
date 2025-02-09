/*

4. Spiral Number Pattern
Print a spiral pattern of numbers for a given size n.
Example forn4 (4x4 matrix):

*/

#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter the size: ";
    cin >> n;

    int arr[n][n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(arr[i][j], arr[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            swap(arr[i][j], arr[i][n - j - 1]);
        }
    }

    cout << "Rotated Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}