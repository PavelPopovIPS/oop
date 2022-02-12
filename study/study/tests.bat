@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% "empty.txt" "%TEMP%\output.txt" || goto err
fc "empty.txt" "%TEMP%\output.txt" || goto err

REM Тесты прошли успешно
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1