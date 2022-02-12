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

REM Copy file with one line
%MyProgram% "one-line.txt" "%TEMP%\output.txt" || goto err
fc "one-line.txt" "%TEMP%\output.txt" || goto err

REM Copy file with one empty line
%MyProgram% "textWithEmptyLine.txt" "%TEMP%\output.txt" || goto err
fc "textWithEmptyLine.txt" "%TEMP%\output.txt" || goto err

REM Copy missing file should fail
%MyProgram% "missingFile.txt" "%TEMP%\output.txt" && goto err
echo It is Ok!
echo:

REM Start program with one arg
%MyProgram% "missingFile.txt" && goto err
echo It is Ok!
echo:

REM Input Output files are not specified
%MyProgram% && goto err
echo It is Ok!
echo:

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1