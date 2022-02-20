@echo off

REM ������ �������� ��� ������� bat �����, ������ ~ ������� �������
SET MyProgram="%~1"

REM ���� �������� �� ��������, ��������� ������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ����� � ����� ���������� � �������� ������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "16" "100" > NUL || goto err
fc "%TEMP%\output.txt" "test-1-standard.txt" > NUL || goto err
echo Test 1: passed successful

REM ����� � ����� ���������� � ����� ������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "Europe." "Asia." > NUL || goto err
fc "%TEMP%\output.txt" "test-2-standard.txt" > NUL || goto err
echo Test 2: passed successful

REM ����� � ����� ���������� � ������ ������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "At least" "More then" > NUL || goto err
fc "%TEMP%\output.txt" "test-3-standard.txt" > NUL || goto err
echo Test 3: passed successful

REM ����� � ����������� ����������� � ����� ������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "a" "AA" > NUL || goto err
fc "%TEMP%\output.txt" "test-4-standard.txt" > NUL || goto err
echo Test 4: passed successful

REM ����� � ����������� ����������� � ������ �������
%MyProgram% "text-mult-lines.txt" "%TEMP%\output.txt" "16" "999a999" > NUL || goto err
fc "%TEMP%\output.txt" "test-5-standard.txt" > NUL || goto err
echo Test 5: passed successful

REM ����� � ���������� ������� ������ � ������-����������: ma �� mama
%MyProgram% "text-mult-lines.txt" "%TEMP%\output.txt" "ma" "mama" > NUL || goto err
fc "%TEMP%\output.txt" "test-6-standard.txt" > NUL || goto err
echo Test 6: passed successful

REM ����� 1231234 ������ ������ 12312312345
%MyProgram% "12312312345.txt" "%TEMP%\output.txt" "1231234" "-------" > NUL || goto err
fc "%TEMP%\output.txt" "test-7-standard.txt" > NUL || goto err
echo Test 7: passed successful

REM ����� � ������ ���� �� ������ ����������
%MyProgram% "empty.txt" "%TEMP%\output.txt" "text" "TEXT2" > NUL || goto err
fc "%TEMP%\output.txt" "empty.txt" > NUL || goto err
echo Test 8: passed successful

REM ������ ��������� ��� ������ ���������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "text" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 9: passed successful

REM ������ ��������� ��� ���� ����������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "text" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 10: passed successful

REM �� ����������� ���������� � ������� ������ ������ ������
%MyProgram% "text-one-line.txt" "%TEMP%\output.txt" "" "TEXT2" > NUL
if NOT ERRORLEVEL 1 goto err
echo Test 11: passed successful

REM ����� ������ �������
echo Tests passed successfuly
exit /B 0

REM ������� ������ ���� ����� �� ������
:err
echo Test failed
exit /B 1