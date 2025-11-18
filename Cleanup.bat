@echo off
echo Cleaning UE Project...

powershell.exe -ExecutionPolicy -Bypass -Command "ls -Recurse -Include Build, Intermediate, Binaries, *.sln, .vs | rmdir -Force -Recurse;"