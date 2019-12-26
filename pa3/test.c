#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[])
{
	int num_trees;
	int size;

	printf("Enter the number of trees to print (must be greater than 0): \n");
	scanf("%d", &num_trees);
	while(num_trees < 1)
	{
		printf("Invalid entry\n");
		printf("Enter the number of trees to print (must be greater than 0): \n");
	}

	printf("Enter the size of one tree (must be greater than 1): \n");
	scanf("%d", &size);
	while(size < 1)
	{
		printf("Invalid entry\n");
		printf("Enter the size of one tree (must be greater than 1): \n");
	}

	char* tree_top = " /\\   ";
	char* level = "/  \\  ";
	char* base = "----  ";
	char* trunk = " ||   ";
	int num_trunks = size / 2;

	for(int h = 0; h < num_trees; h++)
	{
		printf(tree_top);
	}
	printf("\n");
	for(int j = 0; j < size - 1; j++)
	{
		for(int k = 0; k < num_trees; k++)
		{
			printf(level);
		}
		printf("\n");
	}

	for(int v = 0; v < num_trees; v++)
	{
		printf(base);
	}
	printf("\n");

	for(int a = 0; a < num_trunks; a++)
	{
		for(int b = 0; b < num_trees; b++)
		{
			printf(trunk);
		}
		printf("\n");
	}

}