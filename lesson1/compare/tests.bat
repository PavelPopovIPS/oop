@echo off

REM ������ �������� ��� ������� bat �����, ������ ~ ������� �������
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Files with equal text should be equal
(%MyProgram% "source.txt" "copySource.txt" && fc "source.txt" "copySource.txt") || goto err

REM Files with equal text but different length should not be different
%MyProgram% "source.txt" "sourceWithoutOneChar.txt" && fc "source.txt" "sourceWithoutOneChar.txt"
if NOT ERRORLEVEL 1 goto err

REM Files whith different text should be different
%MyProgram% "source.txt" "newText.txt" && fc "source.txt" "newText.txt"
if NOT ERRORLEVEL 1 goto err

REM Empty files should be equal
%MyProgram% "emptyFile1.txt" "emptyFile2.txt" && fc "emptyFile1.txt" "emptyFile2.txt"
if ERRORLEVEL 1 goto err

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1