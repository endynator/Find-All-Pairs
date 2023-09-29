#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector> 

using namespace std; 

struct Contacts {
    string name;
    string phoneNumber;
};

void t1() {
    vector<Contacts> contactList;
    int t;

    cout << "(1) Add contact\n(2) Change contact\n(3) Find contact by name\n(4) Find contact by phone number\n(0) to exit program\n";
    cin >> t;

    while (t != 0) {
        switch (t) {
        case 1: {
            Contacts contact;
            cout << "New contact name: ";
            cin >> contact.name;
            cout << contact.name << "'s phone number: ";
            cin >> contact.phoneNumber;
            contactList.push_back(contact);
            cout << "Saved.\n";
            break;
        }
        case 2: {
            string c;
            cout << "Name: ";
            cin >> c;
            for (Contacts& contact : contactList) {
                if (contact.name == c) {
                    int k;
                    cout << "(1) Change name\n(2) Change phone number\n";
                    cin >> k;
                    if (k == 1) {
                        cout << "Change to: ";
                        cin >> contact.name;
                        cout << "Done.\n";
                    }
                    else if (k == 2) {
                        cout << "Change to: ";
                        cin >> contact.phoneNumber;
                        cout << "Done.\n";
                    }
                }
            }
            break;
        }
        case 3: {
            string c;
            bool succeeded = false;
            cout << "Name: ";
            cin >> c;
            for (const Contacts& contact : contactList) {
                if (contact.name == c) {
                    cout << "Phone Number: " << contact.phoneNumber << endl;
                    succeeded = true;
                }
            }
            if (!succeeded) cout << c << " was not found.\n";
            break;
        }
        case 4: {
            string c;
            bool succeeded = false;
            cout << "Phone Number: ";
            cin >> c;
            for (const Contacts& contact : contactList) {
                if (contact.phoneNumber == c) {
                    cout << "Name: " << contact.name << endl;
                    succeeded = true;
                }
            }
            if (!succeeded) cout << c << " was not found.\n";
            break;
        }
        }
        cout << "(1) Add contact\n(2) Change contact\n(3) Find contact by name\n(4) Find contact by phone number\n(0) to exit program\n";
        cin >> t;
    }
}
