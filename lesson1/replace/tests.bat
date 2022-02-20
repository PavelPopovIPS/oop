@echo off

REM Первый аргумент при запуске bat файла, символ ~ удаляет кавычки
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Текст с одним вхождением в середине строки
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "16" "100" > NUL || goto err
fc "%TEMP%\output.txt" "test-1-standard.txt" > NUL || goto err
echo Test 1: passed successful

REM Текст с одним вхождением в конце строки
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "Europe." "Asia." > NUL || goto err
fc "%TEMP%\output.txt" "test-2-standard.txt" > NUL || goto err
echo Test 2: passed successful

REM Текст с одним вхождением в начале строки
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "At least" "More then" > NUL || goto err
fc "%TEMP%\output.txt" "test-3-standard.txt" > NUL || goto err
echo Test 3: passed successful

REM Текст с несколькими вхождениями в одной строке
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "a" "AA" > NUL || goto err
fc "%TEMP%\output.txt" "test-4-standard.txt" > NUL || goto err
echo Test 4: passed successful

REM Текст с несколькими вхождениями в разных строках
%MyProgram% "text-mult-lines.txt" "%TEMP%\output.txt" "16" "999a999" > NUL || goto err
fc "%TEMP%\output.txt" "test-5-standard.txt" > NUL || goto err
echo Test 5: passed successful

REM Текст с вхождением искомой строки в строку-заменитель: ma на mama
%MyProgram% "text-mult-lines.txt" "%TEMP%\output.txt" "ma" "mama" > NUL || goto err
fc "%TEMP%\output.txt" "test-6-standard.txt" > NUL || goto err
echo Test 6: passed successful

REM Текст 1231234 внутри текста 12312312345
%MyProgram% "12312312345.txt" "%TEMP%\output.txt" "1231234" "-------" > NUL || goto err
fc "%TEMP%\output.txt" "test-7-standard.txt" > NUL || goto err
echo Test 7: passed successful

REM Текст в пустом фале не должен заменяться
%MyProgram% "empty.txt" "%TEMP%\output.txt" "text" "TEXT2" > NUL || goto err
fc "%TEMP%\output.txt" "empty.txt" > NUL || goto err
echo Test 8: passed successful

REM Запуск программы без одного аргумента
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "text" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM Запуск программы без всех аргументов
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "text" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM Не допускается передавать в искомую строку пустую строку
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "" "TEXT2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1