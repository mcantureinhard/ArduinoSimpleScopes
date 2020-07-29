#include "SimpleScopes.h"
#include <iostream>

SimpleScopes::SimpleScopes(scope *scopes, int size){
    this->scopes = scopes;
    this->numScopes = size;
    currentScope = -1;
    memory = new void*;
}

SimpleScopes::~SimpleScopes(){
    scopes = NULL;
    delete memory;
}

void SimpleScopes::init(int scope){
    scopes[scope].initfn(memory);
    currentScope = scope;
}

void SimpleScopes::init(){
    init(0);
}

void SimpleScopes::loop(){
    int res = scopes[currentScope].loopfn(*memory);
    if(res != -1){
        switchScope(res);
    }
}

void SimpleScopes::switchScope(int newScope){
    scopes[currentScope].cleanfn(memory);
    init(newScope);
}