//
// Created by Administrator on 2022/3/31.
//

#ifndef STRVEC_STRVEC_H
#define STRVEC_STRVEC_H

#include <memory>
#include <string>

using namespace std;
class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr)
    {}

    StrVec(const StrVec &);

    StrVec &operator=(const StrVec );

    ~StrVec();

    void push_back(const string &);

    size_t size() const
    { return first_free- elements; }


    size_t capacity()const
    { return cap - elements; }

    string *begin() const
    { return elements; }

    string *end() const
    { return first_free; }


private:
    static std::allocator<string> alloca;

    void chk_n_alloc();

    std::pair<string *, string *> alloc_n_copy(const string *, const string *);

    void free();

    void reallocate();

    string *elements;
    string *first_free;
    string *cap;

};

#endif //STRVEC_STRVEC_H