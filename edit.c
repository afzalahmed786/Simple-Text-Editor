#include <stdio.h>
#include <string.h>


void edit_line(char* buffer, int current_line) {
	for (int i =0; i < current_line - 1; i++) {
	buffer = strchr(buffer, '\n') + 1;
	}

	char* line_end = strchr(buffer, '\n');
	char saved[1024] = {0};
	strcpy(saved, line_end);
	scanf("%s", buffer);
	strcpy(buffer + strlen(buffer), saved);
}

void append_line(char* buffer, int current_line) {
	for(int i = 0; i < current_line - 1; i++) {
		buffer = strchr(buffer, '\n') + 1;
	}
	char* line_end = strchr(buffer, '\n');
	char saved[1024] = {0};
	strcpy(saved, line_end);
	char s[1024] = {0};
	printf("Enter text to add: ");
	scanf("%s", s);
	strcpy(line_end, "\n"); 
	strcat(line_end, s);
	strcat(line_end, saved);

}

void delete_line(char* buffer, int current_line){
	char*start = buffer;
	for(int i = 0; i < current_line - 1; i++) {
                buffer = strchr(buffer, '\n') + 1;
        }
	//find start of next line
	char* next_line = strchr(buffer, '\n') + 1;
	if(next_line) {
		strcpy(buffer, next_line);
	} else {
		*start = '\0';
	}
}	
void main(int argc, char** argv) {
	FILE* f = fopen(argv[1], "r");
	char buffer[1024] = {0};
	fread(buffer, 1024, 1, f);
	fclose(f);
	printf("Contents: \n%s\n", buffer);
	printf("What does the user wan't to do? \na - append\nd- deletion\ns-subtitution\n");
	char choice = '0';
	scanf("%s",&choice);
	printf("Enter What line do you want to change: ");
	int current_line = 0;
	scanf("%d", &current_line);
	if(choice == 'a') {
		append_line(buffer, current_line);
	}
	else if(choice == 's') {
		edit_line(buffer, current_line);
	}
	else if(choice == 'd') {
		delete_line(buffer, current_line);
	}
	f = fopen(argv[1], "w");
	fwrite(buffer, strlen(buffer), 1, f);
	fclose(f);
	printf("Contents: \n%s\n", buffer);
}


