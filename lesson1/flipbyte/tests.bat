@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Значение аргумента 6 корректно обрабатывается
%MyProgram% "6" > NUL 
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM Значение аргумента 0 корректно обрабатывается
%MyProgram% "0" > NUL 
if ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM Значение аргумента 255 корректно обрабатывается
%MyProgram% "255" > NUL 
if ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM Отрицательное число не допустимо в аргументе
%MyProgram% "-1" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Значение более 255 не допустимо в аргументе
%MyProgram% "256" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Аргумент не может принимать буквенно символьную строку
%MyProgram% "abc6" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM Аргумент не может принимать пустую строку
%MyProgram% "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM Тест с двумя аргументами не запустится
%MyProgram% "5" "3"> NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM Тест без всех аргументов не запустится
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1