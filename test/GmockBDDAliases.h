#ifndef GmockBDDAliases_h
#define GmockBDDAliases_h

#define Given(obj, call) ON_CALL(obj, call)
#define Verify(obj, call) EXPECT_CALL(obj, call)

#endif
