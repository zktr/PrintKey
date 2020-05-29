PrintKey
===

This application is for capturing desktop area (or partial) into a image file or clipboard, also with basic annotaion tools for capturted image.

It is based on wxWidgets.

Windows
---

Build with VS2017

Build Dependency: wxWidgets  

+ download [wxWidgets 3.0.4](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.4/wxWidgets-3.0.4.zip) (stable version)

+ unzip to wxWidgets folder.

+ open wxWidgets\build\msw\wx_vc12.sln with VS2017 and convert all the projects to VS2017 format.

+ change all vc12 project files' compile option from MD to MT, MDd to MTd. this can remove the runtime dependency of vc_rulltime dll. To faster the process, you can use notepad++ to open all wx_vc12_*.vcxproj file and replace MultiThreadedDebugDll with MultiThreadedDebug and MultiThreadedDll with MultiThreaded.

+ build all for config: Debug x64, Release x64 (build Win32 static libs on your request, or dll version, but you need to manually change the project file to link the dynamic link verison wxWidgets libs, also need copy necessary dlls to corresponding output exe folder.)

Build PrintKey  
Open PrintKey.sln and build the project, any include or link path error, please check if your wxWidgets source folder config in project properties dialog.

UI Tools
---

The application frame is auto generated from [Anthemion DialogBlocks 5.15](http://www.anthemion.co.uk/dialogblocks/)

Version History
---

1.0.0 Only Windows version, no annotation tools yet.