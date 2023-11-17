#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

using namespace std;

template<class T>
class lock_free_stack {
    public:
        struct Node {
            shared_ptr<T> val;
            Node* next;
            Node(T const& _val) : val(make_shared<T>(_val)) {}
        };

        void push(T const& val) {
            Node* const newNode = new Node(val);
            newNode->next = head.load();
            while(!head.compare_exchange_weak(newNode->next, newNode));
        }

        shared_ptr<T> pop() {
            Node *tmp = head.load();
            while(tmp && !head.compare_exchange_weak(tmp, tmp->next));
            return tmp ? tmp->val : shared_ptr<T>();
        }

        void dump() {
            Node *tmp = head;
            while (tmp != nullptr) {
                cout << "Val = " << *tmp->val << endl;
                tmp = tmp->next;
            }
        }

        lock_free_stack() = default;
        ~lock_free_stack() = default;

    private:
        atomic<Node*> head = nullptr;
};

//! This can be a wrapper to interface/operate on stack for the given values from a thread context
void stackOper(lock_free_stack<int>& obj, vector<int> vals) {
    for (auto val : vals) {
        obj.push(val);
    }
    obj.dump();

    auto res = obj.pop();
    cout << "Popped Stack Value= " << *res << endl;

}

int main() {
    lock_free_stack<int> stackObj;
    thread th0([&]() {
        vector<int> a1 = {10, 20, 30, 40};
        stackOper(stackObj, a1);
    });

    thread th1([&]() {
        vector<int> a2 = {1, 2, 3, 4, 5};
        stackOper(stackObj, a2);
    });
    th0.join();
    th1.join();
}