#!/usr/bin/env pwsh

$number_of_build_workers=8

if (Get-Command "cl.exe" -ErrorAction SilentlyContinue) {
  $vstype = "Professional"
  if (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2019\${vstype}\Common7\Tools") {
  }
  else {
    $vstype = "Enterprise"
    if (Test-Path "C:\Program Files (x86)\Microsoft Visual Studio\2019\${vstype}\Common7\Tools") {
    }
    else {
      $vstype = "Community"
    }
  }
  Write-Host "Found VS 2019 ${vstype}" -ForeGroundColor Yellow
  Push-Location "C:\Program Files (x86)\Microsoft Visual Studio\2019\${vstype}\Common7\Tools"
  cmd.exe /c "VsDevCmd.bat -arch=x64 & set" |
    ForEach-Object {
    if ($_ -match "=") {
      $v = $_.split("="); Set-Item -force -path "ENV:\$($v[0])"  -value "$($v[1])"
    }
  }
  Pop-Location
  Write-Host "Visual Studio 2019 ${vstype} Command Prompt variables set.`n" -ForeGroundColor Yellow
}
else {
  Write-Host "No Compiler found" -ForeGroundColor Red
}


# DEBUG
Remove-Item .\build_win_debug -Force -Recurse -ErrorAction SilentlyContinue
New-Item -Path .\build_win_debug -ItemType directory -Force
Set-Location build_win_debug
cmake -G "Visual Studio 16 2019" -T "host=x64" -A "x64" "-DCMAKE_BUILD_TYPE=Debug" "-DOMP=OFF" "-DPYwrap=OFF" ..
cmake --build . --config Debug --parallel ${number_of_build_workers} --target install
Set-Location ..

# RELEASE
Remove-Item .\build_win_release -Force -Recurse -ErrorAction SilentlyContinue
New-Item -Path .\build_win_release -ItemType directory -Force
Set-Location build_win_release
cmake -G "Visual Studio 16 2019" -T "host=x64" -A "x64" "-DCMAKE_BUILD_TYPE=Release" "-DOMP=OFF" "-DPYwrap=ON" ..
cmake --build . --config Release --parallel ${number_of_build_workers} --target install
Set-Location ..

