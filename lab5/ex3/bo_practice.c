#include <stdio.h>
#include <string.h>

void secret_func(void)
{
	puts("Channel open.");
}

void visible_func(void)
{
	char buffer[64];
	unsigned int s = 0x42424242;

	printf("Please enter your message: ");
	fgets(buffer, 128, stdin);
	printf("You've entered: %s\n", buffer);

	if (s == 0x5a5a5a5a)
		puts("Comm-link online.");
}

int main(void)
{
	puts("Go ahead, TACCOM");
	visible_func();
	return 0;
}