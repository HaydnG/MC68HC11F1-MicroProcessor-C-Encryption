#include <stdio.h>
#include <stdlib.h>

void clearString(), Cipher();

void main(){

	char String[37];
	unsigned char *portA,*ddrA;
	int option;
	
	portA=(unsigned char *)0x00;	/*Port A Data register*/
	ddrA=(unsigned char *)0x01;	  /*Port A Data Direction register*/
	
	*ddrA = 0x06; /* PortA Input=0/Output=1      [0][1 Decrypt LED][1 Encrypt LED][0] */
	
	clearString(String); /*Pad/Clear the memory*/
	
	while(1){
		
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
		
		if(fgets(String, 37, stdin) !=NULL){
			printf("\n\nThe string entered was: %s", string);
			
			Cipher();
			
			*portA = (option+1) << 1; /*Turn on led depending on the value of option*/
			
			for(j=0;j<0xffff;j++);
		}
		
		
		
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

