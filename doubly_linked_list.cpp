#include <bits/stdc++.h>

using namespace std;

#define debug(x) cout << "DEBUG# " << x << endl;

struct Data {
//Constructors
    Data() {
        info = 0;
    }
    Data(int info) {
        this->info = info;
    }
//Methods
    //Const methods
    int get_info() const{
        return info;
    }
    string to_string() const{
        stringstream ss;
        ss << info;
        return ss.str();
    }
    //Non-const methods
    void set_info(int info) {
        this->info = info;
    }

private:
//Data-Properties
    int info;
};

class Node {
//Data-Properties
    Data info;
    Node *prev, *nxt;

public:
//Constructors-Destructors
    Node() : info(), prev(NULL), nxt(NULL) {}
    Node(int info) : info(info), prev(NULL), nxt(NULL) {}
    ~Node() {}
//Methods
    //Const methods
    Data get_info() const{
        return info;
    }
    Node *get_prev_node() const{
        return prev;
    }
    Node *get_nxt_node() const{
        return nxt;
    }
    int compare(int y) const{
        int x = info.get_info();
        return (x > y ? 1 : x < y ? -1 : 0);
    }
    string to_string() const{
        return info.to_string();
    }
    //Non-const methods
    void change_info(int info) {
        this->info.set_info(info);
    }
    void change_prev_node(Node *prev) {
        this->prev = prev;
    }
    void change_nxt_node(Node *nxt) {
        this->nxt = nxt;
    }
    void clear() {
        info.set_info(0);
        clear_prev(), clear_nxt();
    }
    void clear_nxt() {
        nxt = NULL;
    }
    void clear_prev() {
        prev = NULL;
    }
};

