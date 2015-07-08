#include <stdio.h>
#include <string.h>

int astdelux() {
	int c[21];
	int checksum = 0;
	int count = 0;
	FILE *fp;
	int remainder = 0;

	if ((fp = fopen("nvram/astdelux/earom", "r")) == NULL) {
		printf("Sorry, I can't open nvram/astdelux/earom\n");
		return 1;
	}

	for (count = 0; count < 21; count++) {
		c[count] = getc(fp);
		remainder = count % 7;

		if (remainder == 6) {
			/* Checksum; end of line */

			if (c[count] != checksum) {
				printf(" (Checksum failed)");
			}

			printf("\n");
			checksum = 0;
		} else if (remainder > 2) {
			/* Initials */
			checksum += c[count];

			if (c[count] == 0x00) {
				/* Convert spaces into ASCII */
				c[count] = 0x20;
			} else {
				/* Convert A=11, B=12 etc into ASCII */
				c[count] += 0x36;
			}

			printf("%c", c[count]);
		} else {
			/* Score (backwards bytes consisting of forwards packed binary-coded
			   decimal) */
			checksum += c[count];

			if (remainder == 2) {
				printf("%02x", c[count]);
				printf("%02x", c[count - 1]);
				printf("%02x", c[count - 2]);
				printf(" ");
			}
		}
	}

	fclose(fp);
	return 0;
}

int centiped() {
	int c[18];
	int count = 0;
	FILE *fp;
	int offset = 0;

	if ((fp = fopen("nvram/centiped/earom", "r")) == NULL) {
		printf("Sorry, I can't open nvram/centiped/earom\n");
		return 1;
	}

	/* Read file into memory */
	for (count = 0; count < 18; count++) {
		c[count] = getc(fp);

		if (count > 8) {
			/* Initials */
			if (c[count] == 0x00) {
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
		offset = count * 3;

		/* Score (packed binary-coded decimal) */
		printf("%02x", c[offset + 2]);
		printf("%02x", c[offset + 1]);
		printf("%02x", c[offset]);

		printf(" ");

		/* Initials */
		printf("%c", c[offset + 9]);
		printf("%c", c[offset + 10]);
		printf("%c", c[offset + 11]);

		printf("\n");
	}

	return 0;
}

int tempest() {
	int c[18];
	int count = 0;
	FILE *fp;
	int offset = 0;

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
		offset = count * 3;

		/* Score (packed binary-coded decimal) */
		printf("%02x", c[offset]);
		printf("%02x", c[offset + 1]);
		printf("%02x", c[offset + 2]);

		printf(" ");

		/* Initials */
		printf("%c", c[offset + 9]);
		printf("%c", c[offset + 10]);
		printf("%c", c[offset + 11]);

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

	if (strcmp(argv[1], "astdelux") == 0) {
		return astdelux();
	} else if (strcmp(argv[1], "centiped") == 0) {
		return centiped();
	} else if (strcmp(argv[1], "tempest") == 0) {
		return tempest();
	} else {
		printf("Sorry, I don't recognise \"%s\"\n", argv[1]);
	}

	return 1;
}
