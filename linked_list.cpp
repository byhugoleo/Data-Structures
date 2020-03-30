//Implementation of a linked list
#include <bits/stdc++.h>

using namespace std;

struct Data {
//Methods
    void set_Info(int info){
        this->info = info;
    }
    int get_Info() {
        return info;
    }

private:
//Data-Properties
    int info;
};

class node {
//Data-Properties
    Data info;
    node *n;

public:
//Constructors-Destructors
    node() : n(NULL){}
    node(int data) { 
        info.set_Info(data);
        n = NULL;
    }
    ~node() {
        delete n;
    };

//Methods
    void build_Node(int data) {
        info.set_Info(data);
        n = NULL;
    }
    node* get_NxtNode() {
        return n;
    }
    void change_NxtNode(node* n) {
        this->n = n;
    }
    void Report() {
        cout << "INFO-> " << info.get_Info() << " ";
    }
};

class linked_list {
//Data-Properties
    node *head, *tail;
    int size;

public:
//Constructors-Destructors
    linked_list() {
        head = new node;
        tail = head;
        size = 0;
    }
    linked_list(int* array) {
        head = new node;
        node *curnode = head;
        for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
            curnode->build_Node(array[i]);
            if (i == (sizeof(array) / sizeof(array[0]) - 1))
                continue;
            curnode = curnode->get_NxtNode();
        }
        tail = curnode;
        size = sizeof(array) / sizeof(array[0]);
    }
    ~linked_list() { 
        delete head, tail;
    };

//Methods
    void Insert(int data, int pos) {
        if (pos > size or pos < 0) {
            cout << "Invalid Position!!!\n\n";
            return;
        }
        cout << "ko" << endl;
        node *tempnode, *prevnode = head;
        size++;
        tempnode = new node(data);
        if (!pos) {
            tempnode->change_NxtNode(head);
            head = tempnode;
            return;
        }
        for (int i = 0; i < pos - 1; i++)
            prevnode = prevnode->get_NxtNode();
        tempnode->change_NxtNode(prevnode->get_NxtNode());
        prevnode->change_NxtNode(tempnode);
    }
    void Erase(int pos) {
        if (pos < 0 or pos > size - 1) {
            cout << "Invalid Position!!!\n\n";
            return;
        }
        node *prevnode = head, *tempnode = new node;
        size--;
        if (!pos) {
            head = head->get_NxtNode();
            return;
        }
        for (int i = 0; i < pos - 1; i++)
            prevnode = prevnode->get_NxtNode();
        tempnode = (prevnode->get_NxtNode())->get_NxtNode();
        prevnode->get_NxtNode()->change_NxtNode(NULL);
        prevnode->change_NxtNode(tempnode);
    }
    void Report() {
        node *curnode = head;
        if (curnode->get_NxtNode() == NULL)
            cout << "Lista Vazia!!!\n\n";
        while (curnode->get_NxtNode() != NULL) {
            curnode->Report(), curnode = curnode->get_NxtNode();
        }
        cout << endl;
    }
};

int main()
{
    linked_list l;
    l.Insert(1, 0);
    l.Insert(2, 1);
    l.Insert(0, 0);
    l.Report();
    l.Erase(1);
    l.Report();
    l.Erase(0);
    l.Report();
    l.Erase(0);
    l.Report();
    cout << " ok " << endl;
    l.Insert(0, 0);
    l.Insert(1, 1);
    l.Insert(2, 2);
    l.Insert(33, 3);
    l.Report();
}