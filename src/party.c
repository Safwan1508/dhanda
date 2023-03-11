#include <dhanda/dhanda.h>
#include <dhanda/party.h>


void
party_insert_in_list(dhanda *app, party *p)
{
	Node *node;

	node = list_new_node(app->party_list, p);
	if (node)
		list_insert_end(app->party_list, node);
}

party *
party_first_in_list(dhanda *app)
{
	party *p = NULL;
	Node *head;

	head = app->party_list->head;
	if (head)
		p = (party *) head->data;

	return p;
}

party *
party_second_in_list(dhanda *app)
{
	party *p = NULL;
	Node *head;

	head = app->party_list->head;
	if (head && head->next)
		p = (party *) head->next->data;

	return p;
}


int party_update_amount(struct dhanda *app, int pid, int val, int type)
{
	struct party p = {};
	int ret, sign = -1;
	char *err = NULL;
	char sql[1024];

	if (type == 0) {
		val *= sign;
	}

	sprintf(sql, "UPDATE parties SET amount = amount + %d WHERE id = %d", val, pid);

	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		return -1;
	}

	return 0;
}


 


 

