
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*A header file containing the definition of the keys*/

void main(){

	char string[37];
	void Cipher(char[37], int[6], int), GenCodes(int *), SplitNum(int, int*), clearString(char *);
	int keyID, Key[6],counter, Keys[720];

	clearString(string); /*Pad the string out with spaces, to clear the memory, the string can then be inserted into a clear array*/
	
	
	GenCodes(Keys); /*Generate all cipher codes*/
	
	/*Get interger between 1-720(inclusive) for KeyID*/	
	keyID = 0;
	do{
		printf("Enter a Key ID(1-719): ");
		scanf("%d", &keyID);
		fflush(stdin);
	}while(keyID < 1 || keyID > 719);
	

	SplitNum(Keys[keyID], Key); /*split the six digit key into an array */
	
	/*Get string of length 36, 37 including end of string char*/
	printf("Enter a string(Max 36 chars): ");
	if(fgets(string, 37, stdin) !=NULL){
		printf("\n\nThe string entered was: %s", string);
	}
	
	/*Encrypt Pass 1*/
	Cipher(string, Key, 1);
	/*Encrypt Pass 2*/
	Cipher(string, Key, 1);
	
	printf("\nEncrypted string: %s\n", string);
	
	/*Decrypt Pass 1*/
	Cipher(string, Key, 2);	
	/*Decrypt Pass 2*/
	Cipher(string, Key, 2);
	
	printf("\nDecrypted string: %s\n", string);
	
}

void Cipher(char string[37], int Key[6], int mode){
	char table[6][6], tableOutput[6][6];
	void fillTable(char[37], char[6][6], int),applycipher(char [6][6], char [6][6], int [6]), TableToString(char [6][6], char [37],int);
	
	fillTable(string, table, mode); /* Fill table by columns with inputted string*/
	applycipher(table, tableOutput, Key); 
	TableToString(tableOutput, string, mode);
}

void fillTable(char string[37], char table[6][6],int mode){
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
		
		if(mode == 1){ /* Determines wether to sort the message into rows or columns depending on if its decrypting or encrpyting*/
			table[row][column] = string[i];
		}else{
			table[column][row] = string[i];
		}
		
		row++;		
	}	
}

void applycipher(char table[6][6], char encryptedTable[6][6], int Key[6]){
	int i,j;
	
	for(i = 0; i < 6; i++){			
		for(j = 0; j < 6; j++){
			encryptedTable[i][j] = table[Key[i]-1][j];	/* move the contents of the table into the encrypted table, in the order of the key*/
		}		
	}
}

void TableToString(char table[6][6], char string[37], int mode){
	int row, column, count;
	count = 0;
	for(row = 0;row< 6; row++){
		for(column = 0; column < 6; column++){
					
			if(mode == 1){ /*Read table column by column*/
				string[count] = table[row][column];		
			}else{	 /*Read table row by row*/
				string[count] = table[column][row];		
			}		
							
			count++;
		}		
	}
	string[37] = '\0'; /*End string*/
}

void clearString(char string[37]){
	int i;
	
	for(i = 0;i<37;i++){
		string[i] = ' ';
	}
	string[37] = '\0';
}

void SplitNum(int Num, int * Arr){
	
	Arr[0] = Num / 100000;
	Num = Num % 100000;
	
	Arr[1] = Num / 10000;
	Num = Num % 10000;
	
	Arr[2] = Num / 1000;
	Num = Num % 1000;
	
	Arr[3] = Num / 100;
	Num = Num % 100;
	
	Arr[4] = Num / 10;
	Num = Num % 10;
	
	Arr[5] = Num;

}

void GenCodes(int *Keys){
	int a, b, c, d, e, f, counter;	
	counter = 0;
	
	for(a = 1; a <=6;a++){
		for(b = 1; b <=6;b++){
			for(c = 1; c <=6;c++){
				for(d = 1; d <=6;d++){
					for(e = 1; e <=6;e++){
						for(f = 1; f <=6;f++){	
														
							if((a != b) && (a != c) && (a != d) && (a != e) && (a != f)){																
								if((b != c) && (b != d) && (b != e) && (b != f)){																			
									if((c != d) && (c != e) && (c != f)){																		
										if((d != e) && (d != f)){										
											if((e != f)){
		
												Keys[counter] = 0;
												Keys[counter] += a * 100000;
												Keys[counter] += b * 10000;	
												Keys[counter] += c * 1000;
												Keys[counter] += d * 100;
												Keys[counter] += e * 10;											
												Keys[counter] += f;	
												counter++;																										
							}}}}}				
	}}}}}}	
}
