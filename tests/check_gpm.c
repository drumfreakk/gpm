/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/jcon/jcon.h"

/*
START_TEST(test_money_create) {
	Money *m;
	m = money_create(5, "USD");
	ck_assert_int_eq(money_amount(m), 5);
	ck_assert_str_eq(money_currency(m), "USD");
	money_free(m);
}
END_TEST

START_TEST(test_money_neg){
	Money *m = money_create(-1, "USD");
	ck_assert_msg(m == NULL, "NULL should be returned when negative");
}
END_TEST

START_TEST(test_money_zero){
	Money *m = money_create(0, "USD");
	
	ck_assert_msg(money_amount(m) == 0, "Zero is valid");
}
END_TEST
*/

START_TEST(test_jcon_test){
	ck_assert_int_eq(test(5), 5);
	ck_assert_int_eq(test(-1), -1);
}
END_TEST

Suite * jcon_suite(void)
{
    Suite *s;
    TCase *tc_core;
//	TCase *tc_limits;

    s = suite_create("jcon");

 // Core test case
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_jcon_test);
    suite_add_tcase(s, tc_core);

//	tc_limits = tcase_create("Limits");

//	tcase_add_test(tc_limits, test_money_neg);
//	tcase_add_test(tc_limits, test_money_zero);
//	suite_add_tcase(s, tc_limits);

    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = jcon_suite();
    sr = srunner_create(s);
//	srunner_set_fork_status(sr, CK_NOFORK); 	//DEBUGGING
	srunner_set_log (sr, "test.log");	
	srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


