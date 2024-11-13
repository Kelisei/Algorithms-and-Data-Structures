#include "minitest.hpp"
#include "linked_list_test.hpp"

int main(int argc, char const *argv[])
{
    registerLinkedListTests();
    RUN_TESTS();
    return 0;
}
