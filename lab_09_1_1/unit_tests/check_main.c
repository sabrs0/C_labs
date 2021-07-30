#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "funcs.h"
START_TEST(tests_bin_search_pstv)
{
	int rc;
	int flag = 0;
	char keys_title[5][100] = {"alladin", "pulp fiction" , "jocker", "the ugly eight", "reservoir dogs"};
	char keys_name[5][100] = { "guy richie", "tarantino" "joakin phoenix", "tarantino", "tarantino"};
	int keys_year[5] = {2018, 1994, 2018, 2012, 1992};
	films_t *films;
	films = malloc(sizeof(films_t) * 5);
	if (!films)
	{
		rc = ERROR;
		flag = 1;
	}
	int ind =0;
	for (int i = 0; i < 5; i ++)
	{
		films[i].title = malloc(sizeof(char) * (strlen(keys_title[i]) + 1));
		if (!films[i].title)
		{
			rc = ERROR;
			flag = 1;
			break;
		}
		strcpy(films[i].title, keys_title[i]);
		films[i].name = malloc(sizeof(char) * (strlen(keys_name[i]) + 1));
		if (!films[i].name)
		{
			free(films[i].title);
			rc = ERROR;
			flag = 1;
			break;
		}
		strcpy(films[i].name, keys_name[i]);
		films[i].year = keys_year[i];
	}
	if (!flag)
	{
		rc = bin_search(films, 1, "jocker", &ind, 5);
	}
	ck_assert_int_eq(rc, OK);
	free_struct(&films, 5);
}
START_TEST(tests_bin_search_ngtv)
{
	int rc;
	int flag = 0;
	char keys_title[5][100] = {"alladin", "pulp fiction" , "jocker", "the ugly eight", "reservoir dogs"};
	char keys_name[5][100] = { "guy richie", "tarantino" "joakin phoenix", "tarantino", "tarantino"};
	int keys_year[5] = {2018, 1994, 2018, 2012, 1992};
	films_t *films;
	films = malloc(sizeof(films_t) * 5);
	if (!films)
	{
		rc = ERROR;
		flag = 1;
	}
	int ind =0;
	for (int i = 0; i < 5; i ++)
	{
		films[i].title = malloc(sizeof(char) * (strlen(keys_title[i]) + 1));
		if (!films[i].title)
		{
			rc = ERROR;
			flag = 1;
			break;
		}
		strcpy(films[i].title, keys_title[i]);
		films[i].name = malloc(sizeof(char) * (strlen(keys_name[i]) + 1));
		if (!films[i].name)
		{
			free(films[i].title);
			rc = ERROR;
			flag = 1;
			break;
		}
		strcpy(films[i].name, keys_name[i]);
		films[i].year = keys_year[i];
	}
	if (!flag)
	{
		rc = bin_search(films, 1, "SOMEBODY", &ind, 5);
	}
	ck_assert_int_eq(rc, ERROR);
	free_struct(&films, 5);
}
Suite* bin_search_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("bin_search");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, tests_bin_search_ngtv);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, tests_bin_search_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{
    int no_failed1 = 0;


    Suite *s1;
    SRunner *runner1;

    s1 = bin_search_suite();


    runner1 = srunner_create(s1);

    srunner_run_all(runner1, CK_VERBOSE);


    no_failed1 = srunner_ntests_failed(runner1);


    srunner_free(runner1);


    return (no_failed1 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
