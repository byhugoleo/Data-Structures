//Implementation of a linked list
#include <bits/stdc++.h>

using namespace std;

struct Data {
//Methods
    void set_Info(int info) {
        this->info = info;
    }
    int get_Info() const{
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
    node() : n(NULL) {}

    node(int data) { 
        info.set_Info(data);
        n = NULL;
    }
    
    ~node() {
        free(n);
    };

//Methods
    node* get_NxtNode() const{
        return n;
    }

    void change_NxtNode(node* n) {
        this->n = n;
    }

    int Compare(int x) const{
        return (info.get_Info() > x ? 1 : info.get_Info() == x ? 0 : -1);
    }

    Data get_Data() const{
        return info;
    }

    void Report() const{
        cout << info.get_Info();
    }
};

class linked_list {
//Data-Properties
    node *head;
    int size;

public:
//Constructors-Destructors
    linked_list() {
        head = NULL;
        size = 0;
    }

    linked_list(int* array, int size) {
        head = new node(array[0]);
        node *temp = head;
        for (int i = 1; i < size; i++) {
            temp->change_NxtNode(new node(array[i]));
            temp = temp->get_NxtNode();
        }
        this->size = size;
    }

    ~linked_list() {
        node *temp = head;
        while (head != NULL) {
            temp = head;
            head = head->get_NxtNode();
            free(temp);
        }
    };

//Methods
    bool Insert(int data, int pos = 0) {
        if (pos > size or pos < 0) {
            cout << "Invalid Position!!!\n";
            return false;
        }
        node *tempnode, *prevnode = head;
        tempnode = new node(data);
        if (!size) {
            head = tempnode;
            size++;
            return true;
        }
        size++;
        if (!pos) {
            tempnode->change_NxtNode(head);
            head = tempnode;
            return true;
        }
        for (int i = 0; i < pos - 1; i++)
            prevnode = prevnode->get_NxtNode();
        tempnode->change_NxtNode(prevnode->get_NxtNode());
        prevnode->change_NxtNode(tempnode);
        return true;
    }

    bool ordered_Insert(int data) {
        node *tempnode, *prevnode, *curnode = head;
        tempnode = new node(data);
        if (!size) {
            head = tempnode;
            size++;
            return true;
        }
        size++;
        if (curnode->Compare(data) == 1) {
            tempnode->change_NxtNode(head);
            head = tempnode;
            return true;
        }
        while (curnode != NULL) {
            if (curnode->Compare(data) == 1)
                break;
            prevnode = curnode;
            curnode = curnode->get_NxtNode();
        }
        tempnode->change_NxtNode(prevnode->get_NxtNode());
        prevnode->change_NxtNode(tempnode);
        return true;
    }

    bool Erase(int pos) {
        if (pos < 0 or pos > size - 1) {
            cout << "Invalid Position!!!\n";
            return false;
        }
        node *prevnode = head, *tempnode;
        size--;
        if (!pos) {
            head = prevnode->get_NxtNode();
            free(prevnode);
            return true;
        }
        for (int i = 0; i < pos; i++) {
            tempnode = prevnode;
            prevnode = prevnode->get_NxtNode();
        }
        tempnode->change_NxtNode(prevnode->get_NxtNode());
        free(prevnode);
        return true;
    }

    void Clear() {
        node *temp = head;
        while (head != NULL) {
            temp = head;
            head = head->get_NxtNode();
            free(temp);
        }
        size = 0;
    }

    int get_Size() const{
        return size;
    }

    void Sort() {
        //TODO: sort the linked list
    }

    bool Search(int data) {
        node *temp = head;
        while (temp != NULL) {
            if (!temp->Compare(data)) {
                return 1;
            }
            temp = temp->get_NxtNode();
        }
        return 0;
    }

    void Report() {
        node *curnode = head;
        if (curnode == NULL or !size) {
            cout << "Empty List!!!\n";
            return;
        }
        cout << "INFO->";
        while (curnode != NULL) {
            cout << " ", curnode->Report();
            curnode = curnode->get_NxtNode();
        }
        cout << endl;
    }

    void ordered_Report() {
        node *temp = head;
        if (temp == NULL or !size) {
            cout << "Empty List!!!" << endl;
            return;
        }
        const int maxn = (int)1e5;
        int count[maxn];
        while (temp != NULL) {
            count[temp->get_Data().get_Info()]++;
            temp = temp->get_NxtNode();
        }
        for (int i = 1; i <= maxn; i++)
            count[i] += count[i - 1];
        temp = head;
        int ans[size], info;
        while (temp != NULL) {
            info = temp->get_Data().get_Info();
            ans[count[info] - 1] = info;
            count[info]--;
            temp = temp->get_NxtNode();
        }
        cout << "INFO->";
        for (int i = 0; i < size; i++)
            cout << " " << ans[i];
        cout << endl; 
    }
};

int main()
{
    srand(time(NULL));
    /*Functions
    -linkedlist(int* array): constructor with parameter
    -bool Insert(int data, int pos = 0): insert function with position parameter (0 as default)
    -bool ordered_Insert(int data): insert ordered elements
    -bool Erase(int pos)
    -void Clear(): erase all elements of linked list
    -int get_Size(): return the size of the linked list
    -bool Search(int data): search for "data" in the linked list
    -void Report()
    -void orderedReport(): Report with counting sort
    -*/

    cout << "TESTS #1\n" << endl; 
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    linked_list l(array, 8);
    l.Report();
    l.Erase(7);
    l.Report();
    l.Insert(12);
    l.Report();
    while (l.Erase(0));
    l.Report();
    l.Insert(1);
    l.Insert(2);
    l.Report();
    l.Clear();
    l.Report();
    l.Insert(1);
    l.Report();
    l.Erase(0);
    l.Report();
    for (int i = 0; i < 5; i++)
        l.Insert(1 << i, i);
    l.Report();
    l.Clear();
    l.Report();

    cout << "\nTESTS #2\n" << endl;
    linked_list lk;
    for (int i = 0; i < 10; i++)
        lk.ordered_Insert(i);
    lk.Report();
    linked_list ulk;
    for (int i = 0; i < 10; i++)
        ulk.Insert(i);
    ulk.Report();

    cout << "\nTESTS #3\n" << endl;
    linked_list sl;
    vector<int> v;
    for (int i = 0; i < 20; i++) {
        int r = rand() % 50;
        v.push_back(r);
        sl.ordered_Insert(r);
    }
    sort(v.begin(), v.end());
    cout << "INFO->";
    for (auto i : v)
        cout << " " << i;
    cout << endl;
    sl.Report();

    cout << "\nTESTS #4\n" << endl;
    linked_list lt;
    lt.Report();
    v.clear();
    for (int i = 0; i < 30; i++) {
        int r = rand() % 100;
        v.push_back(r);
        lt.Insert(r);
    }
    sort(v.begin(), v.end());
    cout << "INFO->";
    for (auto i : v)
        cout << " " << i;
    cout << endl;
    lt.ordered_Report();
    lt.Report();
    cout << lt.get_Size() << endl;
}