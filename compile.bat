@echo off
echo ���������·���滮��Ŀ...

:: �û�����: �����ʵ��SFML��װ·���޸�������һ��
SET SFML_DIR=C:\Tools\SFML

:: ���SFML��·��
if not exist "%SFML_DIR%\include\SFML" (
    echo ����: �� "%SFML_DIR%\include" ��δ�ҵ�SFMLͷ�ļ�Ŀ¼��
    echo ��ȷ��SFML��װ��ָ��Ŀ¼�£����޸Ĵ˽ű������� SFML_DIR ·����
    pause
    exit /b 1
)

:: ����mingw32���뻷��·��
SET PATH=C:\Tools\mingw32\bin;%PATH%

:: �������� - ʹ��C++14��׼
echo ����ʹ�� g++ ���������б��� (C++14��׼)...
g++ -std=c++14 -Wall -O2 ^
    -Iinclude -Isrc ^
    -I"%SFML_DIR%\include" ^
    -o build\RoboNavPlanner.exe ^
    src\main.cpp ^
    src\core\Map.cpp ^
    src\core\PathPlanner.cpp ^
    src\visualization\Visualizer.cpp ^
    -L"%SFML_DIR%\lib" ^
    -lsfml-graphics -lsfml-window -lsfml-system

if %ERRORLEVEL% EQU 0 (
    echo ����ɹ���build\RoboNavPlanner.exe �����ɡ�
    echo ��Ҫ��ʾ: ��������ʱ������ҪSFML��DLL�ļ���
) else (
    echo ����ʧ�ܣ����������Ϣ��
)

pause