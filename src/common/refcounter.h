#ifndef SMASH_REFCOUNTER_H
#define SMASH_REFCOUNTER_H

class RefCounter {
public:
    void            AddRef() { ++count; }
    void            Release() { if ( --count == 0 ) delete this; }
    unsigned long   RefCount() const { return count; }
protected:
                    RefCounter() : count(1) {}
    virtual         ~RefCounter() {}
private:
    unsigned long   count;
};

#endif // SMASH_REFCOUNTER_H
