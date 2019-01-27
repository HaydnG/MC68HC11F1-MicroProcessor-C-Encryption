
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Keys.h"

void main(){


	char table[6][6]; 
	void fillTable(char[37], char[6][6]);
	char string[37];
	void OutputArray(char[6][6]), padTable(char[6][6]);

	
	printf("Enter a string(Max 36 chars): \n");
	fgets(string, 37, stdin);
	
	padTable(table); /* Fill table with spaces*/
	fillTable(string, table); /* Fill table with inputted string*/
	
	OutputArray(table);

}

void padTable(char table[6][6]){
	int i, j;
	for(i = 0; i < 6; i ++){
		for(j = 0; j < 6; j ++){
			table[i][j] = ' ';
		}
	}

}

void fillTable(char string[37], char table[6][6]){

	int i,row, column;
	row = 0;
	column = 0;
	
	for(i = 0; i <= 36; i++){
		if(row >= 6){
			row = 0;
			column++;
		}
		table[column][row] = string[i];
		row++;
		
	}
	
}

void OutputArray(char Pointer[6][6]){
	int i, j;


	printf("\n\r[");
	for(i = 0; i < 6;i++){
		for(j = 0; j < 6;j++){
		printf("[%c]",Pointer[i][j]);
	
		}
		printf("\n");
	
	}
	printf("]\n\r\n\r");
	
	
}

