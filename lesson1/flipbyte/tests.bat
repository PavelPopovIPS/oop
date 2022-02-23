@echo off

REM ������ �������� ��� ������� bat �����, ~ ������� ������.
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM �������� ��������� 6 ��������� ��������������
%MyProgram% "6" > NUL 
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM �������� ��������� 0 ��������� ��������������
%MyProgram% "0" > NUL 
if ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM �������� ��������� 255 ��������� ��������������
%MyProgram% "255" > NUL 
if ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM ������������� ����� �� ��������� � ���������
%MyProgram% "-1" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM �������� ����� 255 �� ��������� � ���������
%MyProgram% "256" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM �������� �� ����� ��������� �������� ���������� ������
%MyProgram% "abc6" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM �������� �� ����� ��������� ������ ������
%MyProgram% "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM ���� � ����� ����������� �� ����������
%MyProgram% "5" "3"> NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM ���� ��� ���� ���������� �� ����������
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1