; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

[Setup]
; ע��: AppId ֵ����Ψһʶ���Ӧ�ó���
; ��ֹ������Ӧ�ó���İ�װ��ʹ����ͬ�� AppId ֵ��
; (��Ҫ����һ���µ� GUID����ѡ�񡰹��� | ���� GUID����)
AppId={{1CEC7523-C337-45A6-81E5-A6FDE5FA8097}
AppName=MyTanke
AppVerName=1.00
AppPublisher=�ҵĹ�˾
AppPublisherURL=http://www.example.com/
AppSupportURL=http://www.example.com/
AppUpdatesURL=http://www.example.com/
DefaultDirName={pf}\MyTanke
DefaultGroupName=MyTanke
OutputDir=E:\��Ҫ�İ�װ��\̹�˴�ս��װ��
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinese"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "E:\�ĵ�\��ѵ����\TKDZ\̹�˴�ս.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\cv100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\cvaux100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\cvcam100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\cxcore100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\cxts001.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\highgui100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\libguide40.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\ml100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\�ĵ�\��ѵ����\TKDZ\resource\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\MyTanke"; Filename: "{app}\̹�˴�ս.exe"

[Run]
Filename: "{app}\̹�˴�ս.exe"; Description: "{cm:LaunchProgram,MyTanke}"; Flags: nowait postinstall skipifsilent

