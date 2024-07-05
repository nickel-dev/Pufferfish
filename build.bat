@echo off

set project=Pufferfish
set libdir=%cd%\lib\x64

if not exist build     mkdir build
if not exist build-int mkdir build-int

set opts=/EHsc /MD /std:c++20
set lopts=/SUBSYSTEM:CONSOLE
set incs=/I %cd%\third_party
set code=%cd%\source\*.cpp %cd%\source\render\*.cpp %cd%\source\base\*.cpp %cd%\third_party\glad\glad.c
set target=%cd%\build\%project%.exe
set libs=gdi32.lib user32.lib shell32.lib opengl32.lib SDL2.lib SDL2main.lib SDL2_image.lib

pushd build-int
cl %code% %incs% /Fe%target% %opts% /link /LIBPATH:%libdir% %libs% %lopts%
popd

if "%errorlevel%"=="0" start %cd%\build\%project%.exe