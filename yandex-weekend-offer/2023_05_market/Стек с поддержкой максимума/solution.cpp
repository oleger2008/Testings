#include <iostream>
#include <string_view>
#include <string>
#include <list>

using namespace std;

namespace {
using Command = string_view;
const Command getMax("max");
const Command push("push");
const Command pop("pop");
}

struct Element {
    int num = 0;
    int curMax = 0;

    Element(const int n, const int max)
    : num(n)
    , curMax((n > max) ? n : max) {
    }
};

class Stack {
public:
    explicit Stack(ostream &os)
    : container_()
    , os_(os) {}

    void push(const int num) {
        if (container_.empty()) {
            container_.emplace_front(num, num);
            return;
        }

        const int curMax = container_.front().curMax;
        container_.emplace_front(num, curMax);
    }

    void pop() {
        if (container_.empty()) {
            os_ << "error\n"s;
            return;
        }
        container_.erase(container_.begin());
    }

    void getMax() const {
        if (container_.empty()) {
            os_ << "None\n"s;
            return;
        }
        os_ << container_.front().curMax << "\n"s;
    }

private:
    list<Element> container_;
    ostream &os_;
};

void Solution(istream &is, ostream &os) {
    size_t n = 0u;
    is >> n;

    Stack stack(os);
    for (size_t i = 0u; i < n; ++i) {
        string command;
        is >> command;
        if (command == push) {
            int elem = 0u;
            is >> elem;
            stack.push(elem);
        } else if (command == pop) {
            stack.pop();
        } else if (command == getMax) {
            stack.getMax();
        }
    }
}

int main() {
    Solution(cin, cout);
    return 0;
}
