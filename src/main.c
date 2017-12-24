#include <stdio.h>
#include "smtp_client.h"

int main()
{
  //  printf("hello");
    int res = start_smtp_client("/home/lera/Desktop/maildir/new/", "/home/lera/Desktop/maildir/cur/");
    printf("SMTP client terminated with code = %d\n", res);
	return 0;
}
