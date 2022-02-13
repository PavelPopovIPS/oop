@echo off

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Compare equal files
(%MyProgram% "source.txt" "copySource.txt" && fc "source.txt" "copySource.txt") || goto err

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1