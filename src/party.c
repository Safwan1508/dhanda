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


 int put_in_party_struct(void *ptr, int ncols, char **values, char **fields)
 {
 	party *temp = (party *) ptr;
	
 	temp->id = (int) strtol(values[0], NULL, 10);
 	strcpy(temp->fname, values[1]);
 	strcpy(temp->lname, values[2]);
 	strcpy(temp->phone, values[3]);
 	temp->amount = (int) strtol(values[4], NULL, 10);
 	temp->cat = unix_time(values[5]);
 	temp->uat = unix_time(values[6]);

 	return SQLITE_OK;
		
 }


 int put_in_party_list(void *ptr, int ncols, char **values, char **fields)
 {
 	Node *node;
 	party temp = {};

 	temp.id = atoi(values[0]);
 	strcpy(temp.fname, values[1]);
 	strcpy(temp.lname, values[2]);
 	strcpy(temp.phone, values[3]);
 	temp.amount = atoi(values[4]);
 	temp.cat = unix_time(values[5]);
 	temp.uat = unix_time(values[6]);


 	node = list_new_node((struct list *) ptr, (void *) &temp);
 	list_insert_end((struct list *) ptr, node);

 	return SQLITE_OK;
		
 }

