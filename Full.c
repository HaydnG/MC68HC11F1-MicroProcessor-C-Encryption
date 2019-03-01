#include <stdio.h>
#include <stdlib.h>

char *Mgets(char*, int, int), *clearString(char *);
void Cipher(char[37], int[6], int),initialisation();
int *SplitNum(long int, int *), *GetKey(long int *, int *), Msleep(long int), Mputchar(unsigned char),Mgetchar(long int, int), tick, leaptick;
long int * GenCodes(long int *), secs;

unsigned char *portA,*ddrA,*pactl, *tmsk2,*tflg2;

void initialisation(){
	portA=(unsigned char *)0x00;	/*Port A Data register*/
	ddrA=(unsigned char *)0x01;	  /*Port A Data Direction register*/	
	tmsk2 = (unsigned char*)0x24;
	pactl = (unsigned char*)0x26;
	tflg2 = (unsigned char*)0x25;
	
	leaptick = 0;
	secs = 0;
	tick = 0;
	*pactl = 0x03;   /*Set prescaler to maximum*/
	*tmsk2 = 0x40;   /*Enable RTI interrupt*/
	*ddrA = 0x06; /* PortA Input=0/Output=1      [0][1 Decrypt LED][1 Encrypt LED][0] */
		
	
}

void main()
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: clearString(), GetKey(), Mgets(), Cipher(), Msleep(), printf()
Purpose: Determine encryption/decryption, Read key ID, Read String, Apply Modified Double Columnar Transposition Cipher Algorithm, Wait
Version: 1.0
*/
{
	char string[37];	
	long int  Keys[720];
	int option, Key[6];
	
	unsigned int j;
	
	initialisation(); /*Set Data/Pointers*/
	GenCodes(Keys); /*Generate all cipher codes*/
	
	while(1){
			
		clearString(string); /*Pad the string out with spaces, to clear the memory, the string can then be inserted into a clear array*/
		
		GetKey(Keys,Key); /*##COMMENT OUT TO OVERRIDE KEY, THEN SET KEY ARRAY*/

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
		
		if(Mgets(string,36, 10) !=NULL){
			printf("\n\nThe string entered was: %s", string);
			
			/*Encrypt Pass 1*/
			Cipher(string, Key, option);
			/*Encrypt Pass 2*/
			Cipher(string, Key, option);
			
			printf("\nOutput string: %s\n", string);
								
			*portA = (option+1) << 1; /*Turn on led depending on the value of option*/
			
			Msleep(10); /*Sleep 5 seconds*/
			
			*portA = *portA & (0x1); /*Turn LEDs off*/
		}else{
			printf("\n10 Second timeout - Restarting");
		}	
		
		printf("\r\n\n");
		printf("##########################################\n\n");
	}
}

void Cipher(char string[37], int Key[6], int mode)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: filltable(), applycipher(), TableToString()
Purpose: A collection of the functins that carry out the encryption/decryption organised with the correct data inputs and called in the correct order.
Version: 1.0
*/
{
	char table[6][6], tableOutput[6][6];
	void fillTable(char[37], char[6][6], int),applycipher(char [6][6], char [6][6], int [6]), TableToString(char [6][6], char [37],int);
	int j;
	
	fillTable(string, table, mode); /* Fill table by columns with inputted string*/
	applycipher(table, tableOutput, Key); 
	TableToString(tableOutput, string, mode);
}

void fillTable(char string[37], char table[6][6],int mode)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Converts the string specified into a table.
			The mode determines wether to sort the message into rows or columns depending on if its decrypting or encrpyting
Version: 1.0
*/
{
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
		
		if(mode == 0){ /* Mode determines how to store data*/
			table[row][column] = string[i];
		}else{
			table[column][row] = string[i];
		}
		
		row++;		
	}	
}

void applycipher(char table[6][6], char encryptedTable[6][6], int Key[6])
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Moves the rows into another array in the order of the key specified
Version: 1.0
*/
{
	int i,j;
	
	for(i = 0; i < 6; i++){			
		for(j = 0; j < 6; j++){
			encryptedTable[i][j] = table[Key[i]-1][j];	/* move the contents of the table into the encrypted table, in the order of the key*/
		}		
	}
}

void TableToString(char table[6][6], char string[37], int mode)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Converts the Cipher table back to a string. 
		The mode determines to read column by column or row by row, depending on if its decrypting or encrypting
