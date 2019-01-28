#include <stdio.h>
#include <stdlib.h>

unsigned char Mgetchar();
int Mputchar(unsigned char);
char *Mgets(char*);

void main(){

	char StringAlloc[36],*String;
	unsigned char *portA,*ddrA;
	unsigned int j,last,option;
	portA=(unsigned char *)0x00;	/*Cast values into pointers*/
	ddrA=(unsigned char *)0x01;	
	
	
	*ddrA = 0x06;
	
	String = StringAlloc;
	
	
	while(1){
		/*for(j=0;j<0xfff;j++);  /*Delay*/
		
		
		
		if((*portA & 0x01)==0){ /*Mode select*/
			printf("\rEncryption Selected");
			printf("\n\nEnter an Encrpytion key: ");
			String = Mgets(String);
			
			if(String != 0){
				printf("\nInputted string: %s",String);
			}
			
			
		}else if(*portA & 0x01){
			printf("\rDecryption Selected");
			printf("\n\nEnter a Decryption key: ");
			String = Mgets(String);
			
			if(String != 0){
				printf("Inputted string: %s",String);
			}
			
			
		}
		
		printf("\r\n\n");
		printf("##########################################\n\n");

	}
	
	
	

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
