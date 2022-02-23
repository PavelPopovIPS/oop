@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Ротация битов на 2 порядка для числа 17 выполняется успешно
%MyProgram% "17" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM Ротация битов на 2 порядка для числа 0 выполняется успешно
%MyProgram% "0" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM Ротация битов на 2 порядка для числа 255 выполняется успешно
%MyProgram% "255" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM Отрицательное число не допустимо в аргументе byte
%MyProgram% "-1" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Число 256 не допустимо в аргументе byte
%MyProgram% "256" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Текстовая строка не допустима в аргументе byte
%MyProgram% "abcd" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM Сдвиг битов на 0 разрядов влево выполняется корректно
%MyProgram% "17" "0" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM Сдвиг битов на 8 разрядов влево выполняется корректно
%MyProgram% "17" "8" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM Сдвиг битов на 9 разрядов влево равносильно 1 сдвигу влево и выполняется корректно
%MyProgram% "17" "9" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM Не допускается отрицательное значение в аргументе <number of bits>
%MyProgram% "17" "-1" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM Текстовая строка не допустима в аргументе <number of bits>
%MyProgram% "17" "abcd" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM Сдвиг битов на 0 разрядов вправо выполняется корректно
%MyProgram% "17" "0" "R" > NUL 
if ERRORLEVEL 1 goto err
echo Test 12: passed successful

REM Сдвиг битов на 10 разрядов вправо равносильно сдвигу вправо на 2 разряда и выполняется корректно
%MyProgram% "17" "10" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 13: passed successful

REM Не допускается использовать маленькую l для направления влево
%MyProgram% "17" "2" "l" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 14: passed successful

REM Не допускается использовать маленькую r для направления вправо
%MyProgram% "17" "2" "r" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 15: passed successful

REM Не допускается использовать число для направления
%MyProgram% "17" "2" "5" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 16: passed successful

REM Не допускается использовать строку для направления
%MyProgram% "17" "2" "xyz" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 17: passed successful

REM Тест без одного аргумента не запустится
%MyProgram% "17" "2" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 18: passed successful

REM Тест без всех аргументов не запустится
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 19: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1