#ifndef _EXAMPLE_ADDER_MOCK
#define _EXAMPLE_ADDER_MOCK

#include <Adder.h>

class MockAdder: public Adder {
public:
  MOCK_METHOD2(add, int(int, int));
};

#endif