#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "funcs.h"
START_TEST(test_key_usual_arr)
{
    int rc;
    int arr1_b[5] = {1, 2, 3, 4, 5};
    int *arr1_e = arr1_b + 5;
    int *arr2_b, *arr2_e;
    rc = key(arr1_b, arr1_e, &arr2_b, &arr2_e);
    ck_assert_int_eq(rc, OK);
    free(arr2_b);
}
END_TEST
START_TEST(test_key_empty_arr)
{
    int rc;
    int arr1_b[5] = {-1, 2, 3, 4, 5};
    int *arr1_e = arr1_b + 5;
    int *arr2_b, *arr2_e;
    rc = key(arr1_b, arr1_e, &arr2_b, &arr2_e);
    ck_assert_int_eq(rc, ERROR);
}
END_TEST
START_TEST(test_key_bad_arr)
{
    int rc;
    int *arr1_b = NULL;
    int *arr1_e = arr1_b + 5;
    int *arr2_b, *arr2_e;
    rc = key(arr1_b, arr1_e, &arr2_b, &arr2_e);
    ck_assert_int_eq(rc, ERR_INVALID_PTR);
}
END_TEST
START_TEST(test_key_negative_arr)
{
    int rc;
    int arr1_b[5] = {-1, -2, -3, -4, -5};
    int *arr1_e = arr1_b + 5;
    int *arr2_b, *arr2_e;
    rc = key(arr1_b, arr1_e, &arr2_b, &arr2_e);
    ck_assert_int_eq(rc, ERROR);
}
END_TEST
START_TEST(test_mysort_usual_arr)
{
    int rc = OK;
	int n = 5;
    int arr1[5] = {2, 1, 4, 5, 3};
	int arr2[5] = {1, 2, 3, 4, 5};
    mysort(arr1, n, sizeof(int), comparator);
	for (int i = 0; i < n; i ++)
	{
		if (arr1[i] != arr2[i])
		{
			rc = ERROR;
		}
	}
    ck_assert_int_eq(rc, OK);
}
END_TEST
Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    
    s = suite_create("key");

    
    tc_neg = tcase_create("negatives");
    
    tcase_add_test(tc_neg, test_key_bad_arr);
    tcase_add_test(tc_neg, test_key_empty_arr);
	tcase_add_test(tc_neg, test_key_negative_arr);
    
    suite_add_tcase(s, tc_neg);

    
    tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_key_usual_arr);

    
    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_pos = tcase_create("positives");
    
    tcase_add_test(tc_pos, test_mysort_usual_arr);

    
    suite_add_tcase(s, tc_pos);

    return s;
}
int main(void)
{
    int no_failed1 = 0;
	int no_failed2 = 0;
    Suite *s1, *s2;
    SRunner *runner1, *runner2;

    s1 = key_suite();
	s2 = mysort_suite();
    runner1 = srunner_create(s1);
	runner2 = srunner_create(s2);

    srunner_run_all(runner1, CK_VERBOSE);
	srunner_run_all(runner2, CK_VERBOSE);

    no_failed1 = srunner_ntests_failed(runner1);
	no_failed2 = srunner_ntests_failed(runner2);

    srunner_free(runner1);
	srunner_free(runner2);

    return (no_failed1 == 0 && no_failed2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

