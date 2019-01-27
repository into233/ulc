#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now;
	struct tm *ts;
	char buf[80];

	now = time(NULL);
	
	ts = localtime(&now);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
	puts(buf);
	printf("%d, %s", ts, ts);

	return 0;
}
