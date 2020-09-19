#include "check_gpm.h"
#include "../src/str.h"

START_TEST(check_str_init){
	str test;
	str_init(&test, "string");

	ck_assert_int_eq(test.size, 7);
	ck_assert_str_eq(test.string, "string");
}
END_TEST

Suite* check_str_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("str");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, check_str_init);
	suite_add_tcase(s, tc_core);

    return s;
}
