#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "linkedList.h"
#include "orderedLinkedList.h"
using namespace std;

// Thought it might be easier to have all the test cases in one csv if rewritten in a new main for testing

// funciton to ss the numbers from the csv line into a vector
vector<int> csv(const std::string& input) {
    std::vector<int> numbers; // vector to take in nums
    std::stringstream ss(input); // use stringstream to get inputs
    std::string value; // variable to use in getline
    
    // while getting nums, put them in the vector
    while (getline(ss, value, ',')) {
        numbers.push_back(stoi(value));
    }

    // return the vector to work with the values
    return numbers;
}

string line;
int cnt = 0;

int main(){
    // initialize lists
    orderedLinkedList<int> list1, list2, newList;
    // recognize the test csv to get values from
    ifstream file("test_cases.csv");

    while (getline(file, line)) {
        if (line.empty()) {
            // merge and print list after reading them
            if (cnt == 2) {
                cout << "List 1: ";
                list1.print();
                cout << endl;

                cout << "List 2: ";
                list2.print();
                cout << endl;

                // use mergeLists() and print
                newList.mergeLists(list1, list2);
                cout << "Merged List: ";
                newList.print();
                cout << endl;

                // resest for next pair of lists
                list1.destroyList();
                list2.destroyList();
                newList.destroyList();
                cnt = 0;
            }
            continue;  // skip empty lines
        }

        // get nums from line
        vector<int> numbers = csv(line);

        // put nums in corresponding list
        if (cnt == 0) {
            for (int num : numbers) {
                list1.insert(num);
            }
            cnt++;  // move list 2
        } else if (cnt == 1) {
            for (int num : numbers) {
                list2.insert(num);
            }
            cnt++;  // merge them
        }
    }

    // print the last pair
    if (cnt == 2) {
        cout << "List 1: ";
        list1.print();
        cout << endl;

        cout << "List 2: ";
        list2.print();
        cout << endl;

        newList.mergeLists(list1, list2);
        cout << "Merged List: ";
        newList.print();
        cout << endl;
    }

    // close file
    file.close();
    return 0;
}