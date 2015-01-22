//
//  main.cpp
//  PG1 V1 - Find square root of radicant.
//
//  Created by Lawrence Johnson on 1/12/15
//  V1 tested on 1/14/15 10:58pm.
//  Copyright (c) 2015 Lawrence Johnson. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include "main.h"
using namespace std;

int main(int argc, const char * argv[]) {
    string num;
    cout << "Enter a radicand: ";
    getline(cin, num);
    
    string root = square(num), rootSquared = strMult(root, root), remaining = strSub(num, rootSquared);
    
    cout << "The square root of " << num << " is " << root << " and the remainder is " << remaining << endl;

    return 0;
}

/*
 This returns the closest square root smaller or equal to the number as a string.
 @s - Integer passed as a string to find square root of.
 @return - Root of s returned as a string.
 */
string square (string s){
    
    // Get string length to check if even or odd. If odd, add a 0 to the front to make even.
    int numSZ = s.length()%2;
    if (numSZ == 1) s = "0" + s;
    string root = "0", working = "", carry = "", squareRoot = "";
    
    // Calculate square root
    for (int i = 0; i < s.length(); i = i + 2) {
        
        // Get two digits from string. Place the numbers after the carry if carry exists.
        working = carry + s[i] + s[i+1];
        
        // Using the current root value doubled, place a test number at the end.
        //
        for (int j = 0; j < 10; ++j) {
            
            // Convert j and j+1 value to a string to insert for testing.
            string t1 = "", t1n = "";
            t1 = t1 + (char)(j + '0');
            
            // Place j and j+1 after 2 times the value of root.
            t1n = t1n + (char)((j+1) + '0');
            string t2 = (strMult(root, "2") + t1), t2n = (strMult(root, "2") + t1n);
            
            // Times both values by there j value.
            string temp = strMult(t2, t1), tempn = strMult(t2n, t1n);
            
            // If j+1 trial is larger than the working value, use j's values.
            // Stop checking after first j+1 value is larger.
            if (strLargest(working, tempn) == true) {
                carry = strSub(working, temp);
                root = root + t1;
                squareRoot = squareRoot + t1;
                
                // set j to 10 to break current loop.
                j = 10;
            }
        }
    }
    
    // Return square root
    return squareRoot;
}

/*
 This returns the sum of two strings.
 @a & @b - Integer passed as a strings to add.
 @return - sum of a and b returned as a string.
 */
string strAdd(string a, string b) {
    
    string s = "";
    
    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;
    
    a = "0" + a;
    b = "0" + b;
    
    int carry = 0;
    for (int i = (int)a.length()-1; i >= 0; i--) {
        int S = a[i]-'0' + b[i]-'0' + carry;
        carry = S/10;
        S %= 10;
        s = ((char)(S+'0')) + s;
    }
    
    remlzero (s);
    return s;
}

/*
 This returns the product of two strings.
 @a & @b - Integer passed as a strings to multiply.
 @return - Product of a and b returned as a string.
 */
string strMult(string a, string b) {
    
    string s = "0";
    
    for (int i=0; i < (int)a.length(); i++) {
        for (int j=0; j < (int)b.length(); j++) {
            int p = (a[i] - '0') * (b[j]  - '0');
            string pstr = to_string ((long long)p);
            
            for (int k=0; k < (int)a.length()-i-1 + (int)b.length()-j-1; k++)
                pstr += "0";
            
            s = strAdd(s,pstr);
        }
    }
    
    return s;
}

/*
 This returns the difference of two strings.
 @a - First value. Must be the largest value.
 @b - Second value. Must be smaller than a.
 @return - Difference of a and b returned as a string.
 */
string strSub(string a, string b) {
    string s = "";
    
    if (a.length() < b.length()) return "";
    
    while (b.length() < a.length()) b = "0" + b;
    
    a = "0" + a;
    b = "0" + b;
    
    int carry = 0;
    for (int i = (int)a.length()-1; i >= 0; i--) {
        int S;
        if (a[i] - '0' - carry < b[i] - '0') {
            S = (10 + a[i] - '0') - (b[i] - '0') - carry;
            carry = 1;
        }
        else {
            S = (a[i] - '0') - (b[i] - '0') - carry;
            carry = 0;
        }
        s = ((char)(S + '0')) + s;
    }
    
    remlzero (s);
    return s;
}

/*
 This removes all of the 0 at the begining of the string passed.
 @s - Actual value of passed string is modified.
 */
void remlzero (string &s) {
    while (s != "" && s[0] == '0') s = s.substr(1);
    if (s == "") s = "0";
}

/*
 This returns which string is bigger.
 @a & @b - Integer passed as a strings to check.
 @return - If return is true, string b is larger. If return in false, string a is larger.
 */
bool strLargest(string a, string b){
    // make length of strings match.
    while (b.length() < a.length()) b = "0" + b;
    while (a.length() < b.length()) a = "0" + a;
    
    if (a < b) return true;
    else return false;
}
