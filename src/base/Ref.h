#pragma once

#include "Def.h"
#include <new>
#include <vector>
#include <string>

namespace gear {

class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator=(const NonCopyable&);
};
    
GCLASS()
class Ref : public NonCopyable
{
protected:
    Ref();

    unsigned int reference_count_;
public:
    virtual ~Ref();

    virtual bool baseInit(void) { return true; }

    GFUNCTION()
    void retain();
    GFUNCTION()
    void release();

    virtual void update();

    Ref* autoRelease();
    unsigned int getReferenceCount() const { return reference_count_; }

    void addChild(Ref* obj);
    void delChild(Ref* obj);
    void clearChildren();
    virtual void removeFromParent();

    template<typename T>
    T* to() const { return reinterpret_cast<T*>(this); }
    virtual std::string toString() const { return "----[Ref]----"; }
private:
    typedef std::vector<Ref*> RefVec;
    RefVec children_;
    Ref* parent_;
};

#define GEAR_SAFE_RELEASE(r) \
    if (r) \
    { \
        r->release(); \
        r = 0; \
    }

#define GEAR_SAFE_RETAIN(r) \
    if (r) \
    { \
        r->retain(); \
    }

#define GEAR_CREATE_FUNC(__TYPE__) \
    static __TYPE__* create(bool inpool = true) \
    { \
        __TYPE__* ret = new(std::nothrow) __TYPE__(); \
        if (ret && ret->baseInit()) \
        { \
            if (inpool) \
                ret->autoRelease(); \
            return ret; \
        } \
        GEAR_SAFE_RELEASE(ret) \
        return ret; \
    }

} // namespace gear
