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
    char res = scanf("%d",&p.amount);
	check_amount(res);
		
	reset();


	party_insert_in_list(app, &p);

	puts("");
}

