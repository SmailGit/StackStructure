#include <iostream>

template<typename T>
class tstack {
    struct node {
        T     val;
        node* next;
    };
private:
    node* stk;
    size_t cnt;
public:
    tstack(void) :stk(NULL), cnt(0) {}
    tstack(const tstack&);
    ~tstack() {
        this->clear();
    }
public:
    bool push(const T& val) {
        node* p = new (std::nothrow) node();
        if (p != NULL) {
            p->val = val;
            p->next = stk;
            stk = p;
            ++cnt;
        }
        return (p != NULL);
    }

    void pop(void) {
        node* t = stk;
        if (t != NULL) {
            stk = stk->next;
            delete t;
            --cnt;
        }
    }

    template<typename Cmp>
    void remove(Cmp cmp) {
        node* t, * p = stk, * r = stk;
        while (p != NULL) {
            if (cmp(p->val)) {
                if (p == stk) {
                    stk = stk->next;
                    r = t = stk;
                }
                else
                    t = r->next = p->next;
                --cnt;
                delete p;
                p = t;
            }
            else {
                r = p;
                p = p->next;
            }
        }
    }

    T& top(void) const { return stk->val; }
    T& top(void) { return stk->val; }

    bool empty(void) const {
        return (stk == NULL);
    }

    size_t size(void) const {
        return cnt;
    }

    void clear(void) {
        node* t;
        while (stk != NULL) {
            t = stk;
            stk = stk->next;
            delete t;
        }
        cnt = 0;
    }
};


struct lpcmp {
    bool operator () (const int n) const {
        int i = n % 10;
        if (i < 0)
            i = 0 - i;
        return (i == 5);
    }
};

int main(void) {
    tstack<int> st;
    int a[] = { 995, -325, 10, 2, 15, 335, -55, 24, 75, 50, 45 };
    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
        st.push(a[i]);

    st.remove(lpcmp());
    std::cout << "count: " << st.size() << std::endl;

    while (!st.empty()) {
        std::cout << st.top() << ' ';
        st.pop();
    }
    return 0;
}