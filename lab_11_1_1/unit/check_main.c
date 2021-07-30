#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <check.h>
#include "../inc/funcs.h"
#define BUF_LEN 100
START_TEST(test_spec_c)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 50, "%c", 'S');
	lib = snprintf(lib_buf, 50, "%c", 'S');
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_spec_s)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 50, "%s", "I get those goosebumbs every time");
	lib = snprintf(lib_buf, 50, "%s", "I get those goosebumbs every time");
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_spec_d)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 25, "%d", -2000000000);
	lib = snprintf(lib_buf, 25, "%d", -2000000000);
	//printf("%d %d %s %s\n", my, lib, my_buf, lib_buf);
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_spec_i)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 50, "%i", 2);
	lib = snprintf(lib_buf, 50, "%i", 2);
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_NULL)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(NULL, 0, "%d", 23);
	lib = snprintf(NULL, 0, "%d", 23);
	rc = my - lib;
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_truncated_s)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 10, "%s", "I get those goosebumbs every time");
	lib = snprintf(lib_buf, 10, "%s", "I get those goosebumbs every time");
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_truncated_d)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 5, "%d + %d = answer %d", 2, 2, 5);
	lib = snprintf(lib_buf, 5, "%d + %d = answer %d", 2, 2, 5);
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_zero_size)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN] = {0}, lib_buf[BUF_LEN] = {0};
	my = my_snprintf(my_buf, 0, "%s", "I get those goosebumbs every time");
	lib = snprintf(lib_buf, 0, "%s", "I get those goosebumbs every time");
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_format_empt)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN] = {0}, lib_buf[BUF_LEN] = {0};
	my = my_snprintf(my_buf, 50, "", "I get those goosebumbs every time");
	lib = snprintf(lib_buf, 50, "", "I get those goosebumbs every time");
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test1_limits_d)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 25, "%d", INT_MAX);
	lib = snprintf(lib_buf, 25, "%d", INT_MAX);
	//printf("%d %d %s %s\n", my, lib, my_buf, lib_buf);
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test2_limits_d)
{
	int rc;
	int my,lib;
	char my_buf[BUF_LEN], lib_buf[BUF_LEN];
	my = my_snprintf(my_buf, 25, "%d", INT_MIN);
	lib = snprintf(lib_buf, 25, "%d", INT_MIN);
	//printf("%d %d %s %s %d\n", my, lib, my_buf, lib_buf, INT_MIN);
	rc = my - lib + strcmp(my_buf, lib_buf);
	ck_assert_int_eq(rc, OK);
}
END_TEST
Suite* limits_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    
    s = suite_create("limits");
    
    tc_pos = tcase_create("positives");
    
	tcase_add_test(tc_pos, test1_limits_d);
	tcase_add_test(tc_pos, test2_limits_d);

    
    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* specs_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    
    s = suite_create("specs");
    
    tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_spec_c);
	tcase_add_test(tc_pos, test_spec_s);
	tcase_add_test(tc_pos, test_spec_d);
	tcase_add_test(tc_pos, test_spec_i);

    
    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* truncated_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    
    s = suite_create("truncated");
    
    tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_truncated_d);
	tcase_add_test(tc_pos, test_truncated_s);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* nulls_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    
    s = suite_create("zeros");
    
    tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_NULL);
	tcase_add_test(tc_pos, test_zero_size);
	tcase_add_test(tc_pos, test_format_empt);

    suite_add_tcase(s, tc_pos);

    return s;
}
int main()
{
    int no_failed1 = 0;
	int no_failed2 = 0;
	int no_failed3 = 0;
	int no_failed4 = 0;
    Suite *s1, *s2, *s3, *s4;
    SRunner *runner1, *runner2, *runner3, *runner4;

    s1 = specs_suite();
	s2 = truncated_suite();
	s3 = nulls_suite();
	s4 = limits_suite();
    runner1 = srunner_create(s1);
	runner2 = srunner_create(s2);
	runner3 = srunner_create(s3);
	runner4 = srunner_create(s4);

    srunner_run_all(runner1, CK_VERBOSE);
	srunner_run_all(runner2, CK_VERBOSE);
	srunner_run_all(runner3, CK_VERBOSE);
	srunner_run_all(runner4, CK_VERBOSE);

    no_failed1 = srunner_ntests_failed(runner1);
	no_failed2 = srunner_ntests_failed(runner2);
	no_failed3 = srunner_ntests_failed(runner3);
	no_failed4 = srunner_ntests_failed(runner4);

    srunner_free(runner1);
	srunner_free(runner2);
	srunner_free(runner3);
	srunner_free(runner4);

    return (no_failed1 == 0 && no_failed2 == 0 && no_failed3 == 0 && no_failed4 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
