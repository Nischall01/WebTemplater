/*
 * WebTemplater
 * This program creates a basic web project structure with HTML, CSS, and JS
 * files. It supports both Windows and Unix-like systems and includes template
 * management
 */

#include <corecrt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// Platform-specific includes and definitions
#if defined(_WIN32)
#include <direct.h>
#include <windows.h>
#define CREATE_DIR(name) _mkdir(name) // Windows directory creation
#else
#include <sys/stat.h>
#include <unistd.h>
#define CREATE_DIR(name)                                                       \
  mkdir(name, 0700) // Unix directory creation with permissions
#endif

// Maximum length for text buffers
#define MAX_TEXT_LENGTH 2048

// Global variables for path management
char _dirName[MAX_TEXT_LENGTH] = "";           // Current working directory name
char _executableDirPath[MAX_TEXT_LENGTH] = ""; // Path to executable
char _templateDirPath[MAX_TEXT_LENGTH] = "";   // Path to template files

// Utility functions
void cls(void) { system("cls"); }     // Clear screen
void new_line(void) { printf("\n"); } // Print newline

// Function declarations
int create_dir(bool useCurrentDateInDirName);  // Creates project directory
void create_files(bool newDirCreated);         // Creates web files
void create_a_file(char *_fileName, int type); // Creates individual file
void update_html_references(const char *, const char *,
                            const char *); // Updates HTML with CSS/JS links
char *get_current_date(void);              // Gets formatted current date
char *get_executable_dir_path(void);       // Gets executable directory path
void init_executable_and_template_dir_path(void); // Initializes path variables

char *get_user_input(void) {
  static char _inputBuffer[MAX_TEXT_LENGTH] = ""; // User input buffer

  // Read the input into buffer
  if (fgets(_inputBuffer, sizeof(_inputBuffer), stdin) == NULL) {
    printf("Error reading input.\n");
    return NULL;
  }

  // Remove trailing newline if present
  size_t len = strlen(_inputBuffer);
  if (len > 0 && _inputBuffer[len - 1] == '\n') {
    _inputBuffer[len - 1] = '\0';
  }
  // Check if input might have been too long (buffer full without newline)
  else if (len == sizeof(_inputBuffer) - 1) {
    printf("Warning: Input may have been truncated.\n");
    // Clear input buffer to prevent overflow on next read
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
  }

  return _inputBuffer;
}

int main(int argc, char *argv[]) {
  cls();
  init_executable_and_template_dir_path();

  char *wtd = ""; // User choice variable
  while (1) {
    bool exit = false;

    // Main menu prompt
    printf("Do you want to create a folder or not? y/n\n");
    /* scanf_s(" %c", &wtd); */
    wtd = get_user_input();
    if (strlen(wtd) > 1) {
      cls();
      printf("Please enter either 'y' or 'n'\n");
      continue;
    }

    cls();

    // Subfolder creation with optional date prefix
    switch (wtd[0]) {
    case 'y':
      while (1) {
        printf("Do you want to use current date in the folder name? y/n\n");
        /* scanf_s(" %c", &wtd); */
        wtd = get_user_input();
        if (strlen(wtd) > 1) {
          cls();
          printf("Please enter either 'y' or 'n'\n");
          continue;
        }

        cls();

        switch (wtd[0]) {
        case 'y':
          if (create_dir(true) != 0) {
            exit = true;
          }
          break;
        case 'n':
        default:
          if (create_dir(false) != 0) {
            exit = true;
          }
          break;
        }
        if (exit)
          break;
        new_line();
        create_files(true);
        exit = true;
        break;

      case 'n':
        // Create files in current directory
        create_files(false);
        exit = true;
        break;

      default:
        cls();
        printf("Please enter either 'y' or 'n'\n");
        break;
      }
    }
    if (exit)
      break;
  }
  return 0;
}

// Creates a directory with optional date prefix
int create_dir(bool useCurrentDateInDirName) {
  printf("Name the folder: \n");
  scanf_s("%s", _dirName, (unsigned int)sizeof(_dirName));

  // Add date prefix if requested
  if (useCurrentDateInDirName) {
    char *currentDate = get_current_date();
    if (currentDate) {
      char tempDirName[MAX_TEXT_LENGTH] = "";
      snprintf(tempDirName, sizeof(tempDirName), "%s %s", currentDate,
               _dirName);
      strncpy_s(_dirName, sizeof(_dirName), tempDirName, _TRUNCATE);
    } else {
      printf("Failed to get the current date.\n");
    }
  }

  // Create directory and handle errors
  if (CREATE_DIR(_dirName) == 0) {
    printf("Folder '%s' created successfully.\n", _dirName);
  } else {
    perror("Error creating folder");
    return 1;
  }
  return 0;
}

// Creates a file from template based on type (0=HTML, 1=CSS, 2=JS)
void create_a_file(char *_fileName, int type) {
  char fileName[MAX_TEXT_LENGTH] = "";
  char templateTextBuffer[MAX_TEXT_LENGTH] = "";
  FILE *fptr = NULL;
  FILE *file = NULL;

  snprintf(fileName, sizeof(fileName), "%s", _fileName);

  // Set up template path
  char templateFileBuffer[MAX_TEXT_LENGTH] = "";
  strncpy_s(templateFileBuffer, sizeof(templateFileBuffer), _templateDirPath,
            _TRUNCATE);

  // Handle different file types
  switch (type) {
  case 0: // HTML
    strncat_s(fileName, MAX_TEXT_LENGTH, ".html", 5);
    strncat_s(templateFileBuffer, MAX_TEXT_LENGTH, "html.html", 9);
    break;
  case 1: // CSS
    strncat_s(fileName, MAX_TEXT_LENGTH, ".css", 4);
    strncat_s(templateFileBuffer, MAX_TEXT_LENGTH, "css.css", 7);
    break;
  case 2: // JavaScript
    strncat_s(fileName, MAX_TEXT_LENGTH, ".js", 3);
    strncat_s(templateFileBuffer, MAX_TEXT_LENGTH, "js.js", 5);
    break;
  default:
    printf("Error: Unknown file type.\n");
    return;
  }

  // Open template file
  if (fopen_s(&fptr, templateFileBuffer, "r") != 0) {
    printf("Error opening template file\n");
    return;
  }

  // Read template content
  size_t bytesRead = fread(templateTextBuffer, 1, MAX_TEXT_LENGTH - 1, fptr);
  templateTextBuffer[bytesRead] = '\0';
  fclose(fptr);

  // Create and write new file
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

// Creates HTML, CSS, and JS files and updates references
void create_files(bool newDirCreated) {
  char fileName[MAX_TEXT_LENGTH];
  char temp[MAX_TEXT_LENGTH];
  const char *fileTypes[] = {"HTML", "CSS", "JS"};
  char fullFileNames[3][MAX_TEXT_LENGTH] = {0}; // Store complete file paths

  // Add trailing slash to directory name if needed
  if (newDirCreated && _dirName[strlen(_dirName) - 1] != '/') {
    strncat_s(_dirName, MAX_TEXT_LENGTH, "/", 1);
  }

  // Create each file type (HTML, CSS, JS)
  for (int i = 0; i < 3; i++) {
    printf("Enter the %s filename: \n", fileTypes[i]);
    scanf_s("%s", temp, (unsigned)sizeof(temp));

    // Build full file path with directory
    if (strcpy_s(fileName, MAX_TEXT_LENGTH, _dirName) != 0) {
      printf("Error: Failed to copy directory name\n");
      continue;
    }

    if (strncat_s(fileName, MAX_TEXT_LENGTH, temp, strlen(temp)) != 0) {
      printf("Error: Failed to append filename\n");
      continue;
    }

    // Store complete file path for later reference
    strcpy_s(fullFileNames[i], MAX_TEXT_LENGTH, fileName);

    create_a_file(fileName, i);
    new_line();
  }

  // Add file extensions to stored paths
  strncat_s(fullFileNames[0], MAX_TEXT_LENGTH, ".html", 5);
  strncat_s(fullFileNames[1], MAX_TEXT_LENGTH, ".css", 4);
  strncat_s(fullFileNames[2], MAX_TEXT_LENGTH, ".js", 3);

  // Update HTML file with references to CSS and JS files
  update_html_references(fullFileNames[0], fullFileNames[1], fullFileNames[2]);
}

// Updates HTML file to include references to CSS and JS files
void update_html_references(const char *htmlFileName, const char *cssFileName,
                            const char *jsFileName) {
  FILE *htmlFile = NULL;
  char fileContent[MAX_TEXT_LENGTH * 2] = ""; // Doubled buffer for safety
  char newContent[MAX_TEXT_LENGTH * 2] = "";  // Buffer for modified content
  char *headPos = NULL;
  char *bodyEndPos = NULL;

  // Open and read HTML file
  if (fopen_s(&htmlFile, htmlFileName, "r") != 0) {
    printf("Error opening HTML file for reading\n");
    return;
  }

  size_t bytesRead = fread(fileContent, 1, sizeof(fileContent) - 1, htmlFile);
  fileContent[bytesRead] = '\0';
  fclose(htmlFile);

  // Create reference strings for title, CSS, and JS
  char title[MAX_TEXT_LENGTH] = "";
  char cssLink[MAX_TEXT_LENGTH] = "";
  char jsScript[MAX_TEXT_LENGTH] = "";

  // Extract base filenames without directory path
  const char *cssBaseFileName =
      strrchr(cssFileName, '/') ? strrchr(cssFileName, '/') + 1 : cssFileName;
  const char *jsBaseFileName =
      strrchr(jsFileName, '/') ? strrchr(jsFileName, '/') + 1 : jsFileName;
  const char *htmlBaseFileName = strrchr(htmlFileName, '/')
                                     ? strrchr(htmlFileName, '/') + 1
                                     : htmlFileName;

  // Extract HTML filename without extension for title
  const char *lastDot = strrchr(htmlBaseFileName, '.');
  char baseNameWithoutExt[MAX_TEXT_LENGTH];
  size_t length =
      lastDot ? (size_t)(lastDot - htmlBaseFileName) : strlen(htmlBaseFileName);
  strncpy_s(baseNameWithoutExt, MAX_TEXT_LENGTH, htmlBaseFileName, length);
  baseNameWithoutExt[length] = '\0';

  // Format HTML tags for insertion
  snprintf(title, sizeof(title), "  <title>%s</title>\n", baseNameWithoutExt);
  snprintf(cssLink, sizeof(cssLink),
           "  <link rel=\"stylesheet\" href=\"%s\">\n", cssBaseFileName);
  snprintf(jsScript, sizeof(jsScript), "    <script src=\"%s\"></script>\n",
           jsBaseFileName);

  // Find insertion points in HTML
  headPos = strstr(fileContent, "</head>");
  bodyEndPos = strstr(fileContent, "</body>");

  if (headPos == NULL || bodyEndPos == NULL) {
    printf("Error: Could not find required HTML tags\n");
    return;
  }

  // Calculate insertion positions
  size_t headInsertPos = headPos - fileContent;
  size_t bodyInsertPos = bodyEndPos - fileContent;

  // Build new content with references
  strncpy_s(newContent, sizeof(newContent), fileContent, headInsertPos);
  strncat_s(newContent, sizeof(newContent), title, strlen(title));
  strncat_s(newContent, sizeof(newContent), cssLink, strlen(cssLink));
  strncat_s(newContent, sizeof(newContent), headPos,
            bodyInsertPos - headInsertPos);
  strncat_s(newContent, sizeof(newContent), jsScript, strlen(jsScript));
  strncat_s(newContent, sizeof(newContent), bodyEndPos, strlen(bodyEndPos));

  // Write updated content back to file
  if (fopen_s(&htmlFile, htmlFileName, "w") != 0) {
    printf("Error opening HTML file for writing\n");
    return;
  }

  if (fprintf(htmlFile, "%s", newContent) < 0) {
    printf("Error writing to HTML file\n");
    fclose(htmlFile);
    return;
  }

  fclose(htmlFile);
  printf("Successfully updated HTML file with CSS and JS references\n");
}

// Returns current date in YYYY-MM-DD format
char *get_current_date() {
  static char dateStr[11]; // "YYYY-MM-DD" + null terminator
  time_t t = time(NULL);   // Get current time
  struct tm tm;

  // Get local time safely
  if (localtime_s(&tm, &t) != 0) {
    return NULL;
  }

  // Format date string
  snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d", tm.tm_year + 1900,
           tm.tm_mon + 1, tm.tm_mday);

  return dateStr;
}

// Returns the directory path of the executable
char *get_executable_dir_path(void) {
  static char dir[1024];

#if defined(_WIN32)
  // Windows: Get executable path using Windows API
  DWORD result = GetModuleFileName(NULL, dir, sizeof(dir));
  if (result == 0) {
    return "Error retrieving executable path.";
  }

  // Extract directory by removing filename
  char *lastBackslash = strrchr(dir, '\\');
  if (lastBackslash != NULL) {
    *lastBackslash = '\0';
  }

#else
  // Unix/Linux: Get executable path using readlink
  ssize_t len = readlink("/proc/self/exe", dir, sizeof(dir) - 1);
  if (len == -1) {
    return "Error retrieving executable path.";
  }
  dir[len] = '\0';

  // Extract directory using dirname
  char *dirName = dirname(dir);
  strncpy(dir, dirName, sizeof(dir) - 1);
#endif

  return dir;
}

// Initializes paths for executable and template directories
void init_executable_and_template_dir_path(void) {
  // Get and store executable path
  char *executableDirPath = get_executable_dir_path();
  strncpy_s(_executableDirPath, sizeof(_executableDirPath), executableDirPath,
            _TRUNCATE);

  // Build template directory path
  strncat_s(_templateDirPath, MAX_TEXT_LENGTH, _executableDirPath, _TRUNCATE);
  strncat_s(_templateDirPath, MAX_TEXT_LENGTH, "/Templates/", _TRUNCATE);
}
