#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <check.h>
#include "funcs.h"
int comp_lists(node_t *ft, node_t *sec)
{
	if(find_node_len(ft) != find_node_len(sec))
		return ERROR;
	while(ft)
	{
		if (comparator(ft->data, sec->data))
		{
			return ERROR;
		}
		ft = ft->next;
		sec = sec->next;
	}
	return OK;
}
START_TEST(test_front_back_split_pstv)
{
	int rc = 0;
	node_t *tmp = NULL;
	node_t *head1 = NULL;
	node_t *head2 = NULL;
	node_t *head_copy1 = NULL;
	node_t *head_copy2 = NULL;
	char words[6][50] = {"dog", "cat", "snake", "savage", "murda_on_a_beat", "CACTUS"};
	for (int i = 0; i < 6; i ++)
	{
		tmp = create_node(words[i]);
		if (!tmp)
		{
			rc = 1;
			break;
		}
		head1 = add_end(head1, tmp);
	}
	if (!rc)
	{
		front_back_split(head1, &head2);
		if (!head2)
		{

			rc = 1;
		}
		else
		{
			head_copy1 = head1;
			head_copy2 = head2;
			for (int i = 0; i < 3; i ++)
			{
				if (strcmp(head1->data, words[i]) || strcmp(head2->data, words[i + 3]))
				{
					rc = 1;
					break;
				}
				head1 = head1->next;
				head2 = head2->next;
			}
		}
	}
	ck_assert_int_eq(rc, OK);	
	free_list(head_copy1);
	free_list(head_copy2);
}
END_TEST
START_TEST(test_front_back_split_pstv2)
{
	int rc = 0;
	node_t *tmp = NULL;
	node_t *head1 = NULL;
	node_t *head2 = NULL;
	tmp = create_node("dog");
	if (!tmp)
	{
		rc = 1;
	}
	head1 = add_end(head1, tmp);
	if (!rc)
	{
		front_back_split(head1, &head2);
		if (head2 || strcmp(head1->data, "dog"))
			rc = 1;
	}
	ck_assert_int_eq(rc, OK);	
	free_list(head1);
	free_list(head2);
}
END_TEST
START_TEST(test_sorted_merge_pstv)
{
	int rc = 0;
	node_t *h1 = NULL;
	node_t *h2 = NULL;
	node_t *res = NULL;
	node_t *tmp = NULL;
	char words[6][50] = {"dog", "cat", "snake"};
	char words2[6][50] = {"savage", "murda_on_a_beat", "CACTUS"};	
	char words1[6][50] = {"cat", "dog", "murda_on_a_beat", "savage", "snake", "CACTUS"};
	for (int i = 0; i < 3; i ++)
	{
		tmp = create_node(words[i]);
		if (!tmp)
		{
			rc = 1;
			break;
		}
		h1 = add_end(h1, tmp);
		tmp = create_node(words2[i]);
		if (!tmp)
		{
			rc = 1;
			break;
		}
		h2 = add_end(h2, tmp);
	}
	if(!rc && h1 && h2)
	{
		res = sorted_merge(&h1, &h2, comparator);
	}
	else
	{
		rc = 1;
	}
	if(!rc && h1 && h2 && res)
	{
		for (int i = 0; i < 6; i ++)
		{
			if (strcmp(res->data, words1[i]))
			{
				rc = 1;
				break;
			}
		}
	}
	ck_assert_int_eq(rc, OK);	
	free_list(h1);
	free_list(h2);
	free_list(res);

}
START_TEST(test_sort_positive)
{
	int rc;
	node_t *tmp = NULL;
	node_t *head = NULL;
	node_t *head2 = NULL;
	tmp = create_node("lion");
	head = add_end(head, tmp);

	tmp = create_node("cat");
	head = add_end(head, tmp);
	
	tmp = create_node("dog");
	head = add_end(head, tmp);

	tmp = create_node("zebra");
	head = add_end(head, tmp);
	
	tmp = create_node("monkey");
	head = add_end(head, tmp);


	tmp = create_node("cat");
	head2 = add_end(head2, tmp);

	tmp = create_node("dog");
	head2 = add_end(head2, tmp);

	tmp = create_node("lion");
	head2 = add_end(head2, tmp);

	tmp = create_node("monkey");
	head2 = add_end(head2, tmp);

	tmp = create_node("zebra");
	head2 = add_end(head2, tmp);
	head = sort(head, comparator);
	rc = comp_lists(head, head2);
	ck_assert_int_eq(rc, OK);	
	free_list(head);
	free_list(head2);
	//free_list(tmp);
}
END_TEST
START_TEST(test_find_positive)
{
	int rc;

	node_t *tmp = NULL;
	node_t *head = NULL;
	tmp = create_node("lion");
	head = add_end(head, tmp);

	tmp = create_node("cat");
	head = add_end(head, tmp);
	
	tmp = create_node("dog");
	head = add_end(head, tmp);

	tmp = create_node("zebra");
	head = add_end(head, tmp);
	
	tmp = create_node("monkey");
	head = add_end(head, tmp);
	
	char str[7] = "monkey";
	void *p_monkey = str;
	tmp = find(head, p_monkey, comparator);
	if (comparator(p_monkey, tmp->data))
	{
		rc = ERROR;
	}
	else
		rc = OK;
	ck_assert_int_eq(rc, OK);
	free_list(head);
}
END_TEST
START_TEST(test_reverse_positive)
{	
	int rc;
	node_t *tmp = NULL;
	node_t *head = NULL;
	node_t *head2 = NULL;
	tmp = create_node("lion");
	head = add_end(head, tmp);

	tmp = create_node("cat");
	head = add_end(head, tmp);
	
	tmp = create_node("dog");
	head = add_end(head, tmp);

	tmp = create_node("zebra");
	head = add_end(head, tmp);
	
	tmp = create_node("monkey");
	head = add_end(head, tmp);


	tmp = create_node("monkey");
	head2 = add_end(head2, tmp);

	tmp = create_node("zebra");
	head2 = add_end(head2, tmp);

	tmp = create_node("dog");
	head2 = add_end(head2, tmp);

	tmp = create_node("cat");
	head2 = add_end(head2, tmp);

	tmp = create_node("lion");
	head2 = add_end(head2, tmp);
	head = reverse(head);
	rc = comp_lists(head, head2);
	ck_assert_int_eq(rc, OK);
	free_list(head);
	free_list(head2);	
}
END_TEST
START_TEST(test_pop_front_positive)
{
	int rc;

	node_t *tmp = NULL;
	void *ans = NULL;
	node_t *head = NULL;
	tmp = create_node("lion");
	head = add_end(head, tmp);

	tmp = create_node("cat");
	head = add_end(head, tmp);
	
	tmp = create_node("dog");
	head = add_end(head, tmp);

	tmp = create_node("zebra");
	head = add_end(head, tmp);
	
	tmp = create_node("monkey");
	head = add_end(head, tmp);
	
	char str[7] = "lion";
	void *p_lion = str;
	ans = pop_front(&head);
	if (comparator(p_lion, ans))
	{
		rc = ERROR;
	}
	else
		rc = OK;
	ck_assert_int_eq(rc, OK);	
	free_list(head);
	free(ans);
}
END_TEST
Suite* sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_sort_positive);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* find_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("find");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_find_positive);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* reverse_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("reverse");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_reverse_positive);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* pop_front_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("pop_front");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_pop_front_positive);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* front_back_split_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("front_back_split");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_front_back_split_pstv);
	tcase_add_test(tc_pos, test_front_back_split_pstv2);

    suite_add_tcase(s, tc_pos);

    return s;
}
Suite* sorted_merge_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sorted_merge");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_sorted_merge_pstv);

    suite_add_tcase(s, tc_pos);

    return s;
}
int main(void)
{
    int no_failed1 = 0;
	int no_failed2 = 0;
	int no_failed3 = 0;
	int no_failed4 = 0;
	int no_failed5 = 0;
	int no_failed6 = 0;


    Suite *s1, *s2, *s3, *s4, *s5, *s6;
    SRunner *runner1, *runner2, *runner3, *runner4, *runner5, *runner6;

    s1 = sort_suite();
	s2 = find_suite();
	s3 = reverse_suite();
	s4 = pop_front_suite();
	s5 = front_back_split_suite();
	s6 = sorted_merge_suite();

    runner1 = srunner_create(s1);
	runner2 = srunner_create(s2);
	runner3 = srunner_create(s3);
	runner4 = srunner_create(s4);
	runner5 = srunner_create(s5);
	runner6 = srunner_create(s6);

    srunner_run_all(runner1, CK_VERBOSE);
	srunner_run_all(runner2, CK_VERBOSE);
	srunner_run_all(runner3, CK_VERBOSE);
	srunner_run_all(runner4, CK_VERBOSE);
	srunner_run_all(runner5, CK_VERBOSE);
	srunner_run_all(runner6, CK_VERBOSE);

    no_failed1 = srunner_ntests_failed(runner1);
	no_failed2 = srunner_ntests_failed(runner2);
	no_failed3 = srunner_ntests_failed(runner3);
	no_failed4 = srunner_ntests_failed(runner4);
	no_failed5 = srunner_ntests_failed(runner5);
	no_failed6 = srunner_ntests_failed(runner6);

    srunner_free(runner1);
	srunner_free(runner2);
	srunner_free(runner3);
	srunner_free(runner4);
	srunner_free(runner5);
	srunner_free(runner6);

    return (no_failed1 == 0 && no_failed2 == 0 && no_failed3 == 0 && no_failed4 == 0 && no_failed5 == 0 && no_failed6 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
