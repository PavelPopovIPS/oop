@echo off

REM ������ �������� ��� ������� bat �����, ~ ������� ������.
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM � ����� ������ ��������� ������� �������� � �����
%MyProgram% 5 > NUL || goto err
echo Test 1: passed successful

REM � ������ ������� �������� �� ������������
%MyProgram% "text" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM � ������ ������ ������� �������� �� ������������
%MyProgram% "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM ������������� ����� �� �����������
%MyProgram% -5 > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM ���� ��� ��������� �� ����������
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1