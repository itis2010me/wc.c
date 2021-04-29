#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(const char* file_name, int* file_data){
    FILE* file = fopen(file_name, "r");
    int count_char = 0, count_word = 0, count_line = 0;
    char temp_c;
    int word = 0; // bool for checking whether or not currently looking within a word

    if(file == NULL){
        file_data[0] = count_char;
        file_data[1] = count_word;
        file_data[2] = count_line;
        return 1; // cannot open file, exit with 1
    }
    for(temp_c = fgetc(file); temp_c != EOF; temp_c = fgetc(file)){
        count_char++;

        if(temp_c == ' '|| temp_c == '\0' || temp_c == '\n'){
            if (word){ // in a word and the character is space, null or new line, which means exiting the word
                word = 0; // exit a word
                count_word++;
            }
            if(temp_c == '\n'){ // new line
                count_line++;
            }
        }else{ // entering a word
            word = 1;
        }

    }
    // printf("%d, %d, %d \n", count_char, count_word, count_line);
    file_data[0] = count_char;
    file_data[1] = count_word;
    file_data[2] = count_line;

    fclose(file); // close file
    return 0;
}

int main(int argc, char** argv){

    int error = 0; //return 1 error
    //code for parsing the command line arguments
    int cflag = 0, wflag = 0, lflag = 0; // bool for count c/w/l or all together
    int print_total = 0; // bool for print total
    int total_count[3] = {0,0,0};
    // count number of files and flags
    int num_files = 0, num_flags = 0; // number of files and flags
    for(int i = 1; i < argc; i++){
        if(argv[i][0] != '-'){ // not a flag
            num_files++;
        }else{ // a flag
            num_flags++;
        }
    }

    // allocate array for files and flags
    char** file_names = (char**)malloc(num_files*sizeof(char*));
    char** flag_names = (char**)malloc(num_flags*sizeof(char*));
    int index_f = 0, index_fl = 0;

    // retrieve the files and flags into the arraies
    for(int i = 1; i < argc; i++){
        if(argv[i][0] != '-'){
            file_names[index_f] = argv[i];
            index_f++;
        }else{
            flag_names[index_fl] = argv[i];
            index_fl++;
        }
    }

    if(num_files >= 2){
        print_total = 1; // enable print total
    }

    if(num_files == 0){
        free(flag_names);
        free(file_names);
        printf("No files provided");
        return 2;
    }

    int errors[num_files]; //if errors[i] == 1, then the ith file failed to read

    // Each file at most needs 3 ints to record number of char, words and lines
    // the int** will store all files's data, with each as an int*
    int** data = (int**)malloc(num_files*sizeof(int*)); //number of files
    for(int i = 0; i < num_files; i++){
        // Allocate 3 int space for each file's char, words and lines
        data[i] = (int*)malloc(3*sizeof(int));
        errors[i] = count(file_names[i], data[i]);
    }

    // parse through the flags
    // while flags are false, continue to check for flags
    // if all three are true, not need to check any more flags
    int j = 0; //index j to loop through the flags
    while((cflag == 0) || (wflag == 0) || (lflag == 0)){
        if(j >= num_flags){
            break;
        }
        char* p;
        p = strstr(flag_names[j], "m");
        if(p != NULL){
            cflag = 1;
        }
        p = strstr(flag_names[j], "chars");
        if(p != NULL){
            cflag = 1;
        }
        p = strstr(flag_names[j], "w");
        if(p != NULL){
            wflag = 1;
        }
        p = strstr(flag_names[j], "words");
        if(p != NULL){
            wflag = 1;
        }
        p = strstr(flag_names[j], "l");
        if(p != NULL){
            lflag = 1;
        }
        p = strstr(flag_names[j], "line");
        if(p != NULL){
            lflag = 1;
        }
        j++; // next flag
    }

    // if after checking for all flags, still all false,
    // turn on all flags
    if((cflag == 0) && (wflag == 0) && (lflag == 0)){
        cflag = 1;
        wflag = 1;
        lflag = 1;
    }

    // print results
    for(int i = 0; i < num_files; i++){
        if(errors[i]){
            perror("fopen");
            error = 1;
            continue;
        }
        printf("%s ", file_names[i]);
        if(lflag){
            printf("%d ", data[i][2]);
            total_count[0] = total_count[0] + data[i][2];
        }
        if(wflag){
            printf("%d ", data[i][1]);
            total_count[1] = total_count[1] + data[i][1];
        }
        if(cflag){
            printf("%d", data[i][0]);
            total_count[2] = total_count[2] + data[i][0];
        }
        printf("\n");
    }

    // checks print total
    if(print_total){
        printf("total: ");
        if(lflag){
            printf("%d ", total_count[0]);
        }
        if(wflag){
            printf("%d ", total_count[1]);
        }
        if(cflag){
            printf("%d", total_count[2]);
        }
        printf("\n");
    }

    // free the memory
    free(flag_names);
    free(file_names);

    for(int i = 0; i < num_files; i++){
        free(data[i]);
    }
    free(data);

    // terminate program with correct return value
    /*
    * 0 - correct termination
    * 1 - cannot open one of the files
    * 2 - no files provided, this was terminated earier in the program
    */
    if(error == 1){
        return 1;
    }
    return 0;
}
