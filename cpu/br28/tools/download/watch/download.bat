@echo off

@echo ********************************************************************************
@echo 			SDK BR28			
@echo ********************************************************************************
@echo %date%

cd %~dp0


copy ..\..\script.ver .
copy ..\..\uboot.boot .
copy ..\..\ota.bin .
::copy ..\..\ota_all.bin .
::copy ..\..\ota_nor.bin .
copy ..\..\tone.cfg .
copy ..\..\cfg_tool.bin .
copy ..\..\app.bin .
copy ..\..\br28loader.bin .
copy ..\..\user_api.bin .
copy ..\..\isd_config.ini .
copy ..\..\p11_code.bin .
::copy ..\..\config.dat .
copy ..\..\default.key .
copy ..\..\json.txt .
copy ..\..\eq_cfg_hw.bin .

cd ..\..\ui_resource
copy *.* ..\download\watch

cd %~dp0

cd ..\..\ui_upgrade
copy *.* ..\download\watch\ui_upgrade
cd %~dp0


..\..\json_to_res.exe json.txt
..\..\md5sum.exe app.bin md5.bin
set /p "themd5=" < "md5.bin"

::..\..\packres.exe -keep-suffix-case JL.sty JL.res JL.str -n res -o JL
::..\..\packres.exe -keep-suffix-case sidebar.sty sidebar.res sidebar.str sidebar.tab -n res -o sidebar
::..\..\packres.exe -keep-suffix-case watch.sty watch.res watch.str watch.view watch.json -n res -o watch
::..\..\packres.exe -keep-suffix-case watch1.sty watch1.res watch1.str watch1.view watch1.json -n res -o watch1
::..\..\packres.exe -keep-suffix-case watch2.sty watch2.res watch2.str watch2.view watch2.json -n res -o watch2
::..\..\packres.exe -keep-suffix-case watch3.sty watch3.res watch3.str watch3.view watch3.json -n res -o watch3
::..\..\packres.exe -keep-suffix-case watch4.sty watch4.res watch4.str watch4.view watch4.json -n res -o watch4
::..\..\packres.exe -keep-suffix-case watch5.sty watch5.res watch5.str watch5.view watch5.json -n res -o watch5
::..\..\packres.exe -keep-suffix-case F_ASCII.PIX F_GB2312.PIX F_GB2312.TAB ascii.res -n res -o font
..\..\packres.exe -keep-suffix-case ui.res -n res -o ui

::echo %1

set CHIPKEY=default.key

:: 8MBytes
::..\..\packres.exe -keep-suffix-case F_ASCII.PIX ascii.res -n res -o font
::..\..\fat_comm.exe -pad-backup2 -force-align-fat -out new_res.bin -image-size 8 -filelist  JL sidebar watch3 watch4 font  -remove-empty -remove-bpb -mark-bad-after 0x7e0000 -key %CHIPKEY% -address 0
:: 16MBytes
..\..\packres.exe -keep-suffix-case BG.bin BG.res -n res -o BG
..\..\packres.exe -keep-suffix-case CBG.bin CBG.res -n res -o CBG
..\..\packres.exe -keep-suffix-case BIG1.bin BIG1.res -n res -o BIG1
..\..\packres.exe -keep-suffix-case CHG.bin CHG.res -n res -o CHG
..\..\packres.exe -keep-suffix-case L1B.bin L1B.res -n res -o L1B
..\..\packres.exe -keep-suffix-case L1S.bin L1S.res -n res -o L1S
..\..\packres.exe -keep-suffix-case L2B.bin L2B.res -n res -o L2B
..\..\packres.exe -keep-suffix-case L2S.bin L2S.res -n res -o L2S
..\..\packres.exe -keep-suffix-case L3B.bin L3B.res -n res -o L3B
..\..\packres.exe -keep-suffix-case L3S.bin L3S.res -n res -o L3S
..\..\packres.exe -keep-suffix-case L4B.bin L4B.res -n res -o L4B
..\..\packres.exe -keep-suffix-case L4S.bin L4S.res -n res -o L4S
..\..\packres.exe -keep-suffix-case L5B.bin L5B.res -n res -o L5B
..\..\packres.exe -keep-suffix-case L5S.bin L5S.res -n res -o L5S
..\..\packres.exe -keep-suffix-case PWO.bin PWO.res -n res -o PWO
..\..\packres.exe -keep-suffix-case WAT.bin WAT.res -n res -o WAT
..\..\fat_comm.exe -pad-backup2 -force-align-fat -out new_res.bin -image-size 16 -filelist myFont.bin ui BG CBG L1B L1S L2B L2S L3B L3S L4B L4S L5B L5S CHG PWO WAT -remove-empty -remove-bpb -mark-bad-after 0xfe0000 -key %CHIPKEY% -address 0

IF %ERRORLEVEL% NEQ 0 goto exit_point

del /Q res.ori\*
del upgrade.zip
move JL res.ori\JL
move watch? res.ori\
move font res.ori\font

..\..\packres.exe -n res -o res.bin new_res.bin 0 -normal
::����flash�������ļ���ʾ��Ϊ����0xb00000��ַ����Ҫ������nor_up.ufw
::..\..\packres.exe -n res -o res.bin new_res.bin 0 nor_up.ufw 0xb00000 -normal


..\..\isd_download.exe -tonorflash -dev br28 -boot 0x120000 -div8 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res ui_upgrade p11_code.bin config.dat tone.cfg eq_cfg_hw.bin -uboot_compress -key %CHIPKEY% -ex_flash res.bin -ex_api_bin user_api.bin -reboot 2500 -format vm
::..\..\isd_download.exe -tonorflash -dev br28 -boot 0x120000 -div8 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res p11_code.bin config.dat -uboot_compress -key %CHIPKEY% -ex_flash res.bin -ex_api_bin user_api.bin 
::-format all
::-ex_flash res.bin

:: -format all
::-reboot 2500
:: -key xxxx.key

::-format all
::-reboot 100


@rem ɾ����ʱ�ļ�-format all
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty
if exist *.str del *.str
if exist *.anim del *.anim
if exist *.view del *.view
if exist *.json del *.json


::���ʹ������flash�������ļ�������ʽ������������ɵ�update.ufw�в�ֻ�����ֱ���Դ�ļ�������nor_up.ufw�ļ����ݡ�

@rem ���ɹ̼������ļ�
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ota.bin -type 100 -out jl_isd.fw
@rem �������ýű��İ汾��Ϣ�� FW �ļ���
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw


..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw
copy jl_isd.ufw update.ufw
del jl_isd.ufw

::..\..\zip.exe -r upgrade.zip res.ori update.ufw
..\..\zip.exe -r upgrade.zip update.ufw

@REM ���������ļ������ļ�
::ufw_maker.exe -chip AC800X %ADD_KEY% -output config.ufw -res bt_cfg.cfg

::IF EXIST jl_693x.bin del jl_693x.bin 


@rem ��������˵��
@rem -format vm        //����VM ����
@rem -format cfg       //����BT CFG ����
@rem -format 0x3f0-2   //��ʾ�ӵ� 0x3f0 �� sector ��ʼ�������� 2 �� sector(��һ������Ϊ16���ƻ�10���ƶ��ɣ��ڶ�������������10����)

:exit_point

ping /n 2 127.1>null
IF EXIST null del null
::pause
