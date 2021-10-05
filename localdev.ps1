$exenames = 'scoop', '7zip', 'sudo', 'coreutils', 'grep', 'sed', 'less', 'llvm', 'python', 'cmake', 'ninja', 'doxygen', 'ccache', 'cppcheck'

function InstallAppWithScoop {
    param ([string]$exename)
    $found = [bool] (Get-Command -ErrorAction Ignore -Type Application $exename)
    if ( $found ) {
        scoop update $exename
    }
    else {
        scoop install $exename
    }
}

foreach ($exename in $exenames) {
    if ($exename -eq 'scoop') {
        $found = [bool] (Get-Command -ErrorAction Ignore -Type Application $exename)
        if ( $found ) {
            scoop update $exename
        }
        else {
            Set-ExecutionPolicy RemoteSigned -scope CurrentUser -force
            Invoke-Expression (New-Object System.Net.WebClient).DownloadString('https://get.scoop.sh')
        }
        continue
    }
    if ($exename -eq 'llvm') {
        $found = [bool] (Get-Command -ErrorAction Ignore -Type Application clang-tidy) -And [bool] (Get-Command -ErrorAction Ignore -Type Application clang-format)
        if ( $found ) {
            scoop update $exename
        }
        else {
            InstallAppWithScoop $exename
        }
        continue
    }
    if ($exename -eq 'python') {
        $found = [bool] (Get-Command -ErrorAction Ignore -Type Application python3)
        if ( $found ) {
            scoop update $exename
        }
        else {
            InstallAppWithScoop $exename
        }
        continue
    }
    InstallAppWithScoop $exename
}

python -m pip install --upgrade pip
python -m pip install --upgrade cmake-format
python -m pip install --upgrade codecheck

Set-Location -Path ..
If (!(test-path vcpkg)) {
    git clone https://github.com/Microsoft/vcpkg.git
    vcpkg\bootstrap-vcpkg.bat
}
Set-Location -Path vcpkg
git pull --rebase
# $env:Path += ";$pwd\vcpkg"
# .\vcpkg integrate powershell
# static
.\vcpkg install gtest:x64-windows-static --recurse
.\vcpkg install argagg:x64-windows-static --recurse
.\vcpkg install spdlog:x64-windows-static --recurse
.\vcpkg install uvw:x64-windows-static --recurse
# .\vcpkg install libuv:x64-windows-static --recurse
# .\vcpkg install curl:x64-windows-static --recurse
# .\vcpkg install boringssl:x64-windows-static --recurse
# dll strange bug ctest reported [ctest] No tests were found!!! when built with dll
.\vcpkg install gtest:x64-windows --recurse
.\vcpkg install argagg:x64-windows --recurse
.\vcpkg install spdlog:x64-windows --recurse
.\vcpkg install uvw:x64-windows --recurse
# .\vcpkg install libuv:x64-windows --recurse
# .\vcpkg install curl:x64-windows --recurse
# .\vcpkg install boringssl:x64-windows --recurse
.\vcpkg integrate install
# Get-Location
Set-Location -Path ../quicplus -PassThru
