#include <bits/stdc++.h>

using namespace std;

#define debug(x) cout << "DEBUG# " << x << endl;

void tests();

template<class T>
struct Data {
//Constructors
    Data() {}
    Data(const T &info) : info(info) {}
//Methods
    //Const methods
    T get_info() const{
        return this->info;
    }
    string to_string() const{
        stringstream ss;
        ss << this->info;
        return ss.str();
    }
    //Non-const methods
    void set_info(const T &info) {
        this->info = info;
    }

private:
//Data-Properties
    T info;
};

template<class T>
class Node {
//Data-Properties
    Data<T> info;
    Node<T> *prev, *nxt;

public:
//Constructors-Destructors
    Node() : info(), prev(NULL), nxt(NULL) {}
    Node(const T &info) : info(info), prev(NULL), nxt(NULL) {}
    ~Node() {}
//Methods
    //Const methods
    Data<T> get_info() const{
        return this->info;
    }
    Node<T> *get_prev_node() const{
        return this->prev;
    }
    Node<T> *get_nxt_node() const{
        return this->nxt;
    }
    int compare(const T &y) const{
        const T x = this->info.get_info();
        return (x > y ? 1 : x < y ? -1 : 0);
    }
    string to_string() const{
        return this->info.to_string();
    }
    //Non-const methods
    void change_prev_node(Node<T> *prev) {
        this->prev = prev;
    }
    void change_nxt_node(Node<T> *nxt) {
        this->nxt = nxt;
    }
    void clear() {
        clear_prev(), clear_nxt();
    }
    void clear_nxt() {
        this->nxt = NULL;
    }
    void clear_prev() {
        this->prev = NULL;
    }
};

