:: clone repos
echo.
rmdir "../dependencies/xecs" /S /Q
git clone https://github.com/LIONant-depot/xECS.git "../dependencies/xecs"
if %ERRORLEVEL% GEQ 1 goto :ERROR

:: set up branch for xecs
cd ../dependencies/xecs/
git checkout Lesson09_Prefabs
if %ERRORLEVEL% GEQ 1 goto :ERROR

cd build
call GetDependencies.bat "return"
if %ERRORLEVEL% GEQ 1 goto :ERROR

:DONE
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
powershell write-host -fore White XECS - DONE!!
powershell write-host -fore White ------------------------------------------------------------------------------------------------------
goto :PAUSE

:ERROR
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------
powershell write-host -fore Red XECS - ERROR!!
powershell write-host -fore Red ------------------------------------------------------------------------------------------------------

:PAUSE
rem if no one give us any parameters then we will pause it at the end, else we are assuming that another batch file called us
if %1.==. pause
