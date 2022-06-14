#include <stdio.h>
#include <stdlib.h>

void main(){
	
	FILE *f;
        f=fopen("output.txt","r");
        char data[200];
        
        while (!feof(f)){
        	fscanf(f,"%s",data); 
        	printf("%s",data);
        }
}
