#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define SET		(uint8_t)1
#define CLEAR	(uint8_t)0

int main(int argc, char **argv) {
	FILE *original, *modified;
	char character = 0x00;
	uint8_t flag_slash = CLEAR;
	
	if(argc != 3){
		fprintf(stderr, "<original mml file> <name of the converted mml file>\n");
		exit(EXIT_FAILURE);
	}
	
	original = fopen(argv[1], "rb");
	modified = fopen(argv[2], "wb");
	if(original == NULL || modified == NULL) {
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}
	
	while(1){
		character = fgetc(original);
		
		if(character == ' '){
			continue;
		}
		else if(character == '/'){
			if(flag_slash == SET){
				flag_slash = CLEAR;
				continue;
			}
			else{
				flag_slash = SET;
				continue;
			}
		}
		else if(character == '&'){
			continue;
		}
		else if(character == '\n' || character == '\r'){
			continue;
		}
		else if(character == EOF){
			break;
		}
		
		else{
			if(flag_slash == SET){
				continue;
			}
			
			fputc(character, modified);
		}
	}
	
	fclose(original);
	fclose(modified);
	return 0;
}
