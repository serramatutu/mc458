#include <iostream>
#include <vector>
#include <stack>

class Mobile {
    public: 
        size_t l_weight;
        size_t l_distance;
        size_t r_weight;
        size_t r_distance;

        Mobile(size_t l_weight, size_t l_distance, size_t r_weight, size_t r_distance);

        size_t weight() const;
        bool balanced() const;
};

Mobile::Mobile(size_t l_weight, size_t l_distance, size_t r_weight, size_t r_distance) {
    this->r_weight = r_weight;
    this->r_distance = r_distance;
    this->l_weight = l_weight;
    this->l_distance = l_distance;
}

size_t Mobile::weight() const {
    return l_weight + r_weight;
}

bool Mobile::balanced() const {
    return l_weight * l_distance == r_weight * r_distance;
}

void read_input(std::stack<Mobile, std::vector<Mobile> >& stack, size_t mobile_count) {
    for (size_t i = 0; i < mobile_count; i++) {
        size_t r_weight, r_distance, l_weight, l_distance;
        std::cin >> l_weight >> l_distance >> r_weight >> r_distance;
        stack.push(Mobile(l_weight, l_distance, r_weight, r_distance));
    }
}

bool is_balanced(std::stack<Mobile, std::vector<Mobile> > stack) {
    std::stack<size_t> weights_stack;
    
    while (!stack.empty()) {
        Mobile m(stack.top());

        if (m.l_weight == 0) {
            m.l_weight = weights_stack.top();
            weights_stack.pop();
        }
        if (m.r_weight == 0) {
            m.r_weight = weights_stack.top();
            weights_stack.pop();
        }

        if (!m.balanced()) {
            return false;
        }

        weights_stack.push(m.weight());
        stack.pop();
    }

    return true;
}

int main() {
    size_t mobile_count;
    std::cin >> mobile_count;

    std::vector<Mobile> stack_backend;
    stack_backend.reserve(mobile_count);
    std::stack<Mobile, std::vector<Mobile> > stack(stack_backend);

    read_input(stack, mobile_count);

    std::cout << (is_balanced(stack) ? 'S' : 'N') << std::endl;

    return 0;
}