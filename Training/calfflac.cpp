/*
 ID: 
 PROG: calfflac
 LANG: C++14
 */
//NAME          :   
//GROUP         :   Binary
//LAST MODIFIED :   9 April 2018
//PROBLEM ID    :   USACO Calf Flac
//DESCRIPTION   :   Find the largest palindrome a text file when only looking at alphabetical characters and ignoring case
//SOURCES/HELP  :
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//check if a character is alphabetical using ASCII values
bool checkAlphabet(char temp)
{
    int asciiValue = int(temp);
    if (65 <= asciiValue and asciiValue <= 90 or 97 <= asciiValue and asciiValue <= 122)
    {
        return true;
    }
    return false;
}

//make an alphabetical character lower case
char makeLowerCase(char temp)
{
    int asciiValue = int(temp);
    if (65 <= asciiValue and asciiValue <= 90)
    {
        return static_cast<char>(asciiValue+32);
    }
    return static_cast<char>(asciiValue);
}

//format a string by making it only alphabetical and lower case
string formatString(string unformatted)
{
    string formatted = "";
    for (int i = 0; i < unformatted.size(); ++i)
    {
        if (checkAlphabet(makeLowerCase(unformatted[i])))
        {
            formatted += unformatted[i];
        }
    }
    
    return formatted;
}

int main()
{
    //open input file
    ifstream fin ("calfflac.in");
    
    //read in the original text
    fin >> noskipws;
    char tempChar;
    string originalText = "";
    int textSize = 0;
    while(fin >> tempChar)
    {
        originalText += tempChar;
        ++textSize;
    }
    cout << originalText << endl;
    cout << textSize << endl;
    
    //declare variables
    const int MAX_SIZE = 2000;
    string longestPalindrome = "";
    int biggestSize = 0;
    string text = "";
    vector <int> validIndicies;
    
    //loop through the original text
    for (int i = 0; i < textSize; ++i)
    {
        //check if the current character is alphabetical
        if (checkAlphabet(originalText[i]))
        {
            //add the lower case verison of the letter to the string and add its index to the list
            text += makeLowerCase(originalText[i]);
            validIndicies.push_back(i);
        }
        else
        {
            //otherwise add the invlaid character to the string
            text += originalText[i];
        }
        
    }
    
    //loop through valid indices for the text
    for (int pos = 0; pos < validIndicies.size(); ++pos)
    {
        //set the offset variables
        int offset = 0;
        int evenOffset = 0;
        
        //check if only the character in front is equal to the position; case for palindromes with even length
        if (text[validIndicies[pos-1]] != text[validIndicies[pos]] and text[validIndicies[pos]] == text[validIndicies[pos+1]])
        {
            ++evenOffset;
        }
        
        //loop until two characters are not equal to each other
        while (true)
        {
            ++offset;
            if (text[validIndicies[pos+offset+evenOffset]] != text[validIndicies[pos-offset]])
            {
                --offset;
                break;
            }
        }
        
        //declare string variable
        string toCheck = "";
        
        //loop through the original text
        for (int i = validIndicies[pos-offset]; i <= validIndicies[pos+offset+evenOffset]; ++i)
        {
            //add the original text to a separate string
            toCheck += originalText[i];
        }
        
        //find the size of the string only checking alphabetical characters
        int toCheckSize = formatString(toCheck).size();
        
        //check if the string is the longest palindrome so far
        if (toCheckSize > biggestSize)
        {
            longestPalindrome = toCheck;
            biggestSize = toCheckSize;
        }
    }
    
    //output
    ofstream fout ("calfflac.out");
    fout << biggestSize << endl << longestPalindrome << endl;
    fout.close();
    
    //exit program
    return 0;
}
