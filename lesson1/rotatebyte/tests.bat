@echo off

REM ������ �������� ��� ������� bat �����, ~ ������� ������.
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ������� ����� �� 2 ������� ��� ����� 17 ����������� �������
%MyProgram% "17" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM ������� ����� �� 2 ������� ��� ����� 0 ����������� �������
%MyProgram% "0" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM ������� ����� �� 2 ������� ��� ����� 255 ����������� �������
%MyProgram% "255" "2" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM ������������� ����� �� ��������� � ��������� byte
%MyProgram% "-1" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM ����� 256 �� ��������� � ��������� byte
%MyProgram% "256" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM ��������� ������ �� ��������� � ��������� byte
%MyProgram% "abcd" "2" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM ����� ����� �� 0 �������� ����� ����������� ���������
%MyProgram% "17" "0" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM ����� ����� �� 8 �������� ����� ����������� ���������
%MyProgram% "17" "8" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM ����� ����� �� 9 �������� ����� ����������� 1 ������ ����� � ����������� ���������
%MyProgram% "17" "9" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM �� ����������� ������������� �������� � ��������� <number of bits>
%MyProgram% "17" "-1" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM ��������� ������ �� ��������� � ��������� <number of bits>
%MyProgram% "17" "abcd" "L" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM ����� ����� �� 0 �������� ������ ����������� ���������
%MyProgram% "17" "0" "R" > NUL 
if ERRORLEVEL 1 goto err
echo Test 12: passed successful

REM ����� ����� �� 10 �������� ������ ����������� ������ ������ �� 2 ������� � ����������� ���������
%MyProgram% "17" "10" "L" > NUL 
if ERRORLEVEL 1 goto err
echo Test 13: passed successful

REM �� ����������� ������������ ��������� l ��� ����������� �����
%MyProgram% "17" "2" "l" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 14: passed successful

REM �� ����������� ������������ ��������� r ��� ����������� ������
%MyProgram% "17" "2" "r" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 15: passed successful

REM �� ����������� ������������ ����� ��� �����������
%MyProgram% "17" "2" "5" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 16: passed successful

REM �� ����������� ������������ ������ ��� �����������
%MyProgram% "17" "2" "xyz" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 17: passed successful

REM ���� ��� ������ ��������� �� ����������
%MyProgram% "17" "2" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 18: passed successful

REM ���� ��� ���� ���������� �� ����������
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 19: passed successful

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1