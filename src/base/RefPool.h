#pragma once

/**
 * ref pool
 * step 1.push a pool to manager(g_RefPool)
 * step 2.every frame you should call g_RefPool->getCurrentPool()->clear() to release the ref
 *
 **/

#include "Ref.h"
#include <vector>
#include "Singleton.h"

namespace gear {

class RefPool : public Ref
{
public:
    RefPool();
    virtual ~RefPool();

    void addRef(Ref* ref);
    void delRef(Ref* ref);
    void clear();
private:
    typedef std::vector<Ref*> RefVec;
    RefVec ref_vec_;
};

class RefPoolManager : public Ref
{
public:
    RefPoolManager();
    virtual ~RefPoolManager();

    virtual bool baseInit();

    RefPool* getCurrentPool() const { return cur_pool_; }
    void push(RefPool* pool);
    void pop();
private:
    RefPool* cur_pool_;

    typedef std::vector<RefPool*> PoolVec;
    PoolVec pool_vec_;
};

#define g_RefPool (gear::Singleton<gear::RefPoolManager>::instance())

} // namespace gear