template<class T>
class DoublyList {
//Data-Properties
    Node<T> *head, *tail;    
    uint size;
    bool ordered;

public:
//Constructors-Destructors
    DoublyList() : head(new Node<T>), tail(new Node<T>), size(0), ordered(false) {}
    DoublyList(vector<T>) {
        //TODO
    }
    DoublyList(const DoublyList<T> &copy) {
        //TODO: copy constructor
    }
    ~DoublyList() {
        Node<T> *cur;
        while (this->head != NULL) {
            cur = this->head;
            this->head = this->head->get_nxt_node();
            cur->clear();
            free(cur);
        }
        this->tail->clear();
        free(this->tail);
    }
//Methods
    //Const methods
    /**
     * Return all elements of the Doubly Linked List with string format. The default format is: 
     * "INFO-> x1 x2 ... xn".
     * 
     * If the parameter reverse is "true", the elements follow the reverse format:
     * "INFO-> xn ... x2 x1".
     * 
     * If the Doubly Linked List is empty, the function returns an empty string and a message: "WARNING:> Empty List.".
    */ 
    string to_string(bool reverse = false) const{
        if (this->head->get_nxt_node() == NULL) {
            return "WARNING:> Empty List.";
        }
        Node<T> *cur;
        string infos;
        infos += "INFO->";
        if (reverse) {
            cur = this->tail;
            while (true) {
                cur = cur->get_prev_node();
                if (cur == NULL)
                    break;
                infos += " " + cur->to_string();
            }
            return infos;
        }
        cur = this->head;
        while (true) {
            cur = cur->get_nxt_node();
            if (cur == NULL)
                break;
            infos += " " + cur->to_string();
        }
        return infos;
    }
    /**
     * Search an element passed by parameter and returns the index of this element, if this element
     * was not found the function return -1.
     * 
     * If the Doubly Linked List is empty, the function returns -1 and a message: "WARNING:> Empty List.".
    */ 
    int search(const T &info) const{
        if (this->head->get_nxt_node() == NULL) {
            cout << "WARNING:> Empty List." << endl;
            return -1;
        }
        Node<T> *temp = this->head->get_nxt_node();
        uint cnt = -1;
        while (temp != NULL) {
            if (temp->compare(info) == 1 and ordered) {
                temp = NULL;
                return -1;
            }
            else if (!temp->compare(info)) {
                temp = NULL;
                return ++cnt;
            }
            cnt++;
            temp = temp->get_nxt_node();
        }
        temp = NULL;
        return -1;
    }
    /**
     * Returns size of the Doubly Linked List.
    */ 
    uint get_size() const{
        return this->size;
    }
    /**
     * Returns "true" for an empty Doubly Linked List, else returns "false".
    */
    bool empty() const{
        return !this->size;
    }
    //Non-const methods
    /**
     * Insert the value passed by parameter at the "pos" position
     * 
     * The function returns "true" if the element has successfully inserted, else returns "false".
     * 
     * If the list are in ordered mode (only elements can be inserted with ordered fuction), the
     * function returns "false" and two messages: "ERROR:> List mode = ordered insert. Invalid function." and "Try ordered_insert(const T &info)".
    */
    bool insert(uint pos, const T &info) {
        if (ordered) {
            cout << "ERROR:> List mode = ordered insert. Invalid function." << endl;
            cout << "Try ordered_insert(const T &info)" << endl;
            return false;
        }
        if (pos < 0 or pos > this->size) {
            cout << "ERROR:> invalid position." << endl;
            return false;
        }
        Node<T> *temp = new Node<T>(info), *prev, *nxt;
        this->size++;
        if (this->head->get_nxt_node() == NULL) {
            this->head->change_nxt_node(temp);
            this->tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        if (!pos) {
            temp->change_nxt_node(this->head->get_nxt_node());
            this->head->get_nxt_node()->change_prev_node(temp);
            this->head->change_nxt_node(temp);
            temp = NULL;
            return true;
        }
        if (pos == this->size - 1) {
            temp->change_prev_node(this->tail->get_prev_node());
            this->tail->get_prev_node()->change_nxt_node(temp);
            this->tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        const uint mid = (this->size - 1) / 2;
        if (pos + 1 <= mid) {
            prev = this->head->get_nxt_node();
            for (uint i = 1; i < pos; i++)
                prev = prev->get_nxt_node();
            nxt = prev->get_nxt_node();
        } else {
            nxt = this->tail->get_prev_node();
            for (uint i = this->size - 1; i > pos + 1; i--)
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
    /**
     * Insert the value passed by parameter in order
     * 
     * The function returns "true" if the element has successfully inserted, else returns "false".
     * 
     * If the list are not in ordered mode (only elements can be inserted with ordered fuction), the
     * function returns "false" and two messages: "ERROR:> List mode = unordered insert. Invalid function." and "Try insert(int pos, const T &info)".
    */
    bool ordered_insert(const T &info) {
        if (!ordered and this->size) {
            cout << "ERROR:> List mode = unordered insert. Invalid function." << endl;
            cout << "Try insert(int pos, const T &info)" << endl;
            return false;
        }
        ordered = true;
        Node<T> *temp = new Node<T>(info), *nxt, *prev;
        this->size++;
        if (this->head->get_nxt_node() == NULL) {
            this->head->change_nxt_node(temp);
            this->tail->change_prev_node(temp);
            temp = NULL;
            return true;
        }
        nxt = this->head->get_nxt_node();
        if (nxt->compare(info) == 1) {
            nxt->change_prev_node(temp);
            temp->change_nxt_node(nxt);
            this->head->change_nxt_node(temp);
            nxt = temp = NULL;
            return true;
        }
        while (nxt != NULL) {
            if (nxt->compare(info) == 1)
                break;
            nxt = nxt->get_nxt_node();
        }
        if (nxt == NULL) {
            temp->change_prev_node(this->tail->get_prev_node());
            this->tail->get_prev_node()->change_nxt_node(temp);
            this->tail->change_prev_node(temp);
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
    /**
     * Erase one element in the position passed by parameter.
     * 
     * The function returns "true" if the element has successfully erased, else returns "false".
     * 
     * If the Doubly Linked List is empty, the function returns "false" and a message: "WARNING:> Empty List.".
     * 
     * The same happens if the position passed by parameter is out of the bounds, the function returns "false" and a message: "ERROR:> Invalid Position.".
    */  
    bool erase(const int &pos) {
        if (this->head->get_nxt_node() == NULL) {
            cout << "WARNING:> Empty List." << endl;
            return false;
        }
        if (pos < 0 or pos >= this->size) {
            cout << "ERROR:> Invalid Position." << endl;
            return false;
        }
        Node<T> *temp, *prev, *nxt;
        this->size--;
        if (!pos) {
            temp = this->head->get_nxt_node();
            this->head->change_nxt_node(temp->get_nxt_node());
            if (this->size)
                this->head->get_nxt_node()->clear_prev();
            temp->clear();
            free(temp);
            return true;
        }
        if (pos == this->size) {
            temp = this->tail->get_prev_node();
            this->tail->change_prev_node(temp->get_prev_node());
            if (this->size)
                this->tail->get_prev_node()->clear_nxt();
            temp->clear();
            free(temp);
            return true;
        }
        const uint mid = (this->size + 1) / 2;
        if (pos + 1 <= mid) {
            prev = this->head->get_nxt_node();
            for (uint i = 1; i < pos; i++)
                prev = prev->get_nxt_node();
            temp = prev->get_nxt_node();
            nxt = temp->get_nxt_node();
        } else {
            nxt = this->tail->get_prev_node();
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
    /**
     * Remove all elemets that is equals info.
     * 
     * The function returns "true" if the element has successfully removed, else returns "false".
     * 
     * If the Doubly Linked List is empty, the function returns "false" and a message: "WARNING:> Empty List.".
    */ 
    bool remove(const T &info) {
        if (this->head->get_nxt_node() == NULL) {
            cout << "WARNING:> Empty List." << endl;
            return false;
        }
        Node<T> *temp = this->head->get_nxt_node(), *nxt, *prev;
        bool removed = false;
        while (temp != NULL) {
            if (temp->compare(info) == 1 and ordered and removed)
                return true;
            else if (temp->compare(info) == 1 and ordered and !removed)
                return false;
            if (!temp->compare(info) and temp->get_prev_node() == NULL) {
                erase(0);
                temp = this->head->get_nxt_node();
                removed = true;
            } else if (!temp->compare(info) and temp->get_nxt_node() == NULL) {
                erase(this->size - 1);
                removed = true;
                return true;
            } else if (!temp->compare(info)) {
                this->size--;
                prev = temp->get_prev_node();
                nxt = temp->get_nxt_node();
                prev->change_nxt_node(nxt);
                nxt->change_prev_node(prev);
                temp->clear();
                free(temp);
                temp = nxt;
                removed = true;
            } else
                temp = temp->get_nxt_node();
        }
        return removed;
    }
    /**
     * Erase all elements and free the heap memory allocation, except the pointers head and tail are untouched.
    */
    void clear() {
        Node<T> *cur = this->head->get_nxt_node(), *temp;
        while (cur != NULL) {
            temp = cur;
            cur = cur->get_nxt_node();
            temp->clear();
            free(temp);
        }
        this->head->clear();
        this->tail->clear();
        this->size = 0;
    }
    //New functions
    bool push_back(const T &info) {
        //TODO: adds a new element info at the beginning of the list.
    }
    bool push_front(const T &info) {
        //TODO: adds a new element info at the end of the list.
    }
    T get(const int &pos) {
        //TODO: returns the element at the position pos.
    }
    int front() {
        //TODO: returns the first element of the list.
    }
    int back() {
        //TODO: returns the last element of the list.
    }
};

int main()
{
    /*Functions
    All functions are commenteds.
    Just create an object and type '.' to view the functions and comments.
    Ex.:
    DoublyList<Type{basic data types, string}> L;
    L.
    */
    //tests();
}

void tests() 
{
    srand(time(NULL));
    cout << "TESTS #1" << endl;

    Node<int> n(5);
    Data<int> d = n.get_info();
    cout << d.get_info() << endl;

    stringstream ss;
    ss << 55;
    cout << ss.str() << endl;
    n.clear_nxt();
    n.clear();
    cout << n.to_string() << endl;

    cout << "\nTESTS #2" << endl;
    DoublyList<int> l;
    l.insert(0, 1);
    l.clear();
    cout << l.to_string() << endl;

    cout << "\nTESTS #3" << endl;
    DoublyList<int> dl;
    for (int i = 0; i < 6; i++)
        dl.insert(i, i + 1), cout << dl.to_string() << endl;
    cout << dl.to_string() << endl;
    dl.clear();

    cout << "\nTESTS #4" << endl;
    DoublyList<int> ls;
    ls.insert(0, 1);
    ls.insert(1, 2);
    ls.insert(2, 3);
    cout << ls.to_string() << endl;
    ls.insert(1, 5);
    ls.insert(2, 6);
    cout << ls.to_string() << endl;
    cout << ls.to_string() << endl;
    ls.clear();

    DoublyList<int> lb;
    lb.insert(0, 1);
    lb.insert(0, 2);
    lb.insert(0, 3);
    lb.insert(3, 4);
    lb.insert(0, 5);
    lb.insert(4, 6);
    cout << lb.to_string() << endl;
    cout << lb.to_string(true) << endl;
    lb.clear();

    cout << "\nTESTS #5" << endl;
    DoublyList<int> lz;
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
    lz.clear();

    cout << "\nTESTS #6" << endl;
    DoublyList<int> ly;
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
    ly.clear();

    cout << "\nTESTS #7" << endl;
    DoublyList<int> lq;
    v.clear();
    for (int i = 0; i < 20; i++) {
        v.push_back(2);
        lq.insert(i, 2);
    }
    cout << "INFO->";
    for (auto i : v)
        cout << " " << i;
    cout << endl; 
    cout << lq.to_string() << endl;
    cout << lq.get_size() << endl;
    //lq.insert(0, 1);
    lq.remove(2);
    cout << " ok " << endl;
    cout << lq.to_string() << endl;
    cout << lq.get_size() << endl;
    cout << lq.to_string(true) << endl;
    lq.erase(0);
    cout << lq.to_string() << endl;
    lq.clear();

    cout << "\nTESTS #8" << endl;
    DoublyList<int> ll;
    r;
    for (int i = 0; i < 10; i++) {
        r = rand() % 20;
        ll.ordered_insert(r);
    }
    cout << ll.to_string() << endl;
    cout << ll.get_size() << endl;
    cout << ll.to_string(true) << endl;

    cout << "\nTESTS #9" << endl;
    DoublyList<string> listS;
    listS.ordered_insert("teste1");
    listS.ordered_insert("teste3");
    listS.ordered_insert("teste2");
    cout << listS.to_string() << endl;
    listS.erase(listS.search("teste1"));
    cout << listS.to_string() << endl;
    listS.insert(0, "dsd");

    DoublyList<double> ldouble;
    ldouble.ordered_insert(1.1);
    ldouble.ordered_insert(1.0);
    ldouble.ordered_insert(0.9);
    ldouble.ordered_insert(1.3);
    ldouble.erase(ldouble.search(0.9));
    ldouble.ordered_insert(1.12);
    cout << ldouble.to_string() << endl;

    DoublyList<char> listchar;
    listchar.ordered_insert('a');
    listchar.ordered_insert('0');
    listchar.ordered_insert('c');
    listchar.ordered_insert('b');
    cout << listchar.to_string() << endl;
}