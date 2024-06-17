#include "LinkedHashSet.h"

long long linkedhs::student::hash() const {
    long long h = 0;
    int p = 31;
    for (char c : name) {
        h += (c - 'a' + 1) * p;
        p *= 31;
    }
    h = p * h + age;
    return abs(h);
}

bool linkedhs::student::operator==(const student &other) const {
    return this->age == other.age && this->name == other.name;
}

bool linkedhs::student::operator!=(const student &other) const {
    return this->age != other.age || this->name != other.name;
}

int linkedhs::ListOfStudent_::size() {
    return amount_;
}

void linkedhs::ListOfStudent_::clear() {
    while (head_ != nullptr) {
        element_t * tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
    amount_ = 0;
}

void linkedhs::ListOfStudent_::pushBack(const element_t element) {
    element_t * newElement = new element_t(element.age, element.name);
    if (amount_ == 0) {
        head_ = newElement;
        tail_ = newElement;
    } else {
        tail_->next = newElement;
        newElement->prv = tail_;
        tail_ = newElement;
    }
    amount_++;
}

void linkedhs::ListOfStudent_::remove(const int i) {
    element_t * element = getElement(i);
    if (element == head_ && element == tail_) {
        head_ = nullptr;
        tail_ = nullptr;
    } else if (element == head_) {
        head_ = head_->next;
        head_->prv = nullptr;
    } else if (element == tail_) {
        tail_ = tail_->prv;
        tail_->next = nullptr;
    } else {
        element->prv->next = element->next;
        element->next->prv = element->prv;
    }
    amount_--;
    delete element;
}

linkedhs::element_t * linkedhs::ListOfStudent_::getElement(int i) {
    element_t * tmp = head_;
    while (i-- && tmp) {
        tmp = tmp->next;
    }
    return tmp;
}

void linkedhs::memoryAllocated_(const int size) {
    hashArray_ = new ListOfStudent_[size];
    tableSize_ = size;
    hashArray_[size - 1].setEnd(true);
    hashArray_[0].setBegin(true);
}

void linkedhs::copy_(const linkedhs &other) {
    if (this != &other) {
        clear();
        memoryAllocated_(other.tableSize_);
        tableSize_ = other.tableSize_;
        amount_ = other.amount_;
        for (int i = 0; i < tableSize_; i++) {
            for (int j = 0; j < other.hashArray_[i].size(); j++) {
                hashArray_[i].pushBack(*other.hashArray_[i].getElement(j));
            }
        }
    }
}

linkedhs& linkedhs::operator=(const linkedhs &other) {
    copy_(other);
    return *this;
}

size_t linkedhs::size() const {
    return amount_;
}

bool linkedhs::empty() const {
    return amount_ > 0 ? false : true;
}

void linkedhs::insert(const element_t &e) {
    if (tableSize_ == 0) {
        memoryAllocated_(1);
    }
    hashArray_[e.hash() % tableSize_].pushBack(e);
    amount_++;
    if (rehashCheck_()) {
        rehash_();
    }
    order_.clear();
    for (int i = 0; i < tableSize_; i++) {
        for (int j = 0; j < hashArray_[i].size(); j++) {
            order_.pushBack(*hashArray_[i].getElement(j));
        }
    } 
}

bool linkedhs::rehashCheck_() {
    bool result = false;
    if (amount_ >= (4 * tableSize_) / 3.0) {
        result = true;
    }
    return result;
}

void linkedhs::rehash_() {
    int newSize = tableSize_ * 2;
    ListOfStudent_ * hashArray_tmp = new ListOfStudent_[newSize];
    for (int i = 0; i < tableSize_; i++) {
        for (int j = 0; j < hashArray_[i].size(); j++) {
            hashArray_tmp[hashArray_[i].getElement(j)->hash() % newSize].pushBack(*hashArray_[i].getElement(j));
        }
    }
    delete [] hashArray_;
    hashArray_ = hashArray_tmp;
    tableSize_ = newSize;
}

void linkedhs::swap(linkedhs &other) {
    std::swap(other.hashArray_, hashArray_);
    std::swap(other.tableSize_, tableSize_);
    std::swap(other.amount_, amount_);
}

bool linkedhs::compare_(const linkedhs &other) const {
    bool result = true;
    if (amount_ != other.amount_) {
        result = false;
    } else if (tableSize_ != other.tableSize_) {
        result = false;
    } else {
        for (int i = 0; i < tableSize_; i++) {
            for (int j = 0; j < hashArray_[i].size(); j++) {
                if (*hashArray_[i].getElement(j) != *other.hashArray_[i].getElement(j)) {
                    result = false;
                }
            }
        }
    }
    return result;
}

bool linkedhs::operator==(const linkedhs &other) const {
    return compare_(other);
}

bool linkedhs::operator!=(const linkedhs &other) const {
    return compare_(other) ? false : true;
}

void linkedhs::clear() {
    for (int i = 0; i < tableSize_; i++) {
        hashArray_[i].clear();
    }
    if (tableSize_ != 0) {
        delete [] hashArray_;
    }
    amount_ = 0;
    tableSize_ = 0;
}

linkedhs::iterator linkedhs::begin() {
    emptyCheck();
    int i = 0;
    while (!hashArray_[i].size() && i < tableSize_) {
        i++;
    }
    return iterator(&hashArray_[i], hashArray_[i].getElement(0));
}

linkedhs::iterator linkedhs::end() {
    emptyCheck();
    return iterator(&hashArray_[tableSize_ - 1], nullptr);
}

void linkedhs::emptyCheck() {
    if (empty()) {
        throw std::out_of_range("Container is empty!");
    }
}

void linkedhs::iterator::emptyCheck() {
    if (!row_ && !element_) {
        throw std::out_of_range("Container is empty!");
    }
}

linkedhs::element_t &linkedhs::iterator::operator*() {
    emptyCheck();
    return *element_;
}

linkedhs::iterator linkedhs::iterator::operator++() {
    emptyCheck();
    if (element_->next) {
        element_ = element_->next;
    } else if (!row_->getEnd()) {
        while (!(++row_)->size()) {;}
        element_ = row_->getElement(0);
    }
    return iterator(row_, element_);
}

linkedhs::iterator linkedhs::iterator::operator--() {
    emptyCheck();
    if (element_->prv) {
        element_ = element_->prv;
    } else if (!row_->getBegin()) {
        while (!(--row_)->size()) {;}
        element_ = row_->getElement(row_->size() - 1);
    }
    return iterator(row_, element_);
}

bool linkedhs::iterator::operator==(const iterator &other) const {
    return other.element_ == element_ ? true : false;
}

bool linkedhs::iterator::operator!=(const iterator &other) const {
    return other.element_ != element_ ? true : false;
}

std::pair<int, int> linkedhs::find_(const element_t &e) const {
    std::pair<int, int> result(-1, -1);
    for (int i = 0; i < tableSize_; i++) {
        for (int j = 0; j < hashArray_[i].size(); j++) {
            if (*hashArray_[i].getElement(j) == e) {
                result.first = i;
                result.second = j;
                break;
            }
        }
    }
    return result;
}

linkedhs::iterator linkedhs::find(const element_t &e) const {
    std::pair<int, int> result = find_(e);
    return result.first != -1 ? iterator(&hashArray_[result.first], hashArray_[result.first].getElement(result.second)) : iterator(nullptr, nullptr);
}

bool linkedhs::contains(const element_t &e) const {
    return find_(e).first != -1 ? true : false;
}

bool linkedhs::remove(const element_t &e) {
    std::pair<int, int> result = find_(e);
    if (result.first != -1) {
        hashArray_[result.first].remove(result.second);
        amount_--;
        order_.clear();
        for (int i = 0; i < tableSize_; i++) {
            for (int j = 0; j < hashArray_[i].size(); j++) {
                order_.pushBack(*hashArray_[i].getElement(j));
            }
        } 
    }
    return result.first != -1 ? true : false;
}