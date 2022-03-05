@echo off

REM ������ �������� ��� ������� bat �����, ~ ������� ������.
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ���������� ��� ���� ���������� �� ����������
%MyProgram% > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM �� ����������� ���������� � ��������� ������ ������ 
%MyProgram% "" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 2: passed successful

REM ������� ������ �������� ������ �� ����� 
%MyProgram% "matrix-text.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 3: passed successful

REM ������� ������ ��������� �� ����� 3 �����
%MyProgram% "matrix-4row.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 4: passed successful

REM ������� ������ ��������� �� ����� 3 �����
%MyProgram% "matrix-2row.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 5: passed successful

REM ������� ������ ��������� �� ����� 3� ��������
%MyProgram% "matrix-2colum.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 6: passed successful

REM ������� � ������ ��������� � ����� �� ������� �� ��������������
%MyProgram% "matrix-empty-2x2.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 7: passed successful

REM ������ ���� �� ��������������
%MyProgram% "matrix-empty.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 8: passed successful

REM ������ ���� ���������� � ������ ��������� �� ��������������
%MyProgram% "matrixNoExist.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM ���� ������������ ������� ����� 0, �� ��� ��� ��� �������� �������
%MyProgram% "matrix-determinant-zero.txt" > NUL 
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM ���������� �������� ������� � ��������� � ��������
%MyProgram% "matrix-sample.txt" > "%TEMP%\output.txt"
fc "%TEMP%\output.txt" "matrix-sample-invert-double.txt"  > NUL 
if ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1