#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// For Windows
#if defined(_WIN32)
#include <direct.h>
#define CREATE_DIR(name) _mkdir(name)
// For Unix/Linux, macOS
#else
#include <sys/stat.h>
#include <unistd.h>
#define CREATE_DIR(name) mkdir(name, 0700)
#endif

#define MAX_TEXT_LENGTH 1024

// Global Variables
char _dirName[MAX_TEXT_LENGTH] = "";
char _currentDirPath[MAX_TEXT_LENGTH] = "";

void cls() { system("cls"); }
void new_line() { printf("\n"); }

void create_dir();
void create_files(bool newDirCreated);
void create_a_file(char *_fileName, int type);

int main(int argc, char *argv[]) {
  char wtd;
  while (1) {
    bool exit = false;
    printf("Do you want to create a folder or not? y/n\n");
    scanf_s(" %c", &wtd);
    cls();
    switch (wtd) {
    case 'y':
      create_dir();
      new_line();
      create_files(true);
      exit = true;
      break;
    case 'n':
      create_files(false);
      exit = true;
      break;
    default:
      cls();
      printf("Please enter either 'y' or 'n'\n");
      break;
    }
    if (exit) {
      break;
    }
  }
  return 0;
}

void create_dir() {
  printf("Name the folder: \n");
  scanf_s("%s", _dirName);
  if (CREATE_DIR(_dirName) == 0) {
    printf("Folder '%s' created successfully.\n", _dirName);
  } else {
    printf("Error occured when trying to create the folder.\n");
    return;
  }
  return;
}

void create_a_file(char *_fileName, int type) {
  char fileName[MAX_TEXT_LENGTH] = "";
  char templateTextBuffer[MAX_TEXT_LENGTH] = "";
  FILE *fptr = NULL;
  FILE *file = NULL;

  snprintf(fileName, sizeof(fileName), "%s", _fileName);

  switch (type) {
  case 0:
    strncat_s(fileName, MAX_TEXT_LENGTH, ".html", 5);
    if (fopen_s(&fptr, "Templates/html.html", "r") != 0) {
      printf("Error opening template file html.html\n");
      return;
    }
    break;
  case 1:
    strncat_s(fileName, MAX_TEXT_LENGTH, ".css", 4);
    if (fopen_s(&fptr, "Templates/css.css", "r") != 0) {
      printf("Error opening template file css.css\n");
      return;
    }
    break;
  case 2:
    strncat_s(fileName, MAX_TEXT_LENGTH, ".js", 3);
    if (fopen_s(&fptr, "Templates/js.js", "r") != 0) {
      printf("Error opening template file js.js\n");
      return;
    }
    break;
  default:
    printf("Error: Unknown file type.\n");
    return;
  }

  size_t bytesRead = fread(templateTextBuffer, 1, MAX_TEXT_LENGTH - 1, fptr);
  templateTextBuffer[bytesRead] = '\0';
  fclose(fptr);

  if (fopen_s(&file, fileName, "w") != 0) {
    printf("Error creating file %s\n", fileName);
    return;
  }

  if (fprintf(file, "%s", templateTextBuffer) < 0) {
    printf("Error writing to file %s\n", fileName);
    fclose(file);
    return;
  }

  fclose(file);
  printf("File %s created successfully.\n", fileName);
}

void create_files(bool newDirCreated) {
  char fileName[MAX_TEXT_LENGTH];
  char temp[MAX_TEXT_LENGTH];
  const char *fileTypes[] = {"HTML", "CSS", "JS"};
  if (newDirCreated && _dirName[strlen(_dirName) - 1] != '/') {
    strncat_s(_dirName, MAX_TEXT_LENGTH, "/", 1);
  }
  for (int i = 0; i < 3; i++) {
    printf("Enter the %s filename: \n", fileTypes[i]);
    scanf_s("%s", temp, (unsigned)sizeof(temp));
    // Initialize fileName with dirName
    if (strcpy_s(fileName, MAX_TEXT_LENGTH, _dirName) != 0) {

      printf("Error: Failed to copy directory name\n");
      continue;
    }

    // Append temp to fileName
    if (strncat_s(fileName, MAX_TEXT_LENGTH, temp, strlen(temp)) != 0) {
      printf("Error: Failed to append filename\n");
      continue;
    }

    create_a_file(fileName, i);
    new_line();
  }
}
