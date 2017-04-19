#include <iostream>

struct Node {
 public:
    Node(int data, Node* next) : data_(data), next_(next) {}

    Node() {}

    int& data() {
        return data_;
    }

    Node*& next() {
        return next_;
    }

 private:
    int data_;
    Node *next_;
};

struct List {
 public:
    List(int data_) : size_(1), head_(new Node(data_, NULL)) {}

    List() : size_(0), head_(NULL) {}

    int& size() {
        return size_;
    }

    Node*& head() {
        return head_;
    }

    void PrintList() {
        auto current = head();
        for (int i = 0; i < size(); ++i) {
            std::cout << current->data() << " ";
            current = current->next();
        }
    }

    void DeleteList() {
        for (int i = 0; i < size(); ++i) {
            auto current = head();
            head() = head()->next();
            delete current;
        }
    }

 private:
    int size_;
    Node *head_;
};

void Split(List& left, List& right, int size) {
    for (int i = 0; i < size - 1; ++i)
        right.head() = right.head()->next();
    auto tmp = right.head();
    right.head() = right.head()->next();
    tmp->next() = NULL;
    left.size() = size;
    right.size() -= size;
}

List Merge(List left, List right) {
    List answer;
    answer.size() = left.size() + right.size();
    int cur_left = 0, cur_right = 0;
    if (left.head()->data() < right.head()->data()) {
        ++cur_left;
        answer.head() = left.head();
        left.head() = left.head()->next();
    } else {
        ++cur_right;
        answer.head() = right.head();
        right.head() = right.head()->next();
    }
    Node* current = answer.head();
    while (cur_left < left.size() && cur_right < right.size()) {
        if (left.head()->data() < right.head()->data()) {
            auto tmp = left.head()->next();
            current->next() = left.head();
            current = current->next();
            left.head() = tmp;
            ++cur_left;
        } else {
            auto tmp = right.head()->next();
            current->next() = right.head();
            current = current->next();
            right.head() = tmp;
            ++cur_right;
        }
    }
    if (left.head() == NULL) {
        current->next() = right.head();
    } else {
        current->next() = left.head();
    }
    return answer;
}

void MergeSort(List& list) {
    if (list.size() <= 1)
        return;

    auto right = list;
    Split(list, right, list.size() / 2);

    MergeSort(list);
    MergeSort(right);

    list = Merge(list, right);
}

List FillList() {
    int number_of_elements;
    std::cin >> number_of_elements;
    int data;
    std::cin >> data;
    List list(data);
    auto current = list.head();
    for (int i = 1; i < number_of_elements; ++i) {
        std::cin >> data;
        current->next() = new Node();
        current = current->next();
        current->data() = data;
        current->next() = NULL;
        ++list.size();
    }
    return list;
}

int main() {
    List list = FillList();
    MergeSort(list);
    list.PrintList();
    list.DeleteList();
    int n;
    std::cin >> n;
}
