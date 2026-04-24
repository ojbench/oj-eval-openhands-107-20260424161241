

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

namespace LIST
{
    struct NODE {
        int data;
        NODE *next;
    };

    NODE *head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    NODE* move(int i) {
        if (len == 0) return nullptr;
        NODE *curr = head;
        for (int j = 0; j < i; ++j) {
            curr = curr->next;
        }
        return curr;
    }

    void insert(int i, int x) {
        NODE *newNode = new NODE{x, nullptr};
        if (len == 0) {
            newNode->next = newNode;
            head = newNode;
        } else {
            if (i == 0) {
                NODE *tail = move(len - 1);
                newNode->next = head;
                tail->next = newNode;
                head = newNode;
            } else {
                NODE *prev = move(i - 1);
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }
        len++;
    }

    void remove(int i) {
        if (len == 0) return;
        NODE *toDelete;
        if (len == 1) {
            toDelete = head;
            head = nullptr;
        } else {
            if (i == 0) {
                NODE *tail = move(len - 1);
                toDelete = head;
                head = head->next;
                tail->next = head;
            } else {
                NODE *prev = move(i - 1);
                toDelete = prev->next;
                prev->next = toDelete->next;
            }
        }
        delete toDelete;
        len--;
    }

    void remove_insert(int i) {
        if (len == 0) return;
        int val;
        // Get value at i
        NODE *curr = move(i);
        val = curr->data;
        
        // Remove at i
        remove(i);
        
        // Insert at end (which is position len)
        insert(len, val);
    }

    void get_length() {
        cout << len << endl;
    }

    void query(int i) {
        if (i >= len || i < 0) {
            cout << -1 << endl;
            return;
        }
        NODE *curr = move(i);
        cout << curr->data << endl;
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << endl;
            return;
        }
        int maxVal = head->data;
        NODE *curr = head->next;
        for (int i = 1; i < len; ++i) {
            maxVal = max(maxVal, curr->data);
            curr = curr->next;
        }
        cout << maxVal << endl;
    }

    void clear() {
        if (len == 0) return;
        NODE *curr = head;
        for (int i = 0; i < len; ++i) {
            NODE *next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        len = 0;
    }
}

int n;
int main()
{
    if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        if (!(cin >> op)) break;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}

