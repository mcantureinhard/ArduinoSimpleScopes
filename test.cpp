#include "SimpleScopes.h"
#include <iostream>

#define SCOPE_A 0
#define SCOPE_B 1
#define SCOPE_C 2

bool global_boolean = true;
int global_int = 0;
SimpleScopes *scopes;

typedef struct {
    int scope_int;
} testStruct;

void init_a(void ** data){
    std::cout << "Init scope A\n";
    testStruct * test = new testStruct;
    test->scope_int = global_int;
    *data = test;
}

int loop_a(void * data){
    testStruct * test = static_cast<testStruct*>(data);
    test->scope_int++;
    std::cout << "Loop A - data: " << test->scope_int << "\n";
    //Switch scope from within
    if(test->scope_int == 5){
        return SCOPE_B;
    }
    return -1;
}

void clean_a(void ** data){
    testStruct * test = static_cast<testStruct*>(*data);
    global_int = test->scope_int;
    delete test;
    return;
}

void init_b(void ** data){
    std::cout << "Init scope B\n";
    testStruct * test = new testStruct;
    test->scope_int = global_int * 4;
    *data = test;
}

int loop_b(void * data){
    testStruct * test = static_cast<testStruct*>(data);
    test->scope_int--;
    std::cout << "Loop B - data: " << test->scope_int << "\n";
    return -1;
}

void clean_b(void ** data){
    testStruct * test = static_cast<testStruct*>(*data);
    global_int = test->scope_int;
    delete test;
    return;
}

void init_c(void ** data){
    std::cout << "Init scope C\n";
    testStruct * test = new testStruct;
    test->scope_int = global_int;
    *data = test;
}

int loop_c(void * data){
    testStruct * test = static_cast<testStruct*>(data);
    test->scope_int++;
    std::cout << "Loop C - data: " << test->scope_int << "\n";
    return -1;
}

void clean_c(void ** data){
    testStruct * test = static_cast<testStruct*>(*data);
    global_int = test->scope_int;
    delete test;
    return;
}

scope scopesArr[] = {
  {.initfn=&init_a, .loopfn=&loop_a, .cleanfn=&clean_a},
  {.initfn=&init_b, .loopfn=&loop_b, .cleanfn=&clean_b},
  {.initfn=&init_c, .loopfn=&loop_c, .cleanfn=&clean_c}
};

void loop(){
    int x = 0;
    while(global_boolean && ++x){
        scopes->loop();
        if(x == 10){
            //Switch scope from outside
            scopes->switchScope(SCOPE_C);
        } else if(x >= 25){
            global_boolean = false;
        }
        std::cout << "Main LOOP - data: " << global_int << "\n\n";
    }
    delete scopes;
}

int main() {
    scopes = new SimpleScopes(scopesArr, 1);
    scopes->init();
    loop();
}
