@echo off

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Text should be found in the beginning of file 
%MyProgram% "text-en.txt" "No" > NUL
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM Text should be found in the end of file 
%MyProgram% "text-en.txt" "less." > NUL
if ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM Text should be found in the middle of file 
%MyProgram% "text-en.txt" "main" > NUL
if ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM The same text should be found in multiple lines of file 
%MyProgram% "text-en.txt" "the" > NUL
if ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Text with spaces should be found
%MyProgram% "text-en.txt" "a piece of the continent" > NUL
if ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Empty line should be found
%MyProgram% "text-en.txt" "" > NUL
if ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM App should case sensitivity and text should not be found
%MyProgram% "text-en.txt" "Main" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM Text should not be found in emtpty file
%MyProgram% "emptyText.txt" "again" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM App should not search text if got one argument
%MyProgram% "text1.txt" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM App should not search text without arguments
%MyProgram% > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1