#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>


void ui_party_create(struct dhanda *app)
{
	party p;
	int len;
	long ret;
	char s[100];
	char *ptr;
	time_t t;

	print_heading("DHANDA > PARTY > CREATE");
	printf("   FIRST NAME :  ");
	input_valid_string(p.fname, sizeof(p.fname), check_name);
	title_case(p.fname);
	printf("\n");
	printf("   LAST NAME  :  ");
	input_valid_string(p.lname, sizeof(p.lname), check_name);
	title_case(p.lname);
	printf("\n");
	printf("   PHONE      :  ");
	input_valid_string(p.phone, sizeof(p.phone), check_phone);
	printf("\n");
	printf("  AMOUNT     :  ");
	//input_valid_string(p.amount, sizeof(p.amount), check_amount);
	input_amount(&p.amount, validate_amount);

	time(&p.cat);
	
		
	reset();


	party_insert_in_list(app, &p);

	puts("");
}

void ui_party_delete(struct dhanda *app)
{
	Node *ptr;
	party *p;

	debug_print("");


	print_heading("DHANDA > PARTY > DELETE");
	printf("\n\n");
	reset();

	
	ptr = app->party_list->head;
	while(!ptr){
		p = (party *) ptr->data;
	}

}

void ui_party_edit(struct dhanda *app)
{
	long int phone, amount;
	char fname[64], lname[64];
	party *old_party, *new_party;
	int len;
	char *ptr;
	long int ret;

	old_party = party_first_in_list(app);
	new_party = party_second_in_list(app);

	debug_print("");


	print_heading("DHANDA > PARTY > EDIT");

	printf("FIRST NAME :  %s\n\n", old_party->fname);
	printf("LAST NAME  :  %s\n\n", old_party->lname);
	printf("PHONE      :  %s\n\n", old_party->phone);
	printf("AMOUNT     :  %d\n\n", old_party->amount);
	puts("");


	printf("FIRST NAME :  ");
	get_string(new_party->fname, sizeof(new_party->fname));

	printf("LAST NAME  :  ");
	get_string(new_party->lname, sizeof(new_party->lname));

	printf("PHONE      :  ");
	get_string(new_party->phone, sizeof(new_party->phone));
	
	printf("AMOUNT     :  ");
	scanf("%d", &new_party->amount);
}

void ui_party_list(struct dhanda *app)
{
	Node *ptr;
	party *p;
	ptr = app->party_list->head;

	print_heading("DHANDA > PARTY > LIST");
	grey();

	printf("   %-13s %-20s %-20s %-15s %-10s\n\n\n", "ID", "FIRST NAME", "LAST NAME", "AMOUNT", "PHONE");
	reset();
	while(ptr){
		p = (party *) ptr->data;
		printf("   %-13d %-20s %-20s %-15d %-10s\n\n", p->id, p->fname, p->lname, p->amount, p->phone);
		ptr = ptr->next;
	}
}


void ui_party_show(struct dhanda *app)
{
	int id;
	party *p;
	char fname[32];
	char lname[32];
	char phone[12];
	int amount;
	struct tm* tm;



	debug_print("");
	p = party_first_in_list(app);


	print_heading("DHANDA > PARTY > SHOW");

	grey();
	printf("   ID NO      : %d               \n\n", p->id);

	printf("   FIRST NAME : %s               ", p->fname);
	printf("\n\n");
	printf("   LAST NAME  : %s               ", p->lname);
	printf("\n\n");

	printf("   PHONE NO   : %s               \n\n", p->phone);
	//p.created_at = t;
	printf("Created At:	");
	created_at(p->cat);


	//tm = localtime(&p->created_at);
	//strftime(created_at, sizeof(created_at), "%Y-%d-%m", tm);
	reset();
	
}