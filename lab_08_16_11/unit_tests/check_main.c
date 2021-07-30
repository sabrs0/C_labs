#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "funcs.h"
START_TEST(test_create_matrix_ngtv1)
{
	int rc;
	double **m1;
	int m = -1, n = 5;
	rc = create_matrix(&m1, m, n);
	ck_assert_int_eq(rc, ERROR);
}
START_TEST(test_create_matrix_pstv)
{
	int rc;
	double **m1;
	int m = 5, n = 5;
	rc = create_matrix(&m1, m, n);
	ck_assert_int_eq(rc, OK);
	free_matr(m1, m);
}
START_TEST(test_mult_matr_pstv)
{
    int rc;
    double **m1;
	double **m2;
	double **m3;
	create_matrix(&m1, 3, 3);


	*(*(m1 + 0) + 0) = 1;
	*(*(m1 + 0) + 1) = 2;
	*(*(m1 + 0) + 2) = 3;
	*(*(m1 + 1) + 0) = -4;
	*(*(m1 + 1) + 1) = -5;
	*(*(m1 + 1) + 2) = -6;
	*(*(m1 + 2) + 0) = 7;
	*(*(m1 + 2) + 1) = -8;
	*(*(m1 + 2) + 2) = 9;

	create_matrix(&m2, 3, 1);


	**m2 = 1;
	**(m2 + 1) = 2;
	**(m2 + 2) = 3;

	rc = mult_matr(m1, m2, &m3, 3, 3, 3, 1);

    ck_assert_int_eq(rc, OK);

	free_matr(m1, 3);
	free_matr(m2, 3);
	free_matr(m3, 3);
}
END_TEST
START_TEST(test_mult_matr_ngtv)
{
    int rc;
    double **m1;
	double **m2;
	double **m3;
	create_matrix(&m1, 3, 3);

	
	*(*(m1 + 0) + 0) = 1;
	*(*(m1 + 0) + 1) = 2;
	*(*(m1 + 0) + 2) = 3;
	*(*(m1 + 1) + 0) = -4;
	*(*(m1 + 1) + 1) = -5;
	*(*(m1 + 1) + 2) = -6;
	*(*(m1 + 2) + 0) = 7;
	*(*(m1 + 2) + 1) = -8;
	*(*(m1 + 2) + 2) = 9;

	create_matrix(&m2, 2, 1);


	**m2 = 1;
	**(m2 + 1) = 2;
	rc = mult_matr(m1, m2, &m3, 3, 3, 2, 1);

    ck_assert_int_eq(rc, ERROR_INPUT);
	
	free_matr(m2, 2);
	free_matr(m1, 3);
}
END_TEST
START_TEST(test_mult_matr_bad_mem)
{
    int rc;
    double **m1;
	double **m2;
	double **m3;
	create_matrix(&m1, 3, 3);
	create_matrix(&m2, 2, 1);

	rc = mult_matr(m1, m2, &m3, -1, -2, -2, -4);

    ck_assert_int_eq(rc, ERROR_MEM);
	
	free_matr(m2, 2);
	free_matr(m1, 3);
}
END_TEST
START_TEST(test_sum_matr_pstv)
{
    int rc;
	double **m1;
	double **m2;
	create_matrix(&m1, 3, 3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[1][0] = -4;
	m1[1][1] = -5;
	m1[1][2] = -6;
	m1[2][0] = 7;
	m1[2][1] = -8;
	m1[2][2] = 9;

	create_matrix(&m2, 3, 3);
	m2[0][0] = 1;
	m2[0][1] = 2;
	m2[0][2] = 3;
	m2[1][0] = -4;
	m2[1][1] = -5;
	m2[1][2] = -6;
	m2[2][0] = 7;
	m2[2][1] = -8;
	m2[2][2] = 9;


	rc = sum_matr(m1, m2, 3, 3, 3, 3);

    ck_assert_int_eq(rc, OK);

	free_matr(m1, 3);
	free_matr(m2, 3);
}
END_TEST
START_TEST(test_sum_matr_ngtv)
{
    int rc;
	double **m1;
	double **m2;
	create_matrix(&m1, 3, 3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[1][0] = -4;
	m1[1][1] = -5;
	m1[1][2] = -6;
	m1[2][0] = 7;
	m1[2][1] = -8;
	m1[2][2] = 9;

	create_matrix(&m2, 3, 2);
	m2[0][0] = 1;
	m2[0][1] = 2;
	m2[1][0] = -4;
	m2[1][1] = -5;
	m2[2][0] = 7;
	m2[2][1] = -8;

	rc = sum_matr(m1, m2, 3, 3, 3, 2);

    ck_assert_int_eq(rc, ERROR);
	
	free_matr(m1, 3);
	free_matr(m2, 3);
}
END_TEST
START_TEST(test_find_det_pstv)
{
    int rc;
	double **m1;
	char out_file[256] = "out.txt";

	create_matrix(&m1, 3, 3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;
	m1[1][0] = -4;
	m1[1][1] = -5;
	m1[1][2] = -6;
	m1[2][0] = 7;
	m1[2][1] = -8;
	m1[2][2] = 9;
	
	rc = find_det(m1, 3, 3,out_file);

    ck_assert_int_eq(rc, OK);
	
	free_matr(m1, 3);
}
END_TEST
START_TEST(test_find_det_ngtv)
{
    int rc;
    double **m1;
	char out_file[256] = "out.txt";
	
	create_matrix(&m1, 3, 2);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = -4;
	m1[1][1] = -5;
	m1[2][0] = 7;
	m1[2][1] = -8;
	rc = find_det(m1, 3, 2,out_file);

    ck_assert_int_eq(rc, ERROR);

	free_matr(m1, 3);
}
END_TEST
START_TEST(test_find_det_ngtv2)
{
    int rc;
    double **m1;
	char out_file[256] = "out.txt";
	
	create_matrix(&m1, 2, 2);

	rc = find_det(m1, -1, 2,out_file);

    ck_assert_int_eq(rc, ERROR);

	free_matr(m1, 2);
}
END_TEST
Suite* mult_matr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mult_matr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_mult_matr_ngtv);
	tcase_add_test(tc_neg, test_mult_matr_bad_mem);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mult_matr_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* sum_matr_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("sum_matr");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_sum_matr_ngtv);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_sum_matr_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* create_matrix_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("create_matrix");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_create_matrix_ngtv1);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_create_matrix_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* find_det_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find_det");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_find_det_ngtv);

	tcase_add_test(tc_neg, test_find_det_ngtv2);
    
	suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_find_det_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int no_failed1 = 0;
	int no_failed2 = 0;
	int no_failed3 = 0;
	int no_failed4 = 0;


    Suite *s1, *s2, *s3, *s4;
    SRunner *runner1, *runner2, *runner3, *runner4;

    s1 = mult_matr_suite();
	s2 = sum_matr_suite();
	s3 = find_det_suite();
	s4 = create_matrix_suite();

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

