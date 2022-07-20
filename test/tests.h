#define TEST_LIST(test) \
    test(test_entityAllocation)

typedef struct TestEntry TestEntry;
struct TestEntry {
    int (*function)(void);
    const char* name;
};

#define TEST_DEFINE(func) int func(void);
#define TEST_ENTRY(func) {func, #func},

TEST_LIST(TEST_DEFINE)
#define TESTS { \
    TEST_LIST(TEST_ENTRY) \
}
