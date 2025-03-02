@echo off

set project=Pufferfish
set config=x64

if not exist %cd%\build     mkdir %cd%\build
if not exist %cd%\build-int mkdir %cd%\build-int

if not exist %cd%\build\SDL2.dll        copy %cd%\lib\%config%\SDL2.lib       %cd%\build
if not exist %cd%\build\SDL2_image.dll  copy %cd%\lib\%config%\SDL2_image.lib %cd%\build

set libdir=%cd%\lib\%config%

set opts=/EHsc /MD /std:c++20
set lopts=/SUBSYSTEM:CONSOLE
set incs=/I %cd%\third_party
set code=%cd%\source\*.cpp %cd%\source\game\*.cpp %cd%\source\input\*.cpp %cd%\source\sound\*.cpp %cd%\source\render\*.cpp %cd%\source\base\*.cpp %cd%\third_party\glad\glad.c
set target=%cd%\build\%project%.exe
set libs=gdi32.lib user32.lib shell32.lib opengl32.lib SDL2.lib SDL2main.lib SDL2_image.lib

pushd build-int
cl %code% %incs% /Fe%target% %opts% /link /LIBPATH:%libdir% %libs% %lopts%
popd

if %errorlevel%==0 start %target%