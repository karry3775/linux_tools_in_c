A simple program that implements `ls -l`

## Build the program
```
$ make
$ cd build 
$ ./myls
```

## Usage

Without any args
```
kartik@kartik-ThinkPad:~/dev/logbook_projects/linux_tools/my_ls/build$ ./myls 
drwxrwxr-x 2 kartik kartik 4096 Sep 28 13:28 .
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 ..
-rwxrwxr-x 1 kartik kartik 16632 Sep 28 13:28 myls
```

With args
```
kartik@kartik-ThinkPad:~/dev/logbook_projects/linux_tools/my_ls/build$ ./myls  ..
drwxrwxr-x 2 kartik kartik 4096 Sep 28 13:28 .
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 ..
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 README.md
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 build
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 ls.c
drwxrwxr-x 3 kartik kartik 4096 Sep 28 13:28 Makefile
```


