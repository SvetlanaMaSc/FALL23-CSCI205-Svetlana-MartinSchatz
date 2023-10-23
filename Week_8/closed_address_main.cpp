#include <iostream>
#include <string>
#include <fstream>
#include "ClosedHashTable.hpp"
#include "Contact.h"

using namespace std;

int main() {

    ofstream file("comparisons_closed_10\\%.txt");

    ClosedHashTable<int> htable(7);

    htable.put("apple", 1);
    htable.put("banana", 2);
    htable.put("cherry",3);
    htable.put("date", 4);
    htable.put("durian", 5);
    htable.put("fig", 6);
    htable.put("grape", 7);
    htable.put("honeydew", 8);
    htable.put("lychee", 9);
    htable.put("jicama", 10);
    htable.put("kiwi", 11);
    htable.put("lemon", 12);
    htable.put("mango", 13);
    htable.put("nectarine", 14);
    htable.put("orange", 15);

    // Check if key exists
    bool found = htable.contains("apple");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'apple' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("banana");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'banana' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("cherry");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'cherry' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("date");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'date' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("durian");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'durian' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("fig");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'fig' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("grape");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'grape' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("honeydew");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'honeydew' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("lychee");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'lychee' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("jicama");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'jicama' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("kiwi");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'kiwi' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("lemon");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'lemon' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("mango");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'mango' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("nectarine");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'nectarine' in the hash table == : " << found << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    found = htable.contains("orange");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "'orange' in the hash table == : " << found << endl;

    // Retrieve the value associated with a key
    int value = htable.get("apple");
    cout << "The value of 'apple' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("banana");
    cout << "The value of 'banana' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("cherry");
    cout << "The value of 'cherry' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("date");
    cout << "The value of 'date' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("durian");
    cout << "The value of 'durian' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("fig");
    cout << "The value of 'fig' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("grape");
    cout << "The value of 'grape' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("honeydew");
    cout << "The value of 'honeydew' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("lychee");
    cout << "The value of 'lychee' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("jicama");
    cout << "The value of 'jicama' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("kiwi");
    cout << "The value of 'kiwi' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("lemon");
    cout << "The value of 'lemon' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("mango");
    cout << "The value of 'mango' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("nectarine");
    cout << "The value of 'nectarine' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;
    value = htable.get("orange");
    cout << "The value of 'orange' is: " << value << endl;
    file << "99\\% " << htable.getComparisons() << endl;

    
    // Print the contents of the hash table
    cout << "Hash Table contents: " << endl;
    htable.print();

    // Remove a key-value pair
    cout << "Removing 'apple' from the hash table." << endl;
    htable.remove("apple");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'apple' from the hash table." << endl;
    htable.remove("banana");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'banana' from the hash table." << endl;
    htable.remove("cherry");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'cherry' from the hash table." << endl;
    htable.remove("date");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'date' from the hash table." << endl;
    htable.remove("durian");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'durian' from the hash table." << endl;
    htable.remove("fig");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'fig' from the hash table." << endl;
    htable.remove("grape");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'grape' from the hash table." << endl;
    htable.remove("honeydew");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'honeydew' from the hash table." << endl;
    htable.remove("lychee");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'lychee' from the hash table." << endl;
    htable.remove("jicama");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'jicama' from the hash table." << endl;
    htable.remove("kiwi");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'kiwi' from the hash table." << endl;
    htable.remove("lemon");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'lemon' from the hash table." << endl;
    htable.remove("mango");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'mango' from the hash table." << endl;
    htable.remove("nectarine");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'nectarine' from the hash table." << endl;
    htable.remove("orange");
    file << "99\\% " << htable.getComparisons() << endl;
    cout << "Removing 'orange' from the hash table." << endl;

    // Print the contents of the hash table
    cout << "Hash Table contents: " << endl;
    htable.print();

    file.close();

    ClosedHashTable<Contact> myContactTable(7);

    Contact c1("John", "email1", "phone1");
    Contact c2("Bob", "email2", "phone2");
    Contact c3("Mary", "email3", "phone3");
    Contact c4("Rob", "email4", "phone4");
    Contact c5("Joe", "email5", "phone5");
    Contact c6("Sue", "email6", "phone6");
    Contact c7("Ann", "email7", "phone7");
    Contact c8("Tim", "email8", "phone8");
    Contact c9("Dan", "email9", "phone9");
    Contact c10("Max", "email10", "phone10");

    Contact contacts[] = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10};

    for (int i = 0; i < 10; i++) {
        myContactTable.put(contacts[i].getName(), contacts[i]);
    }

    cout << "\nContacts" << endl;
    cout << "--------" << endl;
    myContactTable.print();

    return 0;
}