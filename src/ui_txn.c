#include <dhanda/dhanda.h>
#include <dhanda/txn.h>
#include <dhanda/ui.h>


void ui_txn_create(struct dhanda *app)
{
	txn t;
	char line[256], ch;
	int len;
	debug_print("");

	print_heading("DHANDA > TRANSACTION > CREATE");
	printf("   PARTY ID : ");
	scanf("%d", &t.party_id);
	printf("\n");
	printf("   AMOUNT   : ");
	input_amount(&t.amount, validate_amount);
	//scanf("%d", &t.amount);
	printf("\n");
	printf("[O FOR CRED, 1 FOR DEBT]\n");
	printf("   TYPE     : ");
	scanf("%d", &t.type);
	scanf("%c", &ch);
	printf("\n");
	printf("   DESC     : ");
	get_line(t.desc, 256);
	printf("\n");
	/*if(len > 0)
		strcpy(t.desc, line);*/
	//scanf("%s", t.desc);

	t.cat = time(NULL);
	txn_insert_in_list(app, &t);
	puts("");
}

void ui_txn_list(struct dhanda *app)
{
	Node *temp;
	txn *t;
	debug_print("");


	print_heading("DHANDA > TRANSACTION > LIST");
	printf("   ID         PARTY_ID            AMOUNT          DEBIT/CREDIT(D/C)\n");
	printf("\n\n");

	temp = app->txn_list->head;
	while(temp != NULL)
	{	
		t = (txn *)temp->data;
         	printf("   %-10d %-19d %-15d %-15d\n\n",
			       	t->id,
				t->party_id,
			       	t->amount,
			       	t->type);

		temp = temp->next;
	}


}

void ui_txn_show(struct dhanda *app)
{
	Node *ptr;
	ptr = app->txn_list->head;
	txn *t;
	debug_print("");

	t = (txn *) ptr->data;


	print_heading("DHANDA > TRANSACTION > SHOW");
	printf("%-10s %-10s %-10s %-10s %-10s %-10s", "ID", 
												  "AMOUNT",
												  "CAT",
												  "TYPE",
												  "PARTY_ID",
												  "DESC");
	printf("\n\n");
	
	printf("%-10d %-10d %-10ld %-10d %-10d %s\n\n", t->id, 
										  t->amount, 
										  t->cat, 
										  t->type,
										  t->party_id,
										  t->desc);
		
	

	  /*printf("PARTY TRANSACTION......\n\n");
		printf("NAME       TXN        DEBIT      CREDIT     ");
		printf("\n\n");
		printf("\n\n");
		printf("%-10d %-10d %-10d %-10d", id2, txn2, debit2, credit2);
		printf("\n\n");
		printf("%-10d %-10d %-10d %-10d", id3, txn3, debit3, credit3);
			puts("");*/

}
