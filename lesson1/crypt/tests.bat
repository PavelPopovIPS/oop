@echo off

REM ������ �������� ��� ������� bat �����, ~ ������� ������.
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM � ���������� ������ ���� �������� �� ����� 4 ����������
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM � ���������� ������ ���� �������� �� ����� 5 ����������
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "2" "" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM ���������� ��� ���������� �� ����������
%MyProgram% > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM ���������� �������� ��������� crypt
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "2" > NUL
if ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM ������������ �������� ��������� decrypt
%MyProgram% "decrypt" "text.txt" "%TEMP%\output.txt" "2" > NUL
if ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM ����� ������ �������� � action �� ���������
%MyProgram% "cr" "text.txt" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM �� ������������ ���� ��� ������ �� ���������
%MyProgram% "crypt" "tex" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM ������ ��� ����� ��� ������ �� ���������
%MyProgram% "crypt" "" "%TEMP%\output.txt" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM ������ ��� ����� ��� ������ �� ���������
%MyProgram% "crypt" "text.txt" "" "2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM ���� �� ����� ���� ������ 0
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "-1" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM ���� �� ����� ���� ������ 255
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "256" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM ���� ��� ���������� ����� 0
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "0" > NUL
if ERRORLEVEL 1 goto err
echo Test 12: passed successful

REM ���� ��� ���������� ����� 255
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "255" > NUL
if ERRORLEVEL 1 goto err
echo Test 13: passed successful

REM ���� ��� ���������� �� ����� ���� �������
%MyProgram% "crypt" "text.txt" "%TEMP%\output.txt" "abc" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 14: passed successful


REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1