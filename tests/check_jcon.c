#include "check_gpm.h"
#include "../src/jcon/jcon.h"


START_TEST(test_jcon_create_parser){
	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);

	ck_assert_ptr_nonnull(parser);
	ck_assert_str_eq(parser->json, json);

	jcon_free_parser(parser);
}
END_TEST

START_TEST(test_jcon_create_element){
	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);
	ck_assert_ptr_nonnull(parser);
	
	JCON_element *elements;
	elements = malloc(sizeof(JCON_element));
	
	int len = 1;

	//for(int i = 0; i < 3; i++){
		ck_assert_int_eq(addJCONElement(&elements, len), len + 1);

		ck_assert_int_eq(elements[len].type, JCON_NULL);
		ck_assert_ptr_null(elements[len].parent);
		ck_assert(elements[len].last == false);
		ck_assert_str_eq(elements[len].value_str, "");
		ck_assert_int_eq(elements[len].value_str_size, 1);
		ck_assert_int_eq(elements[len].element_size, 0);
		len++;
/*	//}
		ck_assert_int_eq(addJCONElement(&elements, len), len + 1);

		ck_assert_int_eq(elements[len].type, JCON_NULL);
		ck_assert_ptr_null(elements[len].parent);
		ck_assert(elements[len].last == false);
		ck_assert_str_eq(elements[len].value_str, "");
		ck_assert_int_eq(elements[len].size, 0);
		len++;*/
}
END_TEST

START_TEST(test_jcon_create_element_null){
	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);
	ck_assert_ptr_nonnull(parser);
	
	ck_assert_int_eq(addJCONElement(NULL, 1), -1);

	JCON_element *el = NULL;
	ck_assert_int_eq(addJCONElement(&el, 1), -1);
}
END_TEST

START_TEST(test_jcon_create_elements){
	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);
	ck_assert_ptr_nonnull(parser);
	
	JCON_element *elements;
	int size = jcon_parse(parser, &elements);
	ck_assert_ptr_nonnull(elements);

	jcon_free_elements(elements);
	jcon_free_parser(parser);
}
END_TEST

START_TEST(test_jcon_parse){
	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);
	ck_assert_ptr_nonnull(parser);

	JCON_element *elements;
	int size = jcon_parse(parser, &elements);
	ck_assert_ptr_nonnull(elements);
//	ck_assert_int_eq(size, 2);

	ck_assert(elements[0].type == JCON_OBJECT);
	
	mark_point();

	ck_assert_str_eq(elements[0].value_str, "key"); // The value string for an array is the key
	
	mark_point();

	ck_assert_ptr_eq(elements[0].parent, NULL); // If the parent is NULL it is the top level/last element in the JSON string
	ck_assert(elements[0].last == true); // If last is true it is the top level/last element of the JSON string
	
	ck_assert(elements[1].type == JCON_STRING);
	ck_assert_str_eq(elements[1].value_str, "valuestring");
	ck_assert_ptr_eq(elements[1].parent, &elements[0]);
	ck_assert(elements[1].last == false);

	jcon_free_elements(elements);
	jcon_free_parser(parser);
}
END_TEST

Suite* check_jcon_suite(void){
    Suite *s;
    TCase *tc_create;
	TCase *tc_parse;

    s = suite_create("jcon");

// Core test case
    tc_create = tcase_create("Create");

    tcase_add_test(tc_create, test_jcon_create_parser);
	tcase_add_test(tc_create, test_jcon_create_element);
	tcase_add_test(tc_create, test_jcon_create_element_null);
	tcase_add_test(tc_create, test_jcon_create_elements);
	suite_add_tcase(s, tc_create);

// Parser 
	tc_parse = tcase_create("Parser");

	tcase_add_test(tc_parse, test_jcon_parse);
	suite_add_tcase(s, tc_parse);

    return s;
}

