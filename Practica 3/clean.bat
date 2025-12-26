@echo off
echo Iniciando limpieza...

:: 1. Cierra el programa si se quedo trabado (evita error de Acceso Denegado)
taskkill /IM huffman.exe /F >nul 2>&1

:: 2. Borrar archivos descomprimidos en la raiz (uncompressed.txt, etc)
if exist "uncompressed.*" (
    del /F /Q "uncompressed.*"
)

:: 3. Borrar comprimidos que hayan quedado en la raiz
if exist "*_compressed.dat" (
    del /F /Q "*_compressed.dat"
)

:: 4. Borrar los comprimidos DENTRO de la carpeta Pruebas
if exist "Pruebas" (
    echo Limpiando carpeta Pruebas...
    del /F /Q "Pruebas\*_compressed.dat"
    :: Si por algun motivo se descomprimio algo dentro de Pruebas, borralo tambien
    del /F /Q "Pruebas\uncompressed.*" 2>nul
)

echo.
echo Limpieza finalizada exitosamente.
pause