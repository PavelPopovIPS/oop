@echo off

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Files with equal text should be equal
%MyProgram% "source.txt" "copySource.txt" && fc "source.txt" "copySource.txt"
if ERRORLEVEL 1 goto err

REM Empty files should be equal
%MyProgram% "emptyFile1.txt" "emptyFile2.txt" && fc "emptyFile1.txt" "emptyFile2.txt"
if ERRORLEVEL 1 goto err

REM Files with equal text but different length should be different
%MyProgram% "source.txt" "sourceWithoutOneChar.txt" && fc "source.txt" "sourceWithoutOneChar.txt"
if NOT ERRORLEVEL 1 goto err

REM Files whith different text should be different
%MyProgram% "source.txt" "newText.txt" && fc "source.txt" "newText.txt"
if NOT ERRORLEVEL 1 goto err

REM One empty file and file with one character should be different
%MyProgram% "emptyFile1.txt" "oneChar.txt" && fc "emptyFile1.txt" "oneChar.txt"
if NOT ERRORLEVEL 1 goto err

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