class DoublyList {
//Data-Properties
    Node *head, *tail;    
    uint size;
    bool ordered;

public:
//Constructors-Destructors
    DoublyList() : head(new Node), tail(new Node), size(0), ordered(false) {}
    ~DoublyList() {
        Node *curnode;
        while (head != NULL) {
            curnode = head;
            head = head->get_nxt_node();
            free(curnode);
            curnode->clear();
        }
        free(tail);
        tail->clear();
    }
//Methods
    //Const methods
    string to_string(bool reverse = false) const{
        if (head->get_nxt_node() == NULL) {
            return "WARNING:> Empty List.";
        }
        Node *curnode;
        string infos;
        infos += "INFO->";
        if (reverse) {
            curnode = tail;
            while (true) {
                curnode = curnode->get_prev_node();
                if (curnode == NULL)
                    break;
                infos += " " + curnode->to_string();
            }
            return infos;
        }
        curnode = head;
        while (true) {
            curnode = curnode->get_nxt_node();
            if (curnode == NULL)
                break;
            infos += " " + curnode->to_string();
        }
        return infos;
    }
    int search(int info) const{
        Node *temp = head->get_nxt_node();
        uint cnt = -1;
        while (temp != NULL) {
            if (temp->compare(info) == 1 and ordered) {
                debug("entro");
                return -1;
            }
            else if (!temp->compare(info))
                return ++cnt;
            cnt++;
            temp = temp->get_nxt_node();
        }
        return -1;
    }
    //Non-const methods
    bool insert(uint pos, int info) {
        if (ordered) {
            cout << "ERROR:> List mode = sorting insert. Invalid function." << endl;
            cout << "Try ordered_insert(int info)" << endl;
            return false;
        }
        if (pos < 0 or pos > size) {
            cout << "ERROR:> invalid position." << endl;
            return false;
        }
        Node *temp = new Node(info), *prev, *nxt;
        size++;
        if (head->get_nxt_node() == NULL) {
            head->change_nxt_node(temp);
            tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        if (!pos) {
            temp->change_nxt_node(head->get_nxt_node());
            head->get_nxt_node()->change_prev_node(temp);
            head->change_nxt_node(temp);
            temp = NULL;
            return true;
        }
        if (pos == size - 1) {
            temp->change_prev_node(tail->get_prev_node());
            tail->get_prev_node()->change_nxt_node(temp);
            tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        int mid = (size - 1) / 2;
        if (pos + 1 <= mid) {
            prev = head->get_nxt_node();
            for (uint i = 1; i < pos; i++)
                prev = prev->get_nxt_node();
            nxt = prev->get_nxt_node();
        } else {
            nxt = tail->get_prev_node();
            for (uint i = size - 1; i > pos + 1; i--)
                nxt = nxt->get_prev_node();
            prev = nxt->get_prev_node();
        }
        temp->change_nxt_node(nxt);
        temp->change_prev_node(prev);
        prev->change_nxt_node(temp);
        nxt->change_prev_node(temp);
        temp = nxt = prev = NULL;
        return true;
    }
    bool ordered_insert(int info) {
        if (!ordered and size) {
            cout << "ERROR:> List mode = unordered insert. Invalid function." << endl;
            cout << "Try insert(int info)" << endl;
            return false;
        }
        ordered = true;
        Node *temp = new Node(info), *nxt, *prev;
        size++;
        if (head->get_nxt_node() == NULL) {
            head->change_nxt_node(temp);
            tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        nxt = head->get_nxt_node();
        if (nxt->compare(info) == 1) {
            nxt->change_prev_node(temp);
            temp->change_nxt_node(nxt);
            head->change_nxt_node(temp);
            nxt = temp = NULL;
            return true;
        }
        while (nxt != NULL) {
            if (nxt->compare(info) == 1)
                break;
            nxt = nxt->get_nxt_node();
        }
        if (nxt == NULL) {
            temp->change_prev_node(tail->get_prev_node());
            tail->get_prev_node()->change_nxt_node(temp);
            tail->change_prev_node(temp);
            nxt = temp = NULL;
            return true;
        }
        prev = nxt->get_prev_node();
        temp->change_nxt_node(nxt);
        temp->change_prev_node(prev);
        prev->change_nxt_node(temp);
        nxt->change_prev_node(temp);
        temp = nxt = prev = NULL;
        return true;
    }
    bool erase(int pos) {
        if (pos < 0 or pos >= size) {
            cout << "ERROR:> Invalid Position" << endl;
            return false;
        }
        Node *temp, *prev, *nxt;
        size--;
        if (!pos) {
            temp = head->get_nxt_node();
            head->change_nxt_node(temp->get_nxt_node());
            head->get_nxt_node()->clear_prev();
            free(temp);
            return true;
        }
        if (pos == size) {
            temp = tail->get_prev_node();
            tail->change_prev_node(temp->get_prev_node());
            tail->get_prev_node()->clear_nxt();
            free(temp);
            return true;
        }
        int mid = (size + 1) / 2;
        if (pos + 1 <= mid) {
            prev = head->get_nxt_node();
            for (uint i = 1; i < pos; i++)
                prev = prev->get_nxt_node();
            temp = prev->get_nxt_node();
            nxt = temp->get_nxt_node();
        } else {
            nxt = tail->get_prev_node();
            for (uint i = size; i > pos + 1; i--)
                nxt = nxt->get_prev_node();
            temp = nxt->get_prev_node();
            prev = temp->get_prev_node();
        }
        prev->change_nxt_node(nxt);
        nxt->change_prev_node(prev);
        temp->clear();
        free(temp);
        return true;
    }
    bool remove(int info) {
        //TODO
        return false;
    }
};

int main()
{
    srand(time(NULL));
    cout << "TESTS #1" << endl;
    Node n(5);
    Data d = n.get_info();
    cout << d.get_info() << endl;

    stringstream ss;
    ss << 55;
    cout << ss.str() << endl;
    n.clear_nxt();
    n.clear();
    cout << n.to_string() << endl;

    cout << "\nTESTS #2" << endl;
    DoublyList l;
    l.insert(0, 1);
    cout << l.to_string() << endl;

    cout << "\nTESTS #3" << endl;
    DoublyList dl;
    for (int i = 0; i < 6; i++)
        dl.insert(i, i + 1), cout << dl.to_string() << endl;
    cout << dl.to_string() << endl;

    cout << "\nTESTS #4" << endl;
    DoublyList ls;
    ls.insert(0, 1);
    ls.insert(1, 2);
    ls.insert(2, 3);
    cout << ls.to_string() << endl;
    ls.insert(1, 5);
    ls.insert(2, 6);
    cout << ls.to_string() << endl;
    cout << ls.to_string() << endl;

    DoublyList lb;
    lb.insert(0, 1);
    lb.insert(0, 2);
    lb.insert(0, 3);
    lb.insert(3, 4);
    lb.insert(0, 5);
    lb.insert(4, 6);
    cout << lb.to_string() << endl;
    cout << lb.to_string(true) << endl;

    cout << "\nTESTS #5" << endl;

    DoublyList lz;
    for (int i = 10; i >= 1; i--)
        lz.ordered_insert(i), debug(lz.to_string());
    cout << lz.to_string() << endl;
    lz.insert(1, 9);
    lz.ordered_insert(5);
    lz.ordered_insert(20);
    cout << lz.to_string() << endl;
    lz.ordered_insert(-1);
    cout << lz.to_string() << endl;
    cout << lz.search(11) << endl;
    cout << lz.to_string(true) << endl;

    cout << "\nTESTS #6" << endl;
    
    DoublyList ly;
    int r;
    vector<int> v;
    for (int i = 0; i <= 11; i++) {
        r = rand() % 40;
        v.push_back(r);
        ly.insert(i, r);
    }
    cout << "INFO->";
    for (auto i : v)
        cout << " " << i;
    cout << endl;
    cout << ly.to_string() << endl;
    ly.erase(0);
    debug(ly.to_string());
    ly.erase(10);
    debug(ly.to_string());
    ly.erase(8);
    debug(ly.to_string());
    debug(ly.to_string(true));
    ly.erase(1);
    debug(ly.to_string());
    ly.erase(3);
    debug(ly.to_string());
    debug(ly.to_string(true));
    ly.insert(5, 38);
    debug(ly.to_string());
    ly.erase(ly.search(38));
    debug(ly.to_string());

    cout << "\nTESTS #7" << endl;

}