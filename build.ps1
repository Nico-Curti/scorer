#!/usr/bin/env powershell

#$env:CC = "clang-cl.exe"
#$env:CXX = "clang-cl.exe"
#$env:CC = "clang.exe"
#$env:CXX = "clang++.exe"

Remove-Item build -Force -Recurse -ErrorAction SilentlyContinue
New-Item -Path .\build -ItemType directory -Force > $null
Set-Location build

cmake -G "Ninja" "-DCMAKE_BUILD_TYPE=Release" ..
cmake --build . --config Release
Set-Location ..
