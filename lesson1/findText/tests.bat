@echo off

REM ������ �������� ��� ������� bat �����, ������ ~ ������� �������
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM App should not compare text if got one argument
%MyProgram% "emptyFile1.txt"
if NOT ERRORLEVEL 1 goto err

REM App should not compare text without arguments
%MyProgram%
if NOT ERRORLEVEL 1 goto err

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1