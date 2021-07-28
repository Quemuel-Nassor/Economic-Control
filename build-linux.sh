#!bin/bash
echo -e "\n\nCompiling libraries\n"
gcc=C:/cygwin64/bin/gcc.exe

rm ./dependencies/lib/linux/* -f -r -d
rm ./dependencies/lib/windows/* -f -r -d

gcc -c ./dependencies/implementations/error.c -o ./dependencies/lib/linux/error.o
gcc -c ./dependencies/implementations/file.c -o ./dependencies/lib/linux/file.o
gcc -c ./dependencies/implementations/record.c -o ./dependencies/lib/linux/record.o
gcc -c ./dependencies/implementations/dir_mgmt.c -o ./dependencies/lib/linux/dir_mgmt.o
gcc -c ./dependencies/implementations/date_time.c -o ./dependencies/lib/linux/date_time.o

ar rv ./dependencies/lib/linux/liberror.a ./dependencies/lib/linux/error.o
ar rv ./dependencies/lib/linux/libfile.a ./dependencies/lib/linux/file.o
ar rv ./dependencies/lib/linux/librecord.a ./dependencies/lib/linux/record.o
ar rv ./dependencies/lib/linux/libdir_mgmt.a ./dependencies/lib/linux/dir_mgmt.o
ar rv ./dependencies/lib/linux/libdate_time.a ./dependencies/lib/linux/date_time.o

echo -e "\nCompiling the program \n"
gcc ./mainFile.c -o ./mainFile -L "./dependencies/lib/linux" -I "./dependencies/include" -lfile -lerror -lrecord -ldir_mgmt -ldate_time -ansi --std=c99 -static -Wall -pedantic