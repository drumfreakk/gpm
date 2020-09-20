#include "check_gpm.h"
#include "../src/jsmn/jsmn.h"

jsmn_parser p;
jsmntok_t t[128];
char* s = "{\"glossary\": { \"title\": \"example glossary\",\"GlossDiv\": { \"title\": \"S\",\"GlossList\": { \"GlossEntry\": { \"ID\": \"SGML\",\"SortAs\": \"SGML\",\"GlossTerm\": \"Standard Generalized Markup Language\",\"Acronym\": \"SGML\",\"Abbrev\": \"ISO 8879:1986\",\"GlossDef\": {\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\", \"GlossSeeAlso\": [\"GML\", \"XML\"]},\"GlossSee\": \"markup\"}}}}}";

void setup(void){
	jsmn_init(&p);
}

void teardown(void){
	return;
}

START_TEST(check_jsmn_init){
	ck_assert_int_eq(p.pos, 0);
	ck_assert_int_eq(p.toknext, 0);
	ck_assert_int_eq(p.toksuper, -1);
}
END_TEST

START_TEST(check_jsmn_parse){
	ck_assert_int_eq(jsmn_parse(&p, s, strlen(s), NULL, 0), 33);
}
END_TEST

START_TEST(check_jsmn_element){
	jsmn_parse(&p, s, strlen(s), t, 128);
	ck_assert(t[2].type == JSMN_OBJECT);
	ck_assert_int_eq(t[2].start, 13);
	ck_assert_int_eq(t[2].end, 380);
	ck_assert_int_eq(t[2].size, 2);
}
END_TEST

Suite* check_jsmn_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("jsmn");

	tc_core = tcase_create("Core");

	tcase_add_checked_fixture(tc_core, setup, teardown);

	tcase_add_test(tc_core, check_jsmn_init);
	tcase_add_test(tc_core, check_jsmn_parse);
	tcase_add_test(tc_core, check_jsmn_element);
	suite_add_tcase(s, tc_core);

    return s;
}
