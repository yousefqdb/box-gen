#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GLYPH_LEN 3
const char * glyphs[6] = {"═", "║", "╔", "╗", "╚", "╝"};

int main(int argc, char ** argv)
{
	if (argc != 4) {
		puts("Usage: ./box-gen <rows> <cols> <text>\n");
		return 2;
	}

	int rows, cols, text_row, text_col, text_len;
	rows = atoi(argv[1]);
	if (rows < 3) rows = 3;
	cols = atoi(argv[2]);
	if (cols < 3) cols = 3;
	text_len = strlen(argv[3]);
	if (text_len > cols - 2) {
		puts("Text is too long to fit in the box.\n");
		return 2;
	}
   

	int outer_strlen = cols * GLYPH_LEN;
	int inner_strlen = cols + GLYPH_LEN * 2;
	char * outer_string = malloc(outer_strlen + 2);
	char * inner_string = malloc(inner_strlen + 2);
	char * text_string = malloc(inner_strlen + 2);

	outer_string[outer_strlen] = '\n';
	outer_string[outer_strlen + 1] = '\0';
	inner_string[inner_strlen] = '\n';
	inner_string[inner_strlen + 1] = '\0';
	text_string[inner_strlen + 1] = '\0';

	strcpy(outer_string, glyphs[2]);
	for (int i = 1; i < cols - 1; ++i)
		strcpy(outer_string + i * GLYPH_LEN, glyphs[0]);
	strcpy(outer_string + (cols - 1) * GLYPH_LEN, glyphs[3]);

	strcpy(inner_string, glyphs[1]);
	memset(inner_string + GLYPH_LEN, ' ', cols - 2);
	strcpy(inner_string + GLYPH_LEN + cols - 2, glyphs[1]);
	strcpy(text_string, inner_string);
	int text_offset = (cols - 2 - text_len) / 2;
	strncpy(text_string + GLYPH_LEN + text_offset, argv[3], text_len);

	puts(outer_string);

	int nr_before = rows / 2 - 1;
	int nr_after = rows - nr_before - 3;
	for (int i = 0; i < nr_before; ++i) puts(inner_string);
	puts(text_string);
	for (int i = 0; i < nr_after; ++i) puts(inner_string);

	strncpy(outer_string, glyphs[4], GLYPH_LEN);
	strncpy(outer_string + (cols - 1) * GLYPH_LEN, glyphs[5], GLYPH_LEN);
	puts(outer_string);

	free(outer_string);
	free(inner_string);
	free(text_string);

	return 0;
}
