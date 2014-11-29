#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int c[18] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
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

		/* Read file into memory */
		for (count = 0; count < 18; count++) {
			c[count] = getc(fp);

			if (count > 8) {
				/* Initials */
				if (c[count] == 0) {
					/* Convert spaces */
					c[count] = 0x20;
				} else {
					/* Convert A=1, B=2 etc into ASCII */
					c[count] += 0x40;
				}
			}
		}

		fclose(fp);

		/* Print memory to screen */
		for (count = 0; count < 3; count++) {
			/* Score */
			/* Display hex values as if they're decimal, that old 6502 trick */
			printf("%02x", c[count * 3 + 2]);
			printf("%02x", c[count * 3 + 1]);
			printf("%02x", c[count * 3]);

			printf(" ");

			/* Initials */
			printf("%c", c[count * 3 + 9]);
			printf("%c", c[count * 3 + 10]);
			printf("%c", c[count * 3 + 11]);

			printf("\n");
		}
	}

	return 0;
}
