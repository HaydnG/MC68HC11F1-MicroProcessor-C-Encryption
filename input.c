#include <stdio.h>
#include <stdlib.h>

unsigned char Mgetchar();
int Mputchar(unsigned char);
char *Mgets(char*);
void clearString(), Cipher();

void main(){

	char String[37];
	unsigned char *portA,*ddrA;
	unsigned int j,last,option;
	portA=(unsigned char *)0x00;	/*Port A Data register*/
	ddrA=(unsigned char *)0x01;	  /*Port A Data Direction register*/
	
	*ddrA = 0x06; /* PortA Input=0/Output=1      [0][1 Decrypt LED][1 Encrypt LED][0] */
	
	clearString(String); /*Pad/Clear the memory*/
	
	while(1){
		/*for(j=0;j<0xfff;j++);  /*Delay*/
		
		*portA = 0x0; /*Turn LEDs off*/
		
		option = *portA & 0x01;
		
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
		
		String = Mgets(String);
		
		if(String != 0){
				printf("\nInputted string: %s",String);
		}

		*portA = (option+1) << 1; /*Turn on led depending on the value of option*/
		
		printf("\r\n\n");
		printf("##########################################\n\n");

	}
	
	
	

}

void Cipher(){
	for(j=0;j<0xffff;j++);

}

void clearString(char string[37]){
	int i;
	
	for(i = 0;i<37;i++){
		string[i] = ' ';
	}
	string[37] = '\0';
}

char *Mgets(char *pointer, int Maxlength){
	char *String;
	int Input, length;
	length = 1;

	while(1){
		if(length >= Maxlength){
			break;
		}
		
		if ((Input = Mgetchar()) == EOF){
			return (0);
		}
			
		if (Input == '\n' || Input == '\r'){
			break;
		}else{
			*String++ = Input;
			length++;
		}	
	}
	
	
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
