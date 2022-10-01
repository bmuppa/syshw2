
********************************************  SYSTEMS PROGRAMMING - HOMEWORK 2 *********************************************************

## Source Code Working:

# program will support 4 different commands such as -S -s -f -t
    -S 
        this command fetches all the files and directories along with file_size, last access date, file permissions from the path specified 
        
        Example
                filename (size) (last access time) (permissions)

                # permissions:
                    drwxrwxrwx
                    d  -> directory / file
                    rwx -> read,write,execution -> owner
                    rwx -> read,write,execution -> group
                    rwx -> read,write,execution -> others



    -s <file_size_limit>
        this command fetches all the files with the file size less than or equal to value mentioned.


    -f <pattern> <depth>
        this command fetches all the files in file heirearchy where as file/directory name has pattern as substring
        it lists down the data upto the relative depth(heigh of tree from parent directory/folder) mentioned above

        Example 
                    ./search -f .c 0

                            hw1.c
                            hw2.c
                            hw3.c
                    ./search -f .c 1
                            hw1.c
                                    hw4.c
                            hw2.c
                                    hw5.c
                            hw3.c
    
    -t f
        fetches all regular files from the path mentioned.

    -t d
        fetches all directories from the path mentioned.



## Code Compilation:

        gcc -o search search.c
        <or> 
        make -f Make-File

## Code Execution Commands:

    you can try combination of any commands mentioned above.
    
    pwd  <-- gets you the current path use this command for path usage

    ./search 

    ./search path/default

    ./search -S path/default

    ./search -s <SIZE> path/default

    ./search -t d path/default

    ./search -t f path/default

    ./search -f <pattern> <depth> path/default

    ./search -S -s <SIZE> path/default

    ./search -S -s <SIZE> -f <pattern> <depth> path/default

    ./search -S -s <SIZE> -t d path/default

    ./search -S -s <SIZE> -t f path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t d path/default

    ./search -S -s <SIZE> -f <pattern> <depth> -t f path/default

    


## Reference files from lab work:
readdir.c, lstat.c, funcptr.c, readdir_v2.c which are provided in the lab 5 assignment in the canvas.
