#include <iostream>
#include <list>
#include <vector>

struct student
{
private:
    unsigned age_;
    std::string name_;
    
public:
    student(const unsigned age, const std::string name)
    {
        age_ = age; name_ = name;
    }
    
    bool operator == (const student &other) const
    {
        return (this -> age_ == other.age_ && this -> name_ == other.name_);
    }
    
    long long hash() const
    {
        long long h = 0;
        int p = 31;
        for (char c : name_)
        {
            h += (c - 'a' + 1) * p;
            p *= 31;
        }
        h = p * h + age_;
        return abs(h);
    }
    
};

typedef student element;

class linkedhs
{
private:
    
    std::vector <std::list <element>> elements_;
    
public:
    int amount_;
    class iterator
    {
    public:
        element operator * ();
        iterator operator ++ (int);
        iterator operator -- ();
        bool operator == (const iterator &other) const;
        bool operator != (const iterator &other) const;

    };

    linkedhs ()
    {
        amount_ = 10;
        elements_.resize(amount_);
    }
    
    linkedhs (const int amount)
    {
        this -> amount_ = amount;
        elements_.resize(amount_);
    }
    
    linkedhs (const linkedhs &other)
    {
        int prev_amount_ = amount_;
        this -> amount_ = other.amount_;
        if (prev_amount_  != amount_) this -> elements_.resize(amount_);
        
        for (int i = 0; i < amount_; i++)
        {
            this -> elements_.at(i) = other.elements_.at(i);
        }
        
    }
    
    linkedhs &operator = (const linkedhs &other)
    {
        int prev_amount_ = amount_;
        this -> amount_ = other.amount_;
        if (prev_amount_  != amount_) this -> elements_.resize(amount_);
        
        for (int i = 0; i < amount_; i++)
        {
            this -> elements_.at(i) = other.elements_.at(i);
        }
        return *this;
    }
//
//    void insert (const element &e)
//    {
//
//    }
//    bool remove (const element &e)
//    {
//
//    }

    void swap (linkedhs &other)
    {
        linkedhs temp = other;
        other = *this;
        *this = temp;
    }

    size_t size () const
    {
        int el_amount = 0;
        for (int i = 0; i < amount_; i++)
        {
            el_amount += elements_.at(i).size();
        }
        return el_amount;
    }

    bool empty () const
    {
        return elements_.empty();
    }

//    bool contains (const element &e) const
//    {
//
//    }
    //iterator find (const element &e) const;
//
    bool operator == (const linkedhs &other) const
    {
        return (this -> elements_ == other.elements_);
    }
    
    bool operator != (const linkedhs &other) const
    {
        return (this -> elements_ != other.elements_);
    }

    //iterator begin ();
    //iterator end ();

    void clear ()
    {
        if (!elements_.empty()) elements_.clear();
        amount_ = 0;
    }
};

int main(int argc, char **argv)
{
    
}
