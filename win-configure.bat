set SDL2DIR=d:/lib/SDL2

md ..\jse-2-build
cd ..\jse-2-build
cmake -L ..\jse-2
REM cmake --build . --config Debug

pause
