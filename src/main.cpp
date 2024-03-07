#import "iostream"
#import "windows.h"
#import "stdio.h"

using namespace std;

bool hasOFlag = false, hasEFlag = false, hasBFlag = false;
// O: Only for show.
// E: Make the file empty.
// B: Show binary

void printFile(const char * filePath) {
	FILE * file = fopen(filePath, "r");

	if(file == NULL) {
		if (access(filePath, F_OK) != -1) {
			printf("Can't be opened.\n");
		} else {
			printf("The file does not exist.\n");
		}
		return ;
	}
	if(access(filePath, R_OK) == -1) {
		printf("The file is not readable.\n");
		fclose(file);
		return ;
	}

	char buffer[1000];
	while(fgets(buffer, 1000, file) != NULL) {
		printf("%s", buffer);
	}

	fclose(file);
	return ;
}

void emptyFile(const char * filePath) {
	FILE *file = fopen(filePath, "w");

	if(file == NULL) {
		if (access(filePath, F_OK) != -1) {
			printf("Can't be empty.\n");
		} else {
			printf("The file does not exist.\n");
		}
		return ;
	}
	if(access(filePath, R_OK) == -1) {
		printf("The file is not writable.\n");
		fclose(file);
		return ;
	}

	return ;
}

void printFileBinary(const char *filePath) {
    FILE *file = fopen(filePath, "rb");

    if(file == NULL) {
		if (access(filePath, F_OK) != -1) {
			printf("Can't be opened.\n");
		} else {
			printf("The file does not exist.\n");
		}
		return ;
	}
    if(access(filePath, R_OK) == -1) {
		printf("The file is not readable.\n");
		fclose(file);
		return ;
	}

    unsigned char buffer[1000];
    size_t bytesRead;
    while((bytesRead = fread(buffer, 1, 1000, file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            printf("%d ", buffer[i]);
        }
        cout << endl;
    }

    fclose(file);
}

int main(int argc, char ** argv) {
	for(int i = 1; i < argc; i ++) {
		if(strcmp(argv[i], "-O") == 0) {
			hasOFlag = true;
		}
		if(strcmp(argv[i], "-E") == 0) {
			hasEFlag = true;
		}
		if(strcmp(argv[i], "-B") == 0) {
			hasBFlag = true;
		}
	}

	char * ContinueFile = argv[argc - 1];

	if(hasOFlag) {
		printFile(ContinueFile);
	}
	if(hasEFlag) {
		cout << "Do you want to clear it? [Y(es), N(o)] : ";
		char t = getchar();
		if(t == 'Y') emptyFile(ContinueFile);
	}
	if(hasBFlag) {
		printFileBinary(ContinueFile);
	}

	return 0;
}
