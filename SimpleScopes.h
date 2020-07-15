#ifndef SIMPLESCOPES_h
#define SIMPLESCOPES_h

typedef struct {
    void (*initfn)(void**);
    void (*loopfn)(void*);
    void (*cleanfn)(void**);
} scope;

class SimpleScopes {
    private:
    void **memory;
    scope *scopes;
    int numScopes;
    int currentScope;
    public:
    SimpleScopes(scope*, int);
    void init();
    void init(int);
    void switchScope(int);
    void loop();
};

#endif