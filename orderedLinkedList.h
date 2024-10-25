#ifndef H_orderedListType
#define H_orderedListType

//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an ordered doubly linked list.
//***********************************************************

#include "linkedList.h"

using namespace std;

template <class Type>
class orderedLinkedList: public linkedListType<int>
{
public:
    bool search(const Type& searchItem) const;
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the list,
      //    otherwise the value false is returned.

    void insert(const Type& newItem);
      //Function to insert newItem in the list.
      //Postcondition: first points to the new list, newItem
      //    is inserted at the proper place in the list, and
      //    count is incremented by 1.

    void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the beginning of the list, last points to the
      //    last node in the list, and count is incremented by 1.

    void insertLast(const Type& newItem);
      //Function to insert newItem at the end of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the end of the list, last points to the
      //    last node in the list, and count is incremented by 1.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing deleteItem is
      //    deleted from the list; first points to the first node
      //    of the new list, and count is decremented by 1. If
      //    deleteItem is not in the list, an appropriate message
      //    is printed.

    void mergeLists(orderedLinkedList<Type> &list1, orderedLinkedList<Type> &list2);
};

template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const
{
    bool found = false;
    nodeType<Type> *current; //pointer to traverse the list

    current = first;  //start the search at the first node

    while (current != NULL && !found)
        if (current->info >= searchItem) //what exactly is going on here?
            found = true;
        else
            current = current->link;

    if (found)
       found = (current->info == searchItem); //test for equality

    return found;
}//end search


template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    nodeType<Type> *newNode;  //pointer to create a node

    bool  found;

    newNode = new nodeType<Type>; //create the node
    newNode->info = newItem;   //store newItem in the node
    newNode->link = NULL;      //set the link field of the node
                               //to NULL

    if (first == NULL)  //Case 1: insert into an empty list
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else  //insert into a non-empty list
    {
        current = first;
        found = false;

        while (current != NULL && !found) //search the list
           if (current->info >= newItem)
               found = true;
           else
           {
               trailCurrent = current;
               current = current->link;
           }

        if (current == first)      //Case 2: the new item is smallest
        {
            newNode->link = first;
            first = newNode;
            count++;
        }
        else                       //Case 3: the new item is not smallest
        {
            trailCurrent->link = newNode;
            newNode->link = current;

            if (current == NULL)
                last = newNode;

            count++;
        }
    }//end else
}//end insert

template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    insert(newItem);
}//end insertFirst

template<class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
    insert(newItem);
}//end insertLast

template<class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    if (first == NULL) //Case 1
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        current = first;
        found = false;

        while (current != NULL && !found)  //search the list
            if (current->info >= deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }

        if (current == NULL)   //Case 4
            cout << "The item to be deleted is not in the "
                 << "list." << endl;
        else
            if (current->info == deleteItem) //the item to be
                                   //deleted is in the list
            {
                if (first == current)       //Case 2
                {
                    first = first->link;

                    if (first == NULL)
                        last = NULL;

                    delete current;
                }
                else                         //Case 3
                {
                    trailCurrent->link = current->link;

                    if (current == last)
                        last = trailCurrent;

                    delete current;
                }
                count--;
            }
            else                            //Case 4
                cout << "The item to be deleted is not in the "
                     << "list." << endl;
    }
}//end deleteNode

template<class Type>
void orderedLinkedList<Type>::mergeLists(orderedLinkedList<Type> &list1,orderedLinkedList<Type> &list2)
{
    //From Assignmnet:
    //This function creates a new list by merging the
    //elements of list1 and list2.
    //Postcondition: first points to the merged list; list1
    // and list2 are empty

    nodeType<Type> *current1 = list1.first; // points to the beginning of list 1
    nodeType<Type> *current2 = list2.first; // points to the beginning of list 2
    nodeType<Type> *headMerge = NULL; // points to the head of the list of merged values
    nodeType<Type> *currentMerge = NULL; // points to list of merged values

    // while there is stuff in both lists, merge them
    while(current1!=NULL && current2!=NULL){
        nodeType<Type> *newNode = new nodeType<Type>; // create new node
        newNode->link = NULL; // initialize link with null
        // if the elements in the two lists are the same, add twice
        if(current1->info==current2->info){
            newNode->info = current1->info; // assign the value from list1
            // if the head of the merged list is null, make newNode the head
            if (headMerge == NULL){
                headMerge = newNode;
                currentMerge = headMerge;
            } else { // otherwise link newNode to the merged list
                currentMerge->link = newNode;
                currentMerge = newNode;
            }
            // we need a duplicate node for the duplicate value
            newNode = new nodeType<Type>;
            newNode->info = current1->info;
            newNode->link = NULL;
            currentMerge->link = newNode;
            currentMerge = newNode;
            current1 = current1->link; // move forward in list1
            current2 = current2->link; // move forward in list2
        } else {
            if(current1->info>current2->info){
                newNode->info = current2->info; // assign the value from list2
                current2 = current2->link; // move forward in list2
            } else {
                newNode->info = current1->info; // assign the value from list1
                current1 = current1->link; // move forward in list1
            }
            // same process as above to merge newNode to list
            if (headMerge == NULL){
                headMerge = newNode;
                currentMerge = headMerge;
            } else {
                currentMerge->link = newNode;
                currentMerge = newNode;
            }
        }
    }

    // if any nodes remain in list1, append to merged list
    while (current1 != NULL) {
        nodeType<Type> *newNode = new nodeType<Type>;
        newNode->info = current1->info; // get the rest of the info
        newNode->link = nullptr; // initialize link
        currentMerge->link = newNode; // bring in new node
        currentMerge = newNode; // go to new node
        current1 = current1->link; // move onward in list1
    }

    // if any nodes remain in list2, append to merged list
    while (current2 != NULL) {
        nodeType<Type> *newNode = new nodeType<Type>;
        newNode->info = current2->info; // get the rest of the info
        newNode->link = nullptr; // initialize link
        currentMerge->link = newNode; // bring in new node
        currentMerge = newNode; // go to new node
        current2 = current2->link; // move onward in list2
    }

    // set both input lists to empty
    list1.first=NULL;
    list2.first=NULL;
    // merged list is new list
    this->first = headMerge;
}

#endif