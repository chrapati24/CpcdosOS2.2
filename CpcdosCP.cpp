#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Define a structure for storing variables
typedef struct Variable {
    char name[50];
    char value[256];
} Variable;

Variable variables[100];
int var_count = 0;

// Function to trim leading and trailing spaces
char *trim(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    // All spaces?
    if(*str == 0) return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

// Function to remove spaces after '/'
char *remove_space_after_slash(char *command) {
    char *result = command;
    if (*command == '/') {
        char *content = command + 1;
        while(isspace((unsigned char)*content)) content++;
        memmove(result + 1, content, strlen(content) + 1);
    }
    return result;
}

// Function to get variable value
char* get_variable_value(char *var_name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, var_name) == 0) {
            return variables[i].value;
        }
    }
    return NULL; // Variable not found
}

// Function to replace variables in the command
char *replace_variables(char *command) {
    static char result[256];
    strcpy(result, command);

    char temp[256];
    char *start = strchr(result, '%');
    while (start) {
        char *end = strchr(start + 1, '%');
        if (!end) break;

        char var_name[50];
        strncpy(var_name, start + 1, end - start - 1);
        var_name[end - start - 1] = '\0';

        char *value = get_variable_value(var_name);
        if (value) {
            // Replace %MyVar% with its value
            strncpy(temp, result, start - result);
            temp[start - result] = '\0';
            strcat(temp, value);
            strcat(temp, end + 1);
            strcpy(result, temp);
        }
        
        start = strchr(start + 1, '%');
    }
    return result;
}

// Function to execute a command
void execute_command(char *command) {
    char *cmd = trim(command);
    cmd = remove_space_after_slash(cmd);
    cmd = replace_variables(cmd);

    if (strncmp(cmd, "set/", 4) == 0) {
        // Handle set/ command
        char *eq_pos = strchr(cmd + 4, '=');
        if (eq_pos) {
            char var_name[50];
            strncpy(var_name, cmd + 4, eq_pos - cmd - 4);
            var_name[eq_pos - cmd - 4] = '\0';
            strcpy(var_name, trim(var_name));

            char *var_value = trim(eq_pos + 1);
            strcpy(variables[var_count].name, var_name);
            strcpy(variables[var_count].value, var_value);
            var_count++;
            printf("Variable %s set to %s\n", var_name, var_value);
        } else {
            printf("Invalid set command: %s\n", cmd);
        }
    } else if (strncmp(cmd, "exe/", 4) == 0) {
        printf("Executing file: %s\n", cmd + 4);
        // Add your code to execute file
    } else if (strncmp(cmd, "txt/", 4) == 0) {
        printf("Displaying text: %s\n", cmd + 4);
        // Add your code to display text
    } else if (strncmp(cmd, "sys/", 4) == 0) {
        printf("System command: %s\n", cmd + 4);
        // Add your code to execute system command
    } else if (strncmp(cmd, "ccp/", 4) == 0) {
        printf("CCP command: %s\n", cmd + 4);
        // Add your code for CCP
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}

// Function to process commands from a file
void execute_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        execute_command(line);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // If a file is provided, execute commands from the file
        execute_file(argv[1]);
    } else {
        // Otherwise, read commands from the terminal
        char command[256];
        printf("CpcdosC+ Command Interpreter\n");
        printf("Enter commands (type 'exit' to quit):\n");
        while (1) {
            printf("> ");
            fgets(command, sizeof(command), stdin);
            if (strncmp(command, "exit", 4) == 0) break;
            execute_command(command);
        }
    }

    return 0;
}