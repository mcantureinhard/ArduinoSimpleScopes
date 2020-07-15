#include "SimpleScopes.h"
#include <iostream>

SimpleScopes::SimpleScopes(scope *scopes, int size){
    this->scopes = scopes;
    this->numScopes = size;
    currentScope = -1;
    memory = (void**)malloc(8);
}

void SimpleScopes::init(int scope){
    scopes[scope].initfn(memory);
    currentScope = scope;
}

void SimpleScopes::init(){
    init(0);
}

void SimpleScopes::loop(){
    scopes[currentScope].loopfn(*memory);
}

void SimpleScopes::switchScope(int newScope){
    scopes[currentScope].cleanfn(memory);
    init(newScope);
}