#include <stdio.h>
#include <string.h>

int centiped() {
	int c[18] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	int count = 0;
	FILE *fp;

	if ((fp = fopen("nvram/centiped/earom", "r")) == NULL) {
		printf("Sorry, I can't open nvram/centiped/earom\n");
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

	return 0;
}

int tempest() {
	int c[18] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	int count = 0;
	FILE *fp;

	if ((fp = fopen("nvram/tempest/earom", "r")) == NULL) {
		printf("Sorry, I can't open nvram/tempest/earom\n");
		return 1;
	}

	/* Read file into memory */
	for (count = 17; count > -1; count--) {
		c[count] = getc(fp);

		if (count > 8) {
			/* Initials */
			if (c[count] == 0x1a) {
				/* Convert spaces */
				c[count] = 0x20;
			} else {
				/* Convert A=1, B=2 etc into ASCII */
				c[count] += 0x41;
			}

			if (count == 9) {
				getc(fp); /* Skip the tenth byte */
			}
		}
	}

	fclose(fp);

	/* Print memory to screen */
	for (count = 0; count < 3; count++) {
		/* Score */
		/* Display hex values as if they're decimal, that old 6502 trick */
		printf("%02x", c[count * 3]);
		printf("%02x", c[count * 3 + 1]);
		printf("%02x", c[count * 3 + 2]);

		printf(" ");

		/* Initials */
		printf("%c", c[count * 3 + 9]);
		printf("%c", c[count * 3 + 10]);
		printf("%c", c[count * 3 + 11]);

		printf("\n");
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Please specify a machine name, e.g. \"centiped\"\n");
		return 0;
	}

	if (strcmp(argv[1], "centiped") == 0) {
		return centiped();
	} else if (strcmp(argv[1], "tempest") == 0) {
		return tempest();
	} else {
		printf("Sorry, I don't recognise \"%s\"\n", argv[1]);
	}

	return 1;
}
