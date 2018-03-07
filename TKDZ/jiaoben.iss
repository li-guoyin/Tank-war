; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

[Setup]
; 注意: AppId 值用于唯一识别该应用程序。
; 禁止对其他应用程序的安装器使用相同的 AppId 值！
; (若要生成一个新的 GUID，请选择“工具 | 生成 GUID”。)
AppId={{1CEC7523-C337-45A6-81E5-A6FDE5FA8097}
AppName=MyTanke
AppVerName=1.00
AppPublisher=我的公司
AppPublisherURL=http://www.example.com/
AppSupportURL=http://www.example.com/
AppUpdatesURL=http://www.example.com/
DefaultDirName={pf}\MyTanke
DefaultGroupName=MyTanke
OutputDir=E:\重要的安装包\坦克大战安装包
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinese"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "E:\文档\培训代码\TKDZ\坦克大战.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\cv100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\cvaux100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\cvcam100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\cxcore100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\cxts001.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\highgui100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\libguide40.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\ml100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\文档\培训代码\TKDZ\resource\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\MyTanke"; Filename: "{app}\坦克大战.exe"

[Run]
Filename: "{app}\坦克大战.exe"; Description: "{cm:LaunchProgram,MyTanke}"; Flags: nowait postinstall skipifsilent

