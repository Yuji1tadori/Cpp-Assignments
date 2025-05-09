// 3. String Manipulation
// a. Accepts a string from the user.
// b. Checks whether the string is a palindrome (ignoring spaces and case sensitivity).
// c. Counts and displays the frequency of each character in the string (case insensitive).
// d. Replace all vowels in the string with a specific character (e.g., *).

#include <iostream>
#include <string>
using namespace std;

void checkPalindrome(string str){
    string str2;
    int flag = 0;
    for(int i=0;i<str.length();i++){
        if(str[i] != ' '){
            str2+=tolower(str[i]);
        }
    }

    for(int j=0;j<str2.length();j++){
        if(str2[j] != str2[str2.length()-j-1]){
            flag = 1;
            break;
        }
    }

    if(flag == 0){
        cout<<"The string is a palindrome."<<endl;
    }else{
        cout<<"The string is not a palindrome."<<endl;
    }
}

void counter(string str){
    string str2;
    for(int i=0;i<str.length();i++){
        if(str[i] != ' '){
            str2+=tolower(str[i]);
        }
    }
    int arr[str2.length()];
    for(int j=0;j<str2.length();j++){
        int count = 0;
        for(int k=0;k<str2.length();k++){
            if(str2[j] == str2[k]){
                count++;
            }
        }
        arr[j] = count;
        
        bool printed = false;
        for(int p=0; p<j; p++){
            if(str2[p] == str2[j]){
                printed = true;
                break;
            }
        }
        
        if(!printed){
            cout << str2[j] << ": " << count << endl;
        }
    }
} 

void replacement(string str){
    string str3;
    for(int j=0;j<str.length();j++){
        if(str[j] == 'a' || str[j] == 'e' || str[j] == 'i' || str[j] == 'o' || str[j] == 'u' || str[j] == 'A' || str[j] == 'E' || str[j] == 'I' || str[j] == 'O' || str[j] == 'U'){
            str3+='*';
        }else{
            str3+=str[j];
        }
    }
    cout<<"String after replacing vowels with * : "<<str3<<endl;
}

int main(){
    string str;
    int flag=0;
    cout<<"Enter a string : ";
    getline(cin,str);

    checkPalindrome(str);
    cout<<endl;

    counter(str);
    cout<<endl;

    replacement(str);
    return 0;
}
