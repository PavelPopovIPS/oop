@echo off

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM App should not compare text if got one argument
%MyProgram% "emptyFile1.txt"
if NOT ERRORLEVEL 1 goto err

REM App should not compare text without arguments
%MyProgram%
if NOT ERRORLEVEL 1 goto err

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1