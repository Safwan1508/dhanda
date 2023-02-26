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
