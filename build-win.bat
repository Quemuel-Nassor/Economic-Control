echo -e "\n\nCompiling libraries\n"
set gcc=C:\MinGW\mingw64\bin\gcc.exe

del .\dependencies\lib\windows /F /S /Q

%gcc% -c .\dependencies\implementations\error.c -o .\dependencies\lib\windows\error.o
%gcc% -c .\dependencies\implementations\string_handler.c -o .\dependencies\lib\windows\string_handler.o
%gcc% -c .\dependencies\implementations\file.c -o .\dependencies\lib\windows\file.o
%gcc% -c .\dependencies\implementations\record.c -o .\dependencies\lib\windows\record.o
%gcc% -c .\dependencies\implementations\dir_mgmt.c -o .\dependencies\lib\windows\dir_mgmt.o
%gcc% -c .\dependencies\implementations\date_time.c -o .\dependencies\lib\windows\date_time.o

ar rv .\dependencies\lib\windows\liberror.a .\dependencies\lib\windows\error.o
ar rv .\dependencies\lib\windows\libstring_handler.a .\dependencies\lib\windows\string_handler.o
ar rv .\dependencies\lib\windows\libfile.a .\dependencies\lib\windows\file.o
ar rv .\dependencies\lib\windows\librecord.a .\dependencies\lib\windows\record.o
ar rv .\dependencies\lib\windows\libdir_mgmt.a .\dependencies\lib\windows\dir_mgmt.o
ar rv .\dependencies\lib\windows\libdate_time.a .\dependencies\lib\windows\date_time.o

echo -e "\nCompiling the program \n"
%gcc% .\mainFile.c -o .\mainFile -L ".\dependencies\lib\windows" -I ".\dependencies\include" -lfile -lerror -lstring_handler -lrecord -ldir_mgmt -ldate_time -ansi --std=c99 -static -Wall -pedantic