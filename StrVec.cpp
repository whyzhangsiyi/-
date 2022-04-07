//
// Created by Administrator on 2022/3/31.
//

#include "StrVec.h"

std::allocator<string> StrVec::alloca;

void StrVec::free()
{
    string *tmp_ele = elements;
    while (tmp_ele != first_free)
    {
        alloca.destroy(tmp_ele++);
    }
    alloca.deallocate(elements, capacity());

}

std::pair<string *, string *> StrVec::alloc_n_copy(const string *ele, const string *fir)
{
    string *new_elements = alloca.allocate((fir - ele) * 2);
    int count = 0;
    while (ele != fir)
    {
        alloca.construct(new_elements + count, *ele);
        ++count;
        ++ele;
    }
    std::pair<string *, string *> ptrs(new_elements, new_elements + count);
    return ptrs;
}

void StrVec::reallocate()
{
    std::pair<string *, string *> ptrs = alloc_n_copy(elements, first_free);
    free();
    cap = ptrs.first + size()  * 2;
    elements = ptrs.first;
    first_free = ptrs.second;
}

void  StrVec::chk_n_alloc()
{
     if (cap == first_free)
        reallocate();
}

void StrVec::push_back(const string &s)
{
    if (elements == nullptr){
        elements = alloca.allocate(1);
        alloca.construct(elements,s);
        first_free = cap = elements + 1;
    }
    else {
    chk_n_alloc();
    alloca.construct(elements + size(), s);
    ++first_free;
    }
}

StrVec::StrVec(const StrVec &strvec)
{

    pair<string *, string *> ptrs = alloc_n_copy(strvec.elements, strvec.first_free);
    elements = ptrs.first;
    first_free = ptrs.second;
    cap = elements + 2 * (first_free - elements);
}

StrVec::~StrVec()
{

    free();

}

StrVec& StrVec::operator=(const StrVec strvec){

    free();
    pair<string *, string *>ptrs= alloc_n_copy(strvec.elements,strvec.first_free);
    elements=ptrs.first;
    cap=first_free=ptrs.second;
    return *this;

}























