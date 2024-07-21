#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[25];
	int stock;
	int stock_arr;
}info_t;

int rBinarySearch(FILE* b_fp, char *word, int bottom, int top)
{
	int middle;
	info_t item;
	while (bottom <= top)
	{
		middle = (bottom + top) / 2;
		fseek(b_fp, middle * sizeof(info_t), SEEK_SET);
		fread(&item, sizeof(info_t), 1, b_fp);

		if (strcmp(item.name, word) == 0)
			return middle;
		else
		{
			if (strcmp(item.name, word) == 1)
			{
				return rBinarySearch(b_fp, word, bottom, top - 1);
			}
			else
				return rBinarySearch(b_fp, word, bottom + 1, top);
		}
	}
	return -1;
}

int main()
{
	FILE* b_fp = fopen("items.bin", "rb");
	if (b_fp == NULL)
		printf("This file does not exist!");
	else
	{
		fseek(b_fp, 0, SEEK_END);
		int top = ftell(b_fp) / sizeof(info_t) - 1;
		int bottom = 0;
		int index;
		char word[25];
		
		printf("There are %d items in the list\n", top + 1);

		printf("Enter an item to search: ");
		scanf("%[^\n]", word);

		
		index = rBinarySearch(b_fp, word, bottom, top);

		if (index != -1)
		{
			info_t item;
			fseek(b_fp, index * sizeof(info_t), SEEK_SET);
			fread(&item, sizeof(info_t), 1, b_fp);
			printf("\nbottom: %d, top: %d, middle: %d; %s", bottom, top, index, word);
			printf("\n%s found with %d stocks and %d stocks will arrive", item.name, item.stock, item.stock_arr);
		}
		else
			printf("Item not found!");
	}
}
