@echo off
setlocal

set PRJ_ROOT=%cd%
set EXE_LOC=%PRJ_ROOT%/exec
set PRJ_LOC=%PRJ_ROOT%/code/*/
set TOOL_LOC=%EXE_LOC%/tools
set ARM_TOOL_LOC=%TOOL_LOC%/arm-tool
set CYG_TOOL_LOC=%TOOL_LOC%/Cygwin
set CYGPAHT=%CYG_TOOL_LOC%/bin/cygpath.exe
set ARMCC5_ASMOPT=%ARM_TOOL_LOC%
set ARMCC5_CCOPT=%ARM_TOOL_LOC%
set ARMCC5_FROMELFOPT=%ARM_TOOL_LOC%
set ARMCC5_LINKOPT=%ARM_TOOL_LOC%


echo ###############################################
echo PRJ_LOC:
echo ###############################################
echo %PRJ_LOC%
ls %PRJ_LOC%
echo 
echo ###############################################
echo TOOL_LOC:
echo ###############################################
echo %TOOL_LOC%
ls %TOOL_LOC%
echo 
echo ###############################################
echo ARM_TOOL_LOC:
echo ###############################################
echo %ARM_TOOL_LOC%
ls %ARM_TOOL_LOC%
echo 
echo ###############################################
echo CYG_TOOL_LOC:
echo ###############################################
echo %CYG_TOOL_LOC%
ls %CYG_TOOL_LOC%
echo 
echo ###############################################
echo CYGPAHT:
echo ###############################################
echo %CYGPAHT%
ls %CYGPAHT%
echo 
echo ###############################################
echo ARMCC5_ASMOPT:
echo ###############################################
echo %ARMCC5_ASMOPT%
ls %ARMCC5_ASMOPT%
echo 
echo ###############################################
echo ARMCC5_CCOPT:
echo ###############################################
echo %ARMCC5_CCOPT%
ls %ARMCC5_CCOPT%
echo 
echo ###############################################
echo ARMCC5_FROMELFOPT:
echo ###############################################
echo %ARMCC5_FROMELFOPT%
ls %ARMCC5_FROMELFOPT%
echo 
echo ###############################################
echo ARMCC5_LINKOPT:
echo ###############################################
echo %ARMCC5_LINKOPT%
ls %ARMCC5_LINKOPT%
echo 
echo ARM Tool Chain: Compiling done:
echo 

endlocal