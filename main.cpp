#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype> // Required for isalnum and tolower

using namespace std;

// Cleans the string: removes punctuation/symbols and converts to lowercase
string check(const string& s) {
    string result = "";
    for (char c : s) {
        if (isalnum((unsigned char)c)) {
            result += tolower((unsigned char)c);
        }
    }
    return result;
}

int main() {
    ifstream file("data.txt");

    if (!file.is_open()) {
        cout << "Could not open file 'data.txt'. Please ensure it exists in the same directory.\n";
        return 1;
    }

    vector<string> words;
    vector<string> history;
    string s;

    // Read all words from the file and clean them
    while (file >> s) {
        string cleaned = check(s);
        if (!cleaned.empty()) { // Only add if it contains valid alphanumeric characters
            words.push_back(cleaned);
        }
    }
    file.close(); // Good practice to close the file when done

    int ch;
    string searchword;

    while (true) {
        cout << "\n=== MENU ===\n";
        cout << "1. Search a word\n";
        cout << "2. Exit\n";
        cout << "3. View Search History\n";
        cout << "Enter your choice: ";
        
        // Safety check: Ensure the user actually entered an integer
        if (!(cin >> ch)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(10000, '\n'); // Discard the bad input
            continue;
        }

        if (ch == 1) {
            cout << "Enter word to search: ";
            cin >> searchword;

            searchword = check(searchword);

            // If the user entered purely punctuation, skip searching
            if (searchword.empty()) {
                cout << "Invalid search word.\n";
                continue;
            }

            int count = 0;
            for (size_t i = 0; i < words.size(); i++) {
                if (words[i] == searchword) {
                    count++;
                }
            }

            // Save to history
            history.push_back(searchword);

            if (count == 0) {
                cout << "Couldn't find the word '" << searchword << "' in the file.\n";
            } else {
                cout << "The word searched is: " << searchword << endl;
                cout << "Occurrence: " << count << endl;
            }
        }
        else if (ch == 2) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else if (ch == 3) {
            cout << "\n--- Search History ---\n";
            if (history.empty()) {
                cout << "(No searches made yet)\n";
            } else {
                for (size_t i = 0; i < history.size(); i++) {
                    cout << i + 1 << ". " << history[i] << endl;
                }
            }
        }
        else {
            cout << "Invalid choice! Please choose 1, 2, or 3.\n";
        }
    }

    return 0;
}