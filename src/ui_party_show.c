#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>


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
