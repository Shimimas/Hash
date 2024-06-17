#ifndef LINKED_HASH_SET_H
#define LINKED_HASH_SET_H

#include <iostream>

class linkedhs {
    private:
        typedef struct student {
            public:
                unsigned age = 0;
                std::string name = "";

                struct student * next = nullptr;
                struct student * prv = nullptr;

                student(const unsigned age, const std::string name) : age(age), name(name) {};
                bool operator==(const student &other) const;
                bool operator!=(const student &other) const;
                long long hash() const;
        } element_t;

        class ListOfStudent_ {
            private:
                element_t * head_ = nullptr;
                element_t * tail_ = nullptr;
                int amount_ = 0;

                bool begin_ = false;
                bool end_ = false;

            public:
                ListOfStudent_() {};
                ~ListOfStudent_() {clear();};

                int size();
                void pushBack(const element_t element);
                element_t * getElement(const int i);
                void remove(const int i);
                void clear();

                bool getEnd() {return end_;};
                void setEnd(bool end) {end_ = end;};

                bool getBegin() {return begin_;};
                void setBegin(bool begin) {begin_ = begin;};
        };

        void memoryAllocated_(int size);
        void copy_(const linkedhs &other);
        bool compare_(const linkedhs &other) const;

        bool rehashCheck_();
        void rehash_();

        void emptyCheck();

        std::pair<int, int> find_(const element_t &e) const;

        ListOfStudent_ * hashArray_;
        ListOfStudent_ order_;

        int tableSize_ = 0;
        int amount_ = 0;
        
    public:
        class iterator {
            private:
                ListOfStudent_ * row_;
                element_t * element_;

                void emptyCheck();

            public:
                iterator(ListOfStudent_ * row, element_t * element) : row_(row), element_(element) {};
                element_t &operator*();
                iterator operator++();
                iterator operator--();
                bool operator==(const iterator &other) const;
                bool operator!=(const iterator &other) const;
        };

        linkedhs() {};
        linkedhs(const int size) {memoryAllocated_(size);};
        linkedhs(const linkedhs &other) {copy_(other);};
        ~linkedhs() {clear();};
        
        linkedhs &operator=(const linkedhs &other);

        void insert(const element_t &e);
        bool remove(const element_t &e);

        void swap(linkedhs &other);
        size_t size() const;
        bool empty() const;

        bool contains(const element_t &e) const;
        iterator find(const element_t &e) const;

        bool operator==(const linkedhs &other) const;
        bool operator!=(const linkedhs &other) const;

        iterator begin();
        iterator end();

        void clear();
};

#endif //LINKED_HASH_SET_H