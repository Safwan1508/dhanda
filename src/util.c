#include <dhanda/dhanda.h>
#include <dhanda/util.h>

#include <sys/types.h>
#include <regex.h>

int get_line(char line[], int size)
{
	int i;
	char ch;

	i = 0;
	do
	{
		ch = getchar();
		line[i] = ch;
		++i;
	} while (ch != EOF && ch != '\n' && i < size - 1);

	if (ch == EOF)
		line[--i] = '\0';
	else
		line[i] = '\0';

	return i;
}

int
get_string(char line[], int size)
{
	int len;

	len = get_line(line, size);
	line[len - 1] = '\0';

	return len - 1;
}

//COLORS FUNCTIONS
void sky()
{
	printf("\x1b[30;106m");
}
void red () {
  printf("\x1b[1;31m");
}
void yellow() {
  printf("\x1b[1;33m");
}
void grey(){
	printf("\x1b[30;47m");
}
void reset () {
  printf("\x1b[0m");
}
void italic(){
	printf("\x1b[3m");
}
void bold(){
	printf("\x1b[1m");
}
void framed()
{
	printf("\x1b[51m");
}
void green(){
	printf("\x1b[30;42m");
}
void error() {
	printf("\x1b[37;41m");
	printf("ERROR:");
}
void success(){
	printf("\x1b[37;42m");
	printf("SUCCESS:");
}
void warning(){
	yellow();
	printf("WARNING:");
}


void print_heading(char *s)
{
	bold();
	italic();
	printf("\x1b[92;100m");
	printf("%s", s);
	printf("\n\n");
	reset();
}

void print_success(char *s)
{

	printf("\x1b[1;32m");
	printf("%s", s);
}

void print_error(char *s)
{
	printf("\x1b[1;31m");
	printf("%s", s);
}

void print_warning(char *s)
{
	printf("\x1b[1;93m");
	printf("%s", s);
}




int check_name(char *s)
{
	char *pattern = "^[a-zA-Z ]{2,31}$";
	char buff[1024];

	int err;

	regex_t rgx;

	if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0)
	{
		return -1;
	}
	
	if(regexec(&rgx, s, 0, NULL, 0) == REG_NOMATCH)
	{
		return -1;
	}

	return 0;



}

int check_phone(char *s)
{
	char *pattern = "^[0-9]{10}$";
	char buff[1024];

	int err;

	regex_t rgx;

	if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0)
	{
		return -1;
	}
	
	if(regexec(&rgx, s, 0, NULL, 0) == REG_NOMATCH)
	{
		return -1;
	}

	return 0;
}

void input_valid_string(char *in, size_t size, int (*validator)(char *))
{
	while (1)
	{
		
		get_string(in, size);
		

		if (validator(in) == 0)
		{
			break;
		}
		print_error("Invalid input\n");
		printf("              >  ");
	}
	
}

void input_amount(int *in, int (*validator)(char *)) {
	char amount[10];

	while(1) {
		printf("> ");
		get_string(amount, 10);
			
		if(validator(amount) == 0) {
			long ret = strtol(amount, NULL, 10);
			*in = (int) ret;
			break;
		}
		
		printf("Invalid input\n");
	}

}

int validate_amount(char *str) {
		//regular expression
		char *pattern = "^[0-9]{1,10}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			 regerror(err, &rgx, buf, sizeof(buf));
			 printf("%s\n", buf);
			return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}

		return 0;
}



void title_case(char *s)
{
	int i = 0;

	if (s[i] >= 'a' && s[i] <= 'z')
	{
		s[i] = s[i] - 32;
	}
	
}

void created_at(time_t t) {
	struct tm *tm;
	char timestr[128];

	tm = localtime(&t);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %T", tm);

	printf("%s\n", timestr);

}

char *created_time(time_t t){
	struct tm *tm;
	char *timestr = malloc(sizeof(char) *128);

	tm = localtime(&t);
	strftime(timestr, 128, "%Y-%m-%d %T", tm);

	return timestr;


}

char *updated_time(time_t t){
	struct tm *tm;
	char *timestr = malloc(sizeof(char) *128);

	tm = localtime(&t);
	strftime(timestr, 128, "%Y-%m-%d %T", tm);

	return timestr;


}

void updated_at(time_t t) {
	struct tm *tm;
	char timestr[128];

	tm = localtime(&t);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %T", tm);

	printf("%s\n", timestr);
}

time_t unix_time(char *timestr){
	struct tm tm = {};

	strptime(timestr, "%Y-%m-%d %T", &tm );

	time_t t = mktime(&tm);

	return t;
}