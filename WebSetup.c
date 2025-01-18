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
void update_html_references(const char *, const char *, const char *);

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
  char fullFileNames[3][MAX_TEXT_LENGTH] = {0}; // Store complete file paths

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

    // Store the complete file path
    strcpy_s(fullFileNames[i], MAX_TEXT_LENGTH, fileName);

    create_a_file(fileName, i);
    new_line();
  }

  // Add file extensions to the stored paths
  strncat_s(fullFileNames[0], MAX_TEXT_LENGTH, ".html", 5);
  strncat_s(fullFileNames[1], MAX_TEXT_LENGTH, ".css", 4);
  strncat_s(fullFileNames[2], MAX_TEXT_LENGTH, ".js", 3);

  // Update the HTML file with references to CSS and JS
  update_html_references(fullFileNames[0], fullFileNames[1], fullFileNames[2]);
}

void update_html_references(const char *htmlFileName, const char *cssFileName,
                            const char *jsFileName) {
  FILE *htmlFile = NULL;
  char fileContent[MAX_TEXT_LENGTH * 2] = ""; // Doubled buffer size for safety
  char newContent[MAX_TEXT_LENGTH * 2] = "";  // Buffer for the modified content
  char *headPos = NULL;
  char *bodyEndPos = NULL;

  // Open the HTML file for reading
  if (fopen_s(&htmlFile, htmlFileName, "r") != 0) {
    printf("Error opening HTML file for reading\n");
    return;
  }

  // Read the entire content
  size_t bytesRead = fread(fileContent, 1, sizeof(fileContent) - 1, htmlFile);
  fileContent[bytesRead] = '\0';
  fclose(htmlFile);

  // Create the CSS, JS and jQuery reference strings
  char title[MAX_TEXT_LENGTH] = "";
  char cssLink[MAX_TEXT_LENGTH] = "";
  char jsScript[MAX_TEXT_LENGTH] = "";
  char jQScript[MAX_TEXT_LENGTH] =
      "  <script "
      "src=\"https://cdnjs.cloudflare.com/ajax/libs/jquery/3.7.1/"
      "jquery.min.js\" "
      "integrity=\"sha512-v2CJ7UaYy4JwqLDIrZUI/"
      "4hqeoQieOmAZNXBeQyjo21dadnwR+8ZaIJVT8EE2iyI61OV8e6M8PP2/4hpQINQ/"
      "g==\" crossorigin =\"anonymous\" referrerpolicy=\"no-referrer\" "
      "></script>\n";

  // Extract just the filenames without the directory path
  const char *cssBaseFileName =
      strrchr(cssFileName, '/') ? strrchr(cssFileName, '/') + 1 : cssFileName;
  const char *jsBaseFileName =
      strrchr(jsFileName, '/') ? strrchr(jsFileName, '/') + 1 : jsFileName;
  const char *htmlBaseFileName = strrchr(htmlFileName, '/')
                                     ? strrchr(htmlFileName, '/') + 1
                                     : htmlFileName;

  // Extract the HTML filename without the extension
  const char *lastDot = strrchr(htmlBaseFileName, '.');
  char baseNameWithoutExt[MAX_TEXT_LENGTH];
  size_t length =
      lastDot ? (size_t)(lastDot - htmlBaseFileName) : strlen(htmlBaseFileName);
  strncpy_s(baseNameWithoutExt, MAX_TEXT_LENGTH, htmlBaseFileName, length);
  baseNameWithoutExt[length] = '\0';

  snprintf(title, sizeof(title), "  <title>%s</title>\n", baseNameWithoutExt);
  snprintf(cssLink, sizeof(cssLink),
           "  <link rel=\"stylesheet\" href=\"%s\">\n", cssBaseFileName);
  snprintf(jsScript, sizeof(jsScript), "    <script src=\"%s\"></script>\n",
           jsBaseFileName);

  // Find the </head> and </body> tags in the content
  headPos = strstr(fileContent, "</head>");
  bodyEndPos = strstr(fileContent, "</body>");

  if (headPos == NULL || bodyEndPos == NULL) {
    printf("Error: Could not find required HTML tags\n");
    return;
  }

  // Calculate positions for insertion
  size_t headInsertPos = headPos - fileContent;
  size_t bodyInsertPos = bodyEndPos - fileContent;

  // Create the new content with the references
  // First copy up to head closing tag
  strncpy_s(newContent, sizeof(newContent), fileContent, headInsertPos);

  // Add <title>
  strncat_s(newContent, sizeof(newContent), title, strlen(title));
  // Add CSS link
  strncat_s(newContent, sizeof(newContent), cssLink, strlen(cssLink));

  // Add jQuery link
  // NOTE: Make this optional
  strncat_s(newContent, sizeof(newContent), jQScript, strlen(jQScript));

  // Add everything up to body closing tag
  strncat_s(newContent, sizeof(newContent), headPos,
            bodyInsertPos - headInsertPos);
  // Add JS script
  strncat_s(newContent, sizeof(newContent), jsScript, strlen(jsScript));
  // Add the rest of the content
  strncat_s(newContent, sizeof(newContent), bodyEndPos, strlen(bodyEndPos));

  // Open the file for writing
  if (fopen_s(&htmlFile, htmlFileName, "w") != 0) {
    printf("Error opening HTML file for writing\n");
    return;
  }

  // Write the modified content back to the file
  if (fprintf(htmlFile, "%s", newContent) < 0) {
    printf("Error writing to HTML file\n");
    fclose(htmlFile);
    return;
  }

  fclose(htmlFile);
  printf("Successfully updated HTML file with CSS and JS references\n");
}
