#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

char* get_line()
{
    char* line = NULL;
    size_t len = 0;

    getline(&line, &len, stdin);

    return line;
}

char** parse_line(char* line)
{
    int buffer_size = 64;
    char** tokens = malloc( buffer_size * sizeof(char*));
    char* token;

    int i = 0;
    token = strtok(line, " \t\r\n");
    while(token != NULL)
    {
        tokens[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    tokens[i] = NULL;

    return tokens;
}

char* expand_variable(char* input)
{
    if(input[0] == '$')
    {
        char* value = getenv(input + 1);
        if (value != NULL)
            return value;
    }

    return input;
}

void simple_cmd(char** args, char* output_file)
{
    pid_t pid = fork();
    int status;

    switch(pid)
    {
        case -1:
            perror("[simple_cmd(char**, char*)] ");
            exit(EXIT_FAILURE);
        case 0:
            for (int i = 0; args[i] != NULL; i++)
                args[i] = expand_variable(args[i]);

            if(output_file)
            {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                {
                    perror("[simple_cmd(char**, char*)] ");
                    exit(EXIT_FAILURE);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            if (execvp(args[0], args) == -1)
                perror("[simple_cmd(char**, char*)] ");
            exit(EXIT_FAILURE);
        default:
            waitpid(pid, &status, 0);
    }
}

void set_environment_variable(char* line)
{
    char* name = strtok(line, "=");
    char* value = strtok(NULL, "=");

    if(name && value)
    {
        if (setenv(name, value, 1) == -1)
        {
            perror("[set_environment_variable(char*)] ");
            exit(EXIT_FAILURE);
        }
    }
}

void execute_command(char** command)
{
    if (execvp(command[0], command) == -1)
        perror("[execute_command(char**)] ");
    exit(EXIT_FAILURE);
}

void execute_piped_commands(char** first_command, char** second_command)
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("[execeute_piped_commands(char**, char**)] ");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();

    switch(pid1)
    {
        case -1:
            perror("[execute_piped_commands(char**, char*)] ");
            exit(EXIT_FAILURE);
        case 0:
            close(pipe_fd[READ_END]);
            dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
            close(pipe_fd[WRITE_END]);
            execute_command(first_command);
        case 1:
            waitpid(pid1, NULL, 0);
    }

    pid_t pid2 = fork();

    switch(pid2)
    {
        case -1:
            perror("[execute_piped_commands(char**, char*)] ");
            exit(EXIT_FAILURE);
        case 0:
            close(pipe_fd[WRITE_END]);
            dup2(pipe_fd[READ_END], STDIN_FILENO);
            close(pipe_fd[READ_END]);
            execute_command(second_command);
        case 1:
            waitpid(pid2, NULL, 0);
    }

    close(pipe_fd[READ_END]);
    close(pipe_fd[WRITE_END]);
}

int main()
{
    char* line;
    char** command;

    while(1)
    {
        printf("> ");

        line = get_line();

        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "exit", 4) == 0)
            break;

        if (strchr(line, '='))
            set_environment_variable(line);
        else
        {
            char* output_file = NULL;
            char* redirect = strchr(line, '>');

            if(redirect)
            {
                *redirect = 0;
                redirect++;
                while(*redirect == ' ') redirect++;
                output_file = redirect;
            }

            char* pipe_pos = strchr(line, '|');
            if (pipe_pos)
            {
                *pipe_pos = 0;
                pipe_pos++;
                while(*pipe_pos == ' ') pipe_pos++;

                char** first_command = parse_line(line);
                char** second_command = parse_line(pipe_pos);

                execute_piped_commands(first_command, second_command);
                continue;
            }

            command = parse_line(line);
            simple_cmd(command, output_file);
        }

    }

    free(line);
    free(command);

    exit(EXIT_SUCCESS);
}
