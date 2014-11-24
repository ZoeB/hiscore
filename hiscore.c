#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c = EOF;
	int col = 0;
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

		while ((c = getc(fp)) != EOF) {
			/* Display the high scores */
			if (row & 1) {
				/* Convert spaces */
				if (c == 0) {
					c = -0x20;
				}

				putc(0x40 + c, stdout);
			} else {
				printf("%x", c);
			}

			if (col == 7) {
				putc('\n', stdout);
			}

			/* Update the column number, from 0 to 7 looping */
			col++;

			if (col > 7) {
				col = 0;
				row++;
			}
		}

		fclose(fp);
	}

	return 0;
}
