#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// 1) 
void countLetters(const string& text) {
    int letterCount[26] = { 0 }; 

    for (char c : text) {
        if (isalpha(c)) {
            c = tolower(c); 
            letterCount[c - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        char letter = 'a' + i;
        if (letterCount[i] > 0) {
            cout << letter << ": " << letterCount[i] << " ";
        }
    }
    cout << endl;
}

// 2) 
void countDigits(const string& text) {
    int digitCount[10] = { 0 };

    for (char c : text) {
        if (isdigit(c)) {
            digitCount[c - '0']++;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (digitCount[i] > 0) {
            cout << i << ": " << digitCount[i] << " ";
        }
    }
    cout << endl;
}

// 3) 
int countSentences(const string& text) {
    int sentenceCount = 0;
    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            sentenceCount++;
        }
    }
    return sentenceCount;
}

// 4) 
int countPeriodsAndCommas(const string& text) {
    int count = 0;
    for (char c : text) {
        if (c == '.' || c == ',') {
            count++;
        }
    }
    return count;
}

// 5) 
string capitalizeSentences(const string& text) {
    string result = text;
    bool capitalizeNext = true;

    for (int i = 0; i < result.length(); i++) {
        if (capitalizeNext && isalpha(result[i])) {
            result[i] = toupper(result[i]);
            capitalizeNext = false;
        }
        if (result[i] == '.' || result[i] == '!' || result[i] == '?') {
            capitalizeNext = true;
        }
    }

    return result;
}

// 6) 
string replaceWord(const string& text, const string& target, const string& replacement) {
    string result = text;
    int pos = result.find(target);
    while (pos != string::npos) {
        result.replace(pos, target.length(), replacement);
        pos = result.find(target, pos + replacement.length());
    }
    return result;
}

// 7) 
int countWordOccurrences(const string& text, const string& word) {
    int count = 0;
    int pos = text.find(word);
    while (pos != string::npos) {
        count++;
        pos = text.find(word, pos + word.length());
    }
    return count;
}

// 8) 
string reverseText(string& text) {
    string reversed = text;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

int main() {
    string text = "the C++ programming language is considered a compiled, statically typed language. creator Bjorn Stroustrup (1983).";

    // 1) 
    countLetters(text); cout << endl;

    // 2) 
    countDigits(text); cout << endl;

    // 3) 
    int sentenceCount = countSentences(text);
    cout << "Number of sentences: " << sentenceCount << endl;  cout << endl;

    // 4) 
    int periodCommaCount = countPeriodsAndCommas(text);
    cout << "Number of periods and commas: " << periodCommaCount << endl;  cout << endl;

    // 5) 
    string capitalizedText = capitalizeSentences(text);
    cout << "Capitalized Text:" << endl << capitalizedText << endl; cout << endl;

    // 6)
    string replacedText = replaceWord(text, "C++", "CPlusPlus");
    cout << "Replaced Text:" << endl << replacedText << endl; cout << endl;

    // 7) 
    string u_data;
    cout << "Word: "; cin >> u_data;

    int wordCount = countWordOccurrences(text, u_data);
    cout << "Occurrences of '" << u_data << "': " << wordCount << endl; cout << endl;

    // 8)
    string reversedText = reverseText(text);
    cout << "Reversed Text:" << endl << reversedText << endl; cout << endl;

    return 0;
}
