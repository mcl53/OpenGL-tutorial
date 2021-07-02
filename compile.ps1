param ($rootPath)

& 'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\Launch-VsDevShell.ps1'

Set-Location $rootPath

cl /EHsc src\*.cpp /w /Iinclude /I"C:\Users\matth\vcpkg\installed\x86-windows\include" /Fe".\bin\main.exe" /std:c++17 /link ".\object\glad.o" "C:\Users\matth\vcpkg\installed\x86-windows\lib\assimp-vc142-mt.lib" "C:\Users\matth\vcpkg\installed\x86-windows\lib\glfw3dll.lib"
