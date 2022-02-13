@echo off

REM ������ �������� ��� ������� bat �����, ������ ~ ������� �������
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Compare equal files
(%MyProgram% "source.txt" "copySource.txt" && fc "source.txt" "copySource.txt") || goto err

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1