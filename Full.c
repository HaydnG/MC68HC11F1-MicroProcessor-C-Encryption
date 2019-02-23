#include <stdio.h>
#include <stdlib.h>

unsigned char Mgetchar();
int Mputchar(unsigned char);
char *Mgets(char*, int);
void OutputArray(char[6][6]);

void main(){

	char string[37];
	unsigned char *portA,*ddrA;
	int option, keyID, Key[6], Keys[720];
	unsigned int j,i;
	
	void Cipher(char[37], int[6], int), GenCodes(int *), SplitNum(int, int*), clearString(char *);

	
	portA=(unsigned char *)0x00;	/*Port A Data register*/
	ddrA=(unsigned char *)0x01;	  /*Port A Data Direction register*/
	
	*ddrA = 0x06; /* PortA Input=0/Output=1      [0][1 Decrypt LED][1 Encrypt LED][0] */
	
		
	GenCodes(Keys); /*Generate all cipher codes*/
	
	while(1){
		
		clearString(string); /*Pad the string out with spaces, to clear the memory, the string can then be inserted into a clear array*/
		
		/*Get interger between 1-720(inclusive) for KeyID*/	
		
		keyID = 0;
		do{
			printf("Enter a Key ID(1-719): ");
			scanf("%d", &keyID);
		}while(keyID < 1 || keyID > 719);
		
		
		
		SplitNum(Keys[keyID], Key); /*split the six digit key into an array */	/*##COMMENT OUT TO OVERRIDE KEY, THEN SET KEY ARRAY*/
		

		printf("\n"); /*Debugging to print key*/
		for(j = 0; j < 6; j ++){
			printf("[%d]", Key[j]);
		}
		printf("\n\n");
		
		option = *portA & 0x01; /* Read switch value*/
		
		switch(option){
			case 0:
				printf("\rEncryption Selected");
				printf("\n\nEnter an Encrpytion key: ");
				break;
			case 1:
				printf("\rDecryption Selected");
				printf("\n\nEnter a Decryption key: ");
				break;
		}
		
		if(Mgets(string,37) !=NULL){
			printf("\n\nThe string entered was: %s", string);
			
			/*Encrypt Pass 1*/
			Cipher(string, Key, option);
			/*Encrypt Pass 2*/
			Cipher(string, Key, option);
			
			printf("\nOutput string: %s\n", string);
								
			*portA = (option+1) << 1; /*Turn on led depending on the value of option*/
			
			for(j=0;j<0x7fff;j++);
			for(j=0;j<0x7fff;j++);
			
			*portA = *portA & (0x1); /*Turn LEDs off*/
		}
		
		
		printf("\r\n\n");
		printf("##########################################\n\n");

	}

}

void Cipher(char string[37], int Key[6], int mode){
	char table[6][6], tableOutput[6][6];
	void fillTable(char[37], char[6][6], int),applycipher(char [6][6], char [6][6], int [6]), TableToString(char [6][6], char [37],int);
	int j;
	
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
		
		if(mode == 0){ /* Determines wether to sort the message into rows or columns depending on if its decrypting or encrpyting*/
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
					
			if(mode == 0){ /*Read table column by column*/
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

void GenCodes(long int *Keys){
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

char *Mgets(char *pointer, int Maxlength){
	char *String;
	int Input, length;
	length = 0;
	String = pointer;

	while(1){
		if(length >= Maxlength){
			break;
		}
		
		if ((Input = Mgetchar()) == EOF){
			return (NULL);
		}
			
		if (Input == '\n' || Input == '\r'){
			break;
		}else{
			*String++ = Input;
			length++;
		}	
	}
	
	if (pointer == String)
		return (NULL);
	
	printf("\nlength: %d \n",length);
		
	*String = '\0';
	return (pointer);
}


unsigned char Mgetchar(){
	unsigned char *SCDR, *SCSR,data,returnhit;
		
	SCDR = (unsigned char*) 0x2F;
	SCSR = (unsigned char*) 0x2E;
	
	while(((*SCSR) & 0x20) == 0);
	data = *SCDR;
	Mputchar(data);
		
	return data;

}

int Mputchar(unsigned char input){
	unsigned char *SCDR,*SCSR;
	SCDR = (unsigned char*)0x2F;
	SCSR = (unsigned char*)0x2E;
	while(((*SCSR) & 0x80) == 0);
	*SCDR = input;
	return 1;	
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

