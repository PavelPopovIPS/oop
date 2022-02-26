@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)
REM Приложение без одного аргумента не запустится
%MyProgram% "matrix.txt"> NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM Приложение без всех аргументов не запустится
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM Не допускается передавать в аргументе пустую строку 
%MyProgram% "matrix.txt" "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM Матрица должна состоять только из чисел 
%MyProgram% "matrix-text.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Матрица должна содержать не более 3 строк
%MyProgram% "matrix-4row.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Матрица должна содержать не менее 3 строк
%MyProgram% "matrix-2row.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Матрица должна содержать 3 столбца
%MyProgram% "matrix-2colum.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM Матрица с пустым значением в одной из позиций не обрабатывается
%MyProgram% "matrix-empty-2x2.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM Пустой файл не обрабатывается
%MyProgram% "matrix-empty.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM Пустой файл переданный в первом аргументе не обрабатывается
%MyProgram% "matrixNoExist.txt" "matrix1.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM Пустой файл переданный во втором аргументе не обрабатывается
%MyProgram% "matrix1.txt" "matrixNoExist.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1