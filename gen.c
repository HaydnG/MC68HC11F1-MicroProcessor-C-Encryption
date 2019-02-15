

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*A header file containing the definition of the keys*/

void main(){
	int Keys[720];
	
	GenCodes(Keys);
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
												printf("\n%d", Keys[counter]);
												counter++;																										
											}								
										}							
									}							
								}																
							}	
						}	
					}
				}
			}
		}
	}	
}
