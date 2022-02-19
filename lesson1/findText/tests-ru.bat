@echo off
REM File was saved to OEM-866 for russian

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Text should be found in the beginning of file 
%MyProgram% "text-ru.txt" "пишу"
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1