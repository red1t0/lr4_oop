@echo off
setlocal

REM Установите путь к компилятору MinGW, если он не в PATH
REM set PATH=C:\MinGW\bin;%PATH%

REM Имя исполняемого файла
set TARGET=battleships.exe

REM Исходные файлы
set SRCS= abilities.cpp abilitiesmanager.cpp display.cpp field.cpp fileprocessor.cpp game.cpp gamemanager.cpp gamestate.cpp input.cpp main.cpp myexception.cpp parser.cpp render.cpp ship.cpp shipmanager.cpp

REM Объектные файлы
set OBJS=%SRCS:.cpp=.o%

REM Компиляция всех исходных файлов
echo Compiling source files...
for %%f in (%SRCS%) do (
    g++ -std=c++11 -Wall -c %%f
)

REM Линковка объектных файлов в исполняемый файл
echo Linking object files...
g++ -o %TARGET% %OBJS%

REM Удаление объектных файлов
echo Cleaning up...
del *.o

REM Запуск программы
echo Running the program...
start %TARGET%

endlocal