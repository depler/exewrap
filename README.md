# exewrap
Tiny wrapper to run executables from another folder. Only ~5kb in size, no dependencies, self-wrapper.

# Usage
This will create `curl.exe` wrapper, which run real curl executable from `\curl\curl.exe` relative subfolder:
```
exewrap.exe --d7k9FxrRM8-wrap \curl\curl.exe
move /y curl.exe ..\curl.exe
```
