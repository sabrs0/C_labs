#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "funcs.h"
half_dyn_str *make_list_from_string(char str1[])
{
	half_dyn_str *head = NULL;
	for (int i = 0; i < strlen(str1); i ++)
	{
		head = add_end(head, create_node(str1[i]));
		if (!head)
		{
			return NULL;
		}
	}
	head = add_end(head, '\0');
	return head;
}
int noda_strcmp(half_dyn_str *head, char str[])
{
	half_dyn_str *head_copy = head;
	int is_empty = 0;
	while (head_copy)
	{
		if (head_copy->str_p != '\0')	
		{
			is_empty = 1;
		}
		head_copy = head_copy->next;
	}
	int len = find_node_len(head);
	if (len != strlen(str))
	{
		if (is_empty || (!is_empty && strlen(str)))
		{
			printf("not eq len\n");
			return ERROR;
		}
	}
	int i = 0;
	while(head)
	{
		if (str[i] != head->str_p)
		{
			printf("%c and %c not eq\n", str[i], head->str_p);
			return ERROR;
		}
		i ++;
		head = head->next;
	}
	return OK;
}
START_TEST(test_make_cat_pstv)
{
	int rc = 0;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	half_dyn_str *res = NULL;
	
	str1 = make_list_from_string("Somebody");
	if (!str1)
	{
		rc = 1;
	}
	str2 = make_list_from_string(" once told me");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
	}
	if (!rc)
	{
		make_cat(str1, str2, &res);
		rc = noda_strcmp(res, "Somebody once told me\0");
	}
	free_list(str1);
	free_list(str2);
	free_list(res);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_cat_pstv2)
{
	int rc = 0;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	half_dyn_str *res = NULL;
	char str3[3];
	str3[0] = '\n';
	str3[1] = '\n';
	str3[2] = '\0';
	str1 = make_list_from_string("\n");
	if (!str1)
	{
		rc = 1;
		printf("ZERO\n");
	}
	str2 = make_list_from_string("\n");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
		printf("ZERO2\n");
	}
	if (!rc)
	{
		make_cat(str1, str2, &res);
		rc = noda_strcmp(res, str3);
	}
	free_list(str1);
	free_list(str2);
	free_list(res);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_sps_pstv)
{
	int rc = 0;
	half_dyn_str *str1 = NULL;
	str1 = make_list_from_string("Somebody        once told me       ");
	if (!str1)
	{
		rc = 1;
	}
	if (rc)
	{
		make_sps(&str1);
		rc = noda_strcmp(str1, "Somebody once told me ");
	}
	free_list(str1);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_sps_pstv2)
{
	int rc = 0;
	half_dyn_str *str1 = NULL;
	str1 = make_list_from_string("                            ");
	if (!str1)
	{
		rc = 1;
	}
	if (rc)
	{
		make_sps(&str1);
		rc = noda_strcmp(str1, " ");
	}
	free_list(str1);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_pos_pstv)
{
	int rc = 0;
	int index = -1;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	str1 = make_list_from_string("Masha ela kashu");
	if (!str1)
	{
		rc = 1;
	}
	str2 = make_list_from_string("kash");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
	}
	if (!rc)
	{
		make_pos(str1, str2, &index);
		rc = index - 10;
	}
	free_list(str1);
	free_list(str2);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_pos_pstv2)
{
	int rc = 0;
	int index = -1;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	str1 = make_list_from_string("Masha ela kashu");
	if (!str1)
	{
		rc = 1;
	}
	str2 = make_list_from_string("Somebody");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
	}
	if (!rc)
	{
		make_pos(str1, str2, &index);
		rc = index - -1;
	}
	free_list(str1);
	free_list(str2);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_pos_pstv3)
{
	int rc = 0;
	int index = -1;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	str1 = make_list_from_string("Masha Masha Masha");
	if (!str1)
	{
		rc = 1;
	}
	str2 = make_list_from_string("Masha");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
	}
	if (!rc)
	{
		make_pos(str1, str2, &index);
		rc = index - 0;
	}
	free_list(str1);
	free_list(str2);
	ck_assert_int_eq(rc, OK);
}
END_TEST
START_TEST(test_make_pos_pstv4)
{
	int rc = 0;
	int index = -1;
	half_dyn_str *str1 = NULL;
	half_dyn_str *str2 = NULL;
	str1 = make_list_from_string("Masha Masha Masha");
	if (!str1)
	{
		rc = 1;
	}
	str2 = make_list_from_string("Masha Masha Masha");
	if (!str2 && str1)
	{
		free_list(str1);
		rc = 1;
	}
	if (!rc)
	{
		make_pos(str1, str2, &index);
		rc = index - 0;
	}
	free_list(str1);
	free_list(str2);
	ck_assert_int_eq(rc, OK);
}
END_TEST
Suite* make_cat_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("cat");

	tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_make_cat_pstv);
	tcase_add_test(tc_pos, test_make_cat_pstv2);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* make_sps_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sps");

	tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_make_sps_pstv);
	tcase_add_test(tc_pos, test_make_sps_pstv2);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* make_pos_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("pos");

	tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_make_pos_pstv);
	tcase_add_test(tc_pos, test_make_pos_pstv2);
	tcase_add_test(tc_pos, test_make_pos_pstv3);
	tcase_add_test(tc_pos, test_make_pos_pstv4);

    suite_add_tcase(s, tc_pos);

    return s;
}
int main()
{
    int no_failed1 = 0;
	int no_failed2 = 0;
	int no_failed3 = 0;


    Suite *s1, *s2, *s3;
    SRunner *runner1;
	SRunner *runner2;
	SRunner *runner3;

    s1 = make_cat_suite();
	s2 = make_sps_suite();
	s3 = make_pos_suite();


    runner1 = srunner_create(s1);
	runner2 = srunner_create(s2);
	runner3 = srunner_create(s3);

    srunner_run_all(runner1, CK_VERBOSE);
	srunner_run_all(runner2, CK_VERBOSE);
	srunner_run_all(runner3, CK_VERBOSE);


    no_failed1 = srunner_ntests_failed(runner1);
	no_failed2 = srunner_ntests_failed(runner2);
	no_failed3 = srunner_ntests_failed(runner3);


    srunner_free(runner1);
	srunner_free(runner2);
	srunner_free(runner3);
    return (no_failed1 == 0 && no_failed2 == 0 && no_failed3 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
