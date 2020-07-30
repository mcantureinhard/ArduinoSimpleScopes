#ifndef SIMPLESCOPES_h
#define SIMPLESCOPES_h

typedef struct {
    void (*initfn)(void**);
    int (*loopfn)(void*);
    void (*cleanfn)(void**);
} scope;

class SimpleScopes {
    private:
    void **memory;
    scope *scopes;
    int numScopes;
    int currentScope;
    int prevScope;
    void init(int);
    public:
    SimpleScopes(scope*, int);
    ~SimpleScopes();
    void switchScope(int);
    void loop();
    int getPrevScope(){return prevScope;}
    int getCurrentScope(){return currentScope;}
    void * getCurrentScopeMemory(){return *memory;}
};

#endif