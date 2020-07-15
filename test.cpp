#include "SimpleScopes.h"
#include <iostream>

typedef struct {
    int x;
} testStruct;

void init_a(void ** data){
    testStruct * test = (testStruct*)malloc(sizeof(testStruct*));
    test->x = 5;
    std::cout << "Original ptr: " << test << " <=> Storing value: " << test->x << "\n";
    *data = test;
}

void loop_a(void * data){
    testStruct * test = static_cast<testStruct*>(data);
    std::cout << "Ptr: " << test << " <=> Stored value: " << test->x << "\n";
    return;
}

void clean_a(void ** data){
    return;
}

scope scopesArr[] = {
  {.initfn=&init_a, .loopfn=&loop_a, .cleanfn=&clean_a}
};

SimpleScopes scopes = SimpleScopes(scopesArr, 1);

int main() {
    scopes.init();
    scopes.loop();
}
