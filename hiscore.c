#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c = EOF;
	int count = 0;
	int row = 0;

	if (argc == 1) {
		printf("Please specify a machine name, e.g. \"centiped\"\n");
		return 0;
	}

	while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL) {
			printf("hiscore: sorry, I can't open the file %s\n", *argv);
			return 1;
		}

		while ((c = getc(fp)) != EOF && count < 18) {
			/* Display the high scores */
			if (count < 9) {
				/* Display hex values as if they're decimal, that old 6502 trick */
				printf("%x", c);
			} else {
				/* Convert spaces */
				if (c == 0) {
					c = -0x20;
				}

				/* Convert A=1, B=2 etc into ASCII */
				putc(0x40 + c, stdout);
			}

			if (count % 3 == 2) {
				putc('\n', stdout);
			}

			count++;
		}

		fclose(fp);
	}

	return 0;
}
