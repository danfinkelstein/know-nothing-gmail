#include <iostream>

class Foo {
public:
    void foo();
};

void Foo::foo() {
}

int main(void) {
    Foo f;
    for (int i=0; i<500; i++)
	f.foo();
    return 0;
}
