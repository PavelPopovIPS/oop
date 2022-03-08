@echo off

REM Первый аргумент при запуске bat файла, ~ удаляет скобки.
SET MyProgram="%~1"

REM Если аргумент не передали, выведется ошибка
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM В приложение должно быть передано не менее 4 аргументов
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM В приложение должно быть передано не более 5 аргументов
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "2" "" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM Приложение без аргументов не запустится
%MyProgram% > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM Шифрование задается значением crypt
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "2" > NUL
if ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM Дешифрование задается значением decrypt
%MyProgram% "decrypt" "text.txt" "%TEMP%\output.txt" "2" > NUL
if ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM Любое другое значение в action не допустимо
%MyProgram% "cr" "text.txt" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM Не существующий файл для чтения не откроется
%MyProgram% "crypt" "tex" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM Пустое имя файла для чтения не допустимо
%MyProgram% "crypt" "" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM Пустое имя файла для записи не допустимо
%MyProgram% "crypt" "text.txt" "" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM Ключ не может быть меньше 0
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "-1" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM Ключ не может быть больше 255
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "256" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM Ключ для шифрования равен 0
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "0" > NUL
if ERRORLEVEL 1 goto err
echo Test 12: passed successful

REM Ключ для шифрования равен 255
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "255" > NUL
if ERRORLEVEL 1 goto err
echo Test 13: passed successful

REM Ключ для шифрования не может быть текстом
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "abc" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 14: passed successful

REM Расшифрованный файл должен быть идентичный исходному
%MyProgram% "crypt" "text.txt" "%TEMP%\output-crypt.txt" "3" > NUL
%MyProgram% "decrypt" "%TEMP%\output-crypt.txt" "%TEMP%\output-decrypt.txt" "3" > NUL
fc "text.txt" "%TEMP%\output-decrypt.txt" > NUL
if ERRORLEVEL 1 goto err
echo Test 15: passed successful

REM Расшифрованный файл с другим ключом должен отличаться от исходного
%MyProgram% "crypt" "text.txt" "%TEMP%\output-crypt.txt" "3" > NUL
%MyProgram% "decrypt" "%TEMP%\output-crypt.txt" "%TEMP%\output-decrypt.txt" "5" > NUL
fc "text.txt" "%TEMP%\output-decrypt.txt" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 16: passed successful

REM Шифрование и расшифровака пустого файла
%MyProgram% "crypt" "empty-file.txt" "%TEMP%\output-crypt.txt" "100" > NUL
%MyProgram% "decrypt" "%TEMP%\output-crypt.txt" "%TEMP%\output-decrypt.txt" "100" > NUL
fc "empty-file.txt" "%TEMP%\output-decrypt.txt" > NUL
if ERRORLEVEL 1 goto err
echo Test 17: passed successful


REM Тесты прошли успешно
echo Tests passed successfuly
exit /B 0

REM Выведем ошибку если тесты не прошли
:err
echo Test failed
exit /B 1