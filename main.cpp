// Joseph Ismailyan
// creates a doubly linked list and provides some operations
#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct node{
    int data;
    node* prev;
    node* next;
};

void deleteFromFront(node*&, node*&);
void deleteFromBack(node*&, node*&);
void traverseToScreenBack(node*);
void traverseToScreenFront(node*);
void insertEnd(int, node*&, node*&);
void writeToFile(node*&);

int main(){
    node *head, *tail;
    head = NULL;
    tail = NULL;
    int helper = 0;

    if(in){
        do{
            in >> helper;
            insertEnd(helper, head, tail);
        }while(!in.eof());
        in.close();
        traverseToScreenFront(head);
        deleteFromFront(head, tail);
        traverseToScreenFront(head);
        deleteFromBack(head, tail);
        traverseToScreenFront(head);
        writeToFile(head);
    }
    else{
        cout << "File was not opened successfully" << endl;
        cout << "Please create or modify input.txt" << endl;
    }
return 0;

}

void writeToFile(node *&head){
    node *current = head;
    if(out){
        while(current){
            out << current->data << ' ';
            current = current->next;
        }
        cout << endl << "output.txt written successfully." << endl;
    }
    else{
        cout << "File was not opened successfully" << endl;
        cout << "Please create or modify output.txt" << endl;
    }
    out.close();
}

void traverseToScreenFront(node *head){
    node *current = head;
    cout << "front: " << endl;
    while(current){
        cout << current->data << endl;
        current = current->next;
    }
}

void traverseToScreenBack(node *tail){
    node *current = tail;
    cout << "back: " << endl;
    while(current){
        cout << current->data << endl;
        current = current->prev;
    }
}

void insertEnd(int item, node *&head, node *&tail){
    node *newNode;
    newNode = new node;
    newNode->data = item;
    newNode->prev = tail; // let node see the tail even if there isnt one it will be NULL

    if(!head){
        //if there is nothing in the list
        head = newNode;       //has a head now :) birth
        tail = newNode;       //has a tail now :) birth
        newNode->next = NULL; //make sure that the new node is the VERY end

    }
    else{
        //if this is not the first node
        newNode->next = NULL; //make sure that the new node is the VERY end
        tail->next = newNode; //hook up current tail to the new node (add it to the end)
        tail = newNode;     //make the tail reflect the new change
    }

}

void deleteFromFront(node *&head, node *&tail){
    int counter;
    node* temp;
    node* lastTemp;
    node* toDelete;
    temp = head;
    lastTemp = temp;

    cout << "Enter item to delete from beginning: ";
    cin >> counter;

    for(int i = 1; i < counter; i++){
        temp = temp->next;
        lastTemp = temp->prev;
    }
    lastTemp->next = temp->next;
    toDelete = temp;
    if(temp->next == NULL){
        delete temp;
    }
    else {
        temp = temp->next;
        temp->prev = lastTemp;
    }
    if(toDelete->prev == NULL){
        head = toDelete->next;
    }
    if(toDelete->next == NULL){
        tail = toDelete->prev;
    }
    delete toDelete;
}

void deleteFromBack(node *&head, node *&tail){
    int counter;
    node* temp;
    node* nextTemp;
    node* toDelete;
    temp = tail;
    nextTemp = temp;

    cout << "Enter item to delete from end: ";
    cin >> counter;

    for(int i = 1; i < counter; i++){
        temp = temp->prev;
        nextTemp = temp->next;
    }
    nextTemp->prev = temp->prev;
    toDelete = temp;
    if(temp->prev == NULL){
        head = temp->next;
        delete temp;
    }
    else {
        temp = temp->prev;
        temp->next = nextTemp;
    }
    if(toDelete->prev == NULL){
        head = toDelete->next;
        head->prev = NULL;
    }
    if(toDelete->next == NULL){
        tail = toDelete->prev;
        tail->next = NULL;
    }
    delete toDelete;
}