Version: 1.0
*/
{
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

char * clearString(char string[37])
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Pre-pads out the string to remove unwanted bits and to set to spaces.
Version: 1.0
*/
{
	int i;
	
	for(i = 0;i<37;i++){
		string[i] = ' ';
	}
	string[37] = '\0';
	
	return string;
}


int * GetKey(long int *Keys, int * Key)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: printf(), scanf(), SplitNum()
Purpose: Gets a key id from 1-719 and looks up the key in the generated list
Version: 1.0
*/
{
	int keyID;


	keyID = 0; /*Clear key*/		
	do{
		printf("\nEnter a Key ID(1-719): ");
		scanf("%d", &keyID);
	}while(keyID < 1 || keyID > 719);
			
	SplitNum(Keys[keyID], Key); /*split the six digit key into an array */

	return Key;

}

int * SplitNum(long int Num, int * Key)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Splits the long int key into individual ints stored inside an array for ease of use later in the algorithm
Version: 1.0
*/
{
	
	Key[0] = Num / 100000;
	Num = Num % 100000;
	
	Key[1] = Num / 10000;
	Num = Num % 10000;
	
	Key[2] = Num / 1000;
	Num = Num % 1000;
	
	Key[3] = Num / 100;
	Num = Num % 100;
	
	Key[4] = Num / 10;
	Num = Num % 10;
	
	Key[5] = Num;
	
	return Key;
}

long int * GenCodes(long int *Keys)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Generates list of keys for the modified double columnar transposition cipher algorithm to use.
Version: 1.0
*/
{
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
												Keys[counter] += (long int)a * 100000;
												Keys[counter] += (long int)b * 10000;	
												Keys[counter] += (long int)c * 1000;
												Keys[counter] += (long int)d * 100;
												Keys[counter] += (long int)e * 10;										
												Keys[counter] += (long int)f;	
												counter++;																										
							}}}}}				
	}}}}}}	
	
	return Keys;
}

char *Mgets(char *pointer, int Maxlength, int timelimit)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: Mgetchar()
Purpose: Custom gets function, only captures string for the specified time limit and length. 
		When ever a user enters a new character the timestamp is updated. if the user doesnt enter a key and the timelimit is reached null is returned
		Enables backspace to work.
Version: 1.0
*/
{
	char *String;
	int Input, length;
	long int timestamp;
	length = 0;
	String = pointer;
	
	timestamp = secs; /*Get time when function starts*/

	while(1){
		if(length >= (Maxlength+1)){ /*Add 1 to make room for end of string identifier*/
			break;
		}
		
		if ((Input = Mgetchar(timestamp, timelimit)) == EOF){
			return (NULL);
		}
		if(Input == -1){
			return (NULL);
		}
			
		if (Input == '\n' || Input == '\r'){
			break;
		}else if(Input == '\b'){ /*Allow backspace to work*/
			putchar(' ');
			putchar('\b');
			*String--;
			length--;
		}else{
			*String++ = Input;
			length++;			
		}
		timestamp = secs; /*Reset time stamp*/
	}
	
	if (pointer == String)
		return (NULL);
		
	*String = '\0';
	return (pointer);
}

int Mgetchar(long int timestamp, int timelimit)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: putchar()
Purpose: Custom Mgetchar function.
		Waits for input buffer or for the time to run out. If the time runs out and a character is not entered -1 is returned.
		If a character is returned the data is read in and the char gets returned.
		
Version: 1.0
*/
{
	unsigned char *SCDR, *SCSR,data;
		
	SCDR = (unsigned char*) 0x2F;
	SCSR = (unsigned char*) 0x2E;
	
	while((((*SCSR) & 0x20) == 0) && ((secs-timestamp) <= timelimit));
	
	if((((*SCSR) & 0x20) == 0) && ((secs-timestamp) >= timelimit)){
		return -1; /*Times up*/
	}
	
	data = *SCDR;
	
	if (data == '\r')
		data = '\n';
		
	return (putchar(data));

}

int Msleep(long int duration)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Wait a specified time
Version: 1.0
*/
{
	long int timestamp;
	int tock;
	timestamp = 0;
	
	tock = 0;
	timestamp = secs;
	printf("\n");
	while(secs-timestamp < duration){
		
		if(tick == 0 && tock == 0){
			printf("\rResetting: %ld",duration - (secs-timestamp));
			tock = 1;
		}
		if(tick == 1 && tock == 1){
			tock = 0;
		}
	}; 
	
	return duration;
}

@interrupt void timer(void)
/* Author Haydn Gynn
Company: Staffordshire University
Date: 27/02/2019
Functions used: None
Purpose: Keep track of time from when the program starts.
Version: 1.0
*/
{
	
	tick++;
	if(leaptick == 2){ /*Added leap tick which allows an extra tick every 2 seconds						
						Thiss increases accuracy and makes it tick closer to a second*/
		leaptick = 0;
		tick--;
	}
	
	if (tick == 30)
	{
		tick = 0;
		secs++;
		leaptick++;
	}
	
	*tflg2 = 0x40;                      /*Reset RTI flag*/
}

