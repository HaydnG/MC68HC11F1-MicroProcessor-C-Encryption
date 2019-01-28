
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Keys.h"

void main(){


	char table[6][6],string[37], tableEncrypted[6][6];
	void fillTable(char[37], char[6][6]),OutputArray(char[6][6]),encryptTable(char [6][6], char [6][6], int [6]), convertToString(char [6][6], char [37]);
	int keyID, *Key,i;


	clearString(string); /*Pad the string out with spaces, to clear the memory*/
	
	
	/*Get interger between 1-720(inclusive) for KeyID*/
	keyID = 0;
	do{
		printf("Enter a Key ID(1-720): ");
		scanf("%d", &keyID);
		fflush(stdin);
	}while(keyID < 1 || keyID > 720);
	
	printf("KeyID: %d\n", keyID);
	
	Key = Keys[keyID];
	
	
	/*Get string of length 36, 37 including end of string char*/
	printf("Enter a string(Max 36 chars): ");
	if(fgets(string, 37, stdin) !=NULL){
		printf("\n\nThe string entered was: %s", string);
	}
	
	/*Pass 1*/
	fillTable(string, table); /* Fill table with inputted string*/
	encryptTable(table, tableEncrypted, Key);
	convertToString(tableEncrypted, string);

	/*Pass 2*/
	fillTable(string, table);
	encryptTable(table, tableEncrypted, Key);
	convertToString(tableEncrypted, string);


	printf("\nEncrypted string: %s\n", string);


}

void convertToString(char table[6][6], char string[37]){
	int row, letter, count;
	count = 0;
	for(row = 0;row< 6; row++){
		for(letter = 0; letter < 6; letter++){
					
			string[count] = table[row][letter];						
			count++;
		}		
	}
	string[37] = '\0'; /*End string*/
}

void encryptTable(char table[6][6], char encryptedTable[6][6], int Key[6]){
	int i,j;
	
	for(i = 0; i < 6; i++){			
		for(j = 0; j < 6; j++){
			encryptedTable[i][j] = table[Key[i]-1][j];	/* move the contents of the table into the encrypted table, in the order of the key*/
		}		
	}
}

void clearString(char string[37]){
	int i;
	
	for(i = 0;i<37;i++){
		string[i] = ' ';
	}
	string[37] = '\0';
}

void fillTable(char string[37], char table[6][6]){
	int i,row, column;
	row = 0;
	column = 0;
	
	for(i = 0; i < 36; i++){
		if(row >= 6){ 								/*Calculate rows and columns of table to put the contents of the string in the correct place*/
			row = 0;
			column++;
		}
		if(string[i] == '\n' || string[i] == '\0'){ /* Remove new line and end of string character. The end of string char will be added
														back when re-building the string*/
			string[i] = ' ';
		}
		
		table[row][column] = string[i];
		row++;		
	}	
}

void OutputArray(char table[6][6]){
	int i, j;

	for(i = 0; i < 6;i++){
		for(j = 0; j < 6;j++){
			printf("[%c]",table[j][i]);
	
		}
		printf("\n");
	
	}
	printf("\n\r\n\r");		
}

