#include "check_gpm.h"
#define JSMN_HEADER
#include "../src/jsmn/jsmn.h"

START_TEST(check_jsmn_init){
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 JSON tokens */

	jsmn_init(&p);

	ck_assert_int_eq(p.pos, 0);
	ck_assert_int_eq(p.toknext, 0);
	ck_assert_int_eq(p.toksuper, -1);
}
END_TEST

Suite* check_jsmn_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("jsmn");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, check_jsmn_init);
	suite_add_tcase(s, tc_core);

    return s;
}
