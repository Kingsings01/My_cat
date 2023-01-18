#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main( int arg_c, char** arg_s) {

    if (arg_c < 2) {
        printf("Usage: Please Enter file ");  //Check if arguments are passed
        return 1; //error indication
    }

    for (int i = 1; i < arg_c; i++) {  
        int file_d = open (arg_s[i], O_RDONLY); //open the arg in read-only mode

        struct stat str;
        fstat(file_d, & str);
        size_t file_size = str.st_size;
        char* buffer = malloc(file_size +1);
        ssize_t bytes_read = read(file_d, buffer, file_size);
        //using structure to allocate memory to be used by the file opened in form of buffer

        if(bytes_read == -1){
            perror("Error reading file"); // if the file is not read, we return an error signifying that there was an error
            free(buffer); // free the allocated memory buffer
            close(file_d); // close the file
            return 1;
        }

        buffer[bytes_read] = '\0';

        printf("%s", buffer); // we print the buffer content to console, wihich is the file content as displauyed by cat shell command

        free(buffer); // we free the alliocated memory buffer
        close(file_d); // we close the file
    }

    return 0; 

}

// This C program is a custom implementation of the 'cat' command, which reads the contents of one or more files passed as command-line arguments and prints the contents to the console.
// The program starts with including the necessary headers, 'stdio.h', 'stdlib.h', 'sys/stat.h', 'unistd.h' and 'fcntl.h' which are required for input/output operations, memory allocation, and file manipulation.
// In the main function 'int main( int argc, char** argv)', the program checks if the number of command-line arguments passed is less than 2 by checking the value of 'argc'. If the number of arguments is less than 2, it prints a message "Usage: provide file please" and returns 1, which is typically used to indicate an error.
// Then, the program uses a for loop to iterate through each command-line argument starting from the second argument, using the 'open()' function to open the file in read-only mode, passing the name of the file and the constant 'O_RDONLY' as arguments. The function returns a file descriptor, which is stored in the variable file_d.
// The program uses the 'fstat()' function to get information about the file, such as its size, and stores it in a 'struct stat' object called 'str'. It uses the st_size member of this object to allocate memory for a buffer large enough to hold the contents of the file, using the 'malloc()' function.
// Then, the program uses the 'read()' function to read the contents of the file into the buffer. If the return value of 'read()' is -1, it means an error occurred while reading the file, the program then prints an error message using the 'perror()' function and returns 1.
// The program then adds a null-terminator to the end of the buffer, to ensure that the contents of the buffer are treated as a null-terminated string, and then prints the contents of the buffer to the console using the 'printf()' function.
// Finally, the program frees the memory allocated to the buffer using the 'free()' function, closes the file using the 'close()' function and returns 0. This is typically used to indicate a successful execution of the program.
