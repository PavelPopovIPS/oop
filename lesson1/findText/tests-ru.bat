@echo off
REM File was saved to OEM-866 for russian

REM ���� ��㬥�� �� ����᪥ bat 䠩��, ᨬ��� ~ 㤠��� ����窨
SET MyProgram="%~1"

REM �᫨ ��㬥�� �� ��।���, �뢥����� �訡��
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Text should be found in the beginning of file 
%MyProgram% "text-ru.txt" "����"
if ERRORLEVEL 1 goto err
echo Test 1: passed successful

REM ����� ��諨 �ᯥ譮
echo Tests passed successfuly
exit /B 0

REM �뢥��� �訡�� �᫨ ���� �� ��諨
:err
echo Test failed
exit /B 1