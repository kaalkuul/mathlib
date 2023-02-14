@echo off

cmake -S ..\.. -B build_install ^
    -DCMAKE_INSTALL_PREFIX="%CD%\usr" ^
    -DMATHLIB_BUILD_TEST_LIB=OFF ^
    -DMATHLIB_BUILD_TESTS=OFF
if errorlevel 1 goto failed

cmake --build build_install --config Release
if errorlevel 1 goto failed

cmake --build build_install --config Debug
if errorlevel 1 goto failed

cmake --install build_install --config Release
if errorlevel 1 goto failed

cmake --install build_install --config Debug
if errorlevel 1 goto failed


cmake -S . -B build -DCMAKE_PREFIX_PATH="%CD%\usr"
if errorlevel 1 goto failed

cmake --build build --config Release
if errorlevel 1 goto failed

cmake --build build --config Debug
if errorlevel 1 goto failed


echo.
echo Running program (Release)
build\Release\integration.exe
if errorlevel 1 goto failed
echo OK

echo.
echo Running program (Release)
build\Debug\integration.exe
if errorlevel 1 goto failed
echo OK


exit /B 0

:failed
echo Build failed
exit /B 1
