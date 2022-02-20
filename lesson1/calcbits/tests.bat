@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM В числе должен произойти подсчет еденичек в битах
%MyProgram% 5 > NUL || goto err
echo Test 1: passed successful

REM В строке подсчет еденичек не производится
%MyProgram% "text" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM В пустой строке подсчет еденичек не производится
%MyProgram% "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM Отрицательное число не применяется
%MyProgram% -5 > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Тест без аргумента не запустится
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1