cls
@echo off

python make.py clean

if [%1]==[] goto standard
python make.py --region=NTSC_U --flags=%1
goto copy

:standard
python make.py --region=NTSC_U

:copy
xcopy "build/main_NTSC_U.dol" "romfs/NTSC_U/sys/main.dol" /y /f /i
xcopy "build/modules/SportsNet_NTSC_U.bin" "romfs/NTSC_U/files/modules/SportsNet_NTSC_U.bin" /y /f /i
xcopy "build/modules/SportsNet_NTSC_U.map" "romfs/NTSC_U/files/modules/SportsNet_NTSC_U.map" /y /f /i