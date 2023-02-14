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

void check_amount(char  res)
{
	while (1)
	{
		if (res == 1) {
            break;
        } else {
            printf("Invalid input. Please enter a number.\n");
			printf("              >  ");
            while ((res = getchar()) != '\n' && res != EOF);
        }
	}
	
}

void title_case(char *s)
{
	int i = 0;

	if (s[i] >= 'a' && s[i] <= 'z')
	{
		s[i] = s[i] - 32;
	}
	
}