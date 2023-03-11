#include <dhanda/dhanda.h>
#include <dhanda/txn.h>


void
txn_insert_in_list(dhanda *app, txn *t)
{
	Node *node;
	debug_print("");

	node = list_new_node(app->txn_list, t);
	if (node)
		list_insert_end(app->txn_list, node);
}

txn *
txn_first_in_list(dhanda *app)
{
	txn *t = NULL;
	Node *head;
	debug_print("");

	head = app->txn_list->head;
	if (head)
		t = (txn *) head->data;

	return t;
}

txn *
txn_second_in_list(dhanda *app)
{
	txn *t = NULL;
	Node *head;
	debug_print("");

	head = app->txn_list->head;
	if (head && head->next)
		t = (txn *) head->next->data;

	return t;
}

int put_in_txn_list(void *ptr, int ncols, char **values, char **fields)
{
	Node *node;
	txn temp = {};

	temp.id = (int) strtol(values[0], NULL, 10);
	temp.amount = (int) strtol(values[1], NULL, 10);
	temp.cat = unix_time(values[2]);
	temp.type = (int) strtol(values[3], NULL, 10);
	strcpy(temp.desc, values[4]);
	temp.party_id = (int) strtol(values[5], NULL, 10);

	node = list_new_node((struct list *) ptr, (void *) &temp);
	assert(node != NULL);
	list_insert_end((struct list *) ptr, node);

	return SQLITE_OK;
}

int put_in_txn_struct(void *ptr, int ncols, char **values, char **fields)
{
	txn *temp = (txn *) ptr;

	temp->id = (int) strtol(values[0], NULL, 10);
	temp->amount = (int) strtol(values[1], NULL, 10);
	temp->cat = unix_time(values[2]);
	temp->type = (int) strtol(values[3], NULL, 10);
	strcpy(temp->desc, values[4]);
	temp->party_id = (int) strtol(values[5], NULL, 10);

	return SQLITE_OK;
}

