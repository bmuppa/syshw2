#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

/*
Name: Bhavana Muppa
BlazerId: bmuppa
Project #: implementing search command using C system calls
To compile: gcc -o search search.c or make -f Make-File
To run: ./search -S
        ./search -s 1024
        ./search -f .c 0
        ./search -t d
        ./search -t f

        please refer README.txt file for compilation and more execution commands in detail
*/
#define max_value 1001
#define emptystring sprintf(file_name,"%s", "");
#define copy(a,b) strcpy(a,b);
#define tabspace printf(" \t ");

long long int limit_value;
int depth_value;
int height_Check;
int commands[4] ={0,0,0,0};
char command_line_arguments[8] = "Ss:f:t:";
char substring_pattern[max_value];
char file_type[max_value];
char file_name[max_value];
char permissions_array[10];

typedef void Func_Pointer(struct stat lstat_buffer, int cnt, char *current_file_path);
void file_permissions(struct stat buffer);
void print_list(char *file_name, int level_cnt);
void get_files(char *folder_path, int level_cnt, Func_Pointer *func_pointer);
void get_argument_values(char argument);
int get_depth_value(int a, char **b);

void file_permissions(struct stat buffer){
    permissions_array[0] = *( (S_ISDIR(buffer.st_mode)) ? "d" : "-");
    permissions_array[1] = *( (buffer.st_mode & S_IRUSR) ? "r" : "-");
    permissions_array[2] = *( (buffer.st_mode & S_IWUSR) ? "w" : "-");
    permissions_array[3] = *( (buffer.st_mode & S_IXUSR) ? "x" : "-");
    permissions_array[4] = *( (buffer.st_mode & S_IRGRP) ? "r" : "-");
    permissions_array[5] = *( (buffer.st_mode & S_IWGRP) ? "w" : "-");
    permissions_array[6] = *( (buffer.st_mode & S_IXGRP) ? "x" : "-");
    permissions_array[7] = *( (buffer.st_mode & S_IROTH) ? "r" : "-");
    permissions_array[8] = *( (buffer.st_mode & S_IWOTH) ? "w" : "-");
    permissions_array[9] = *( (buffer.st_mode & S_IXOTH) ? "x" : "-");
    if (S_ISREG(buffer.st_mode))
        permissions_array[0] ='f';
}

void print_list(char *file_name, int level_cnt){
    if (strcmp(file_name, "") != 0)
    {
        for (int i =0;i<level_cnt+1;i++ ) {
            if(commands[2]==0)
                tabspace
        }
        if(commands[2]==1 && level_cnt<=height_Check){
            for (int j = 0;j<level_cnt+1;j++ ) {
                tabspace
            }
            if(commands[0]== 1){
                printf("%s %s\n",file_name,permissions_array);
            }
            else {
                printf("%s \n", file_name);
            }
        }
        else if(commands[2]==0){
            if(commands[0]== 1){
                printf("%s %s\n",file_name,permissions_array);
            }
            else   { 
                printf("%s \n", file_name);
            }
        }
    }
}

void  commands_function(struct stat lstat_buffer,int level_cnt, char *current_file_path)
{
    emptystring
    strcat(file_name, current_file_path);
    if (commands[0] == 1)
    {
        char temporary_array[max_value];
        copy(temporary_array, " ");
        sprintf(temporary_array, "%lld", lstat_buffer.st_size);
        strcat(file_name, "  (");
        strcat(file_name, temporary_array);
        strcat(file_name, ")  ");
        char *time_val = ctime(&lstat_buffer.st_atime);
        time_val[strlen(time_val)-1]='\0';
        strcat(file_name,time_val);
        file_permissions(lstat_buffer);
    }

    if (((commands[3]==1) &&(S_ISDIR(lstat_buffer.st_mode) != 0) && (strcmp(file_type, "f") == 0)) ||((commands[3]==1) && (S_ISREG(lstat_buffer.st_mode) != 0) && (strcmp(file_type, "d") == 0 ))) {
        copy(file_name, "");
    }
    else if (commands[1] == 1 && lstat_buffer.st_size >= limit_value)
    {
        copy(file_name, "");
    }
    else if ( ((commands[2] == 1 && strstr(current_file_path, substring_pattern) == NULL))) {
        copy(file_name, "");
    }
    print_list(file_name, level_cnt);

}

void get_files(char *folder_path, int level_cnt, Func_Pointer *func_pointer)
{
    struct dirent *dirent;
    DIR *directory_path = opendir(folder_path);
    if (!directory_path || (commands[2]==1 && depth_value == -1))
    {
        return;
    }
    while ((dirent = readdir(directory_path)) != NULL)
    {
        if (strcmp(dirent->d_name,".") && strcmp(dirent->d_name,".."))
        {
            char full_file_path[max_value] ;
            copy(full_file_path, folder_path);
            strcat(full_file_path, "/");
        	strcat(full_file_path, (*dirent).d_name);
            struct stat lstat_buffer;
            lstat(full_file_path, &lstat_buffer);
            func_pointer(lstat_buffer,level_cnt, (*dirent).d_name);
            if ((*dirent).d_type == DT_DIR)
            {
                level_cnt = level_cnt + 1;get_files(full_file_path,level_cnt, func_pointer);
                level_cnt = level_cnt - 1;
            }
        }
    }
    closedir(directory_path);
}

void get_argument_values(char argument) {

    if(argument == 'S')
        commands[0] = 1;
    if(argument == 's')
        {commands[1] = 1; limit_value = atoi(optarg);}
    if(argument == 'f')
        {commands[2] = 1;    copy(substring_pattern,optarg);  }
    if(argument == 't')
        {commands[3] = 1; }
}

int get_depth_value(int a, char **b){

    int i = 0;
    char *height;
    int output;
    while(i<a){
        if(strcasecmp(b[i],"-f")==0){
            height = b[i+2];
            output = atoi(height);
        }
        if(strcmp(b[i],"-t")==0){
            commands[3] = 1;
            strcpy(file_type,b[i+1]);
            // printf("%s\n",file_type);
        }
        i = i + 1;
    }
    return output;
}

int main(int argc, char **argv)
{
    int opt = 0;
    char folder_path[max_value];
    copy(folder_path,argv[argc-1]);

    while ((opt = getopt(argc, argv, command_line_arguments)) != EOF)
    {
       char argument = opt;
       get_argument_values(argument);
    }

    depth_value = get_depth_value(argc,argv);
    height_Check = depth_value;

    if(opendir(folder_path)){
        char  *user_path = argv[argc -  1];
        get_files(user_path,0,commands_function); 
        
    }
    else{
        getcwd(folder_path, max_value);
        get_files(folder_path,0,commands_function);
    }  
    return 0;
}


