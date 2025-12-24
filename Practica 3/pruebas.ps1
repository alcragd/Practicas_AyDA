# 1. Configuración
$EXE = "./huffman.exe"
$OUTPUT_CSV = "resultados_huffman.csv"

# 2. Encabezado
"Archivo,Tamano_Bytes,Operacion,Tiempo_Segundos" | Out-File -FilePath $OUTPUT_CSV -Encoding utf8

# 3. Lista de archivos (ajusta a tus nombres reales)
$archivos = @("prueba.txt" ,"Slime.png") 

Write-Host "Iniciando pruebas de rendimiento..." -ForegroundColor Cyan

foreach ($f in $archivos) {
    if (Test-Path $f) {
        $size = (Get-Item $f).Length
        Write-Host "Procesando: $f ($size bytes)" -ForegroundColor Yellow

        # --- COMPRESIÓN ---
        # Ejecutamos y capturamos TODA la salida (incluyendo errores)
        $out_c = & $EXE $f 1 2>&1 | Out-String
        
        # Buscamos la línea de tiempo de forma segura
        if ($out_c -match "TIEMPO_EJECUCION:\s+([\d\.]+)") {
            $tiempo_c = $Matches[1]
            "$f,$size,Compresion,$tiempo_c" | Out-File -FilePath $OUTPUT_CSV -Append -Encoding utf8
        } else {
            Write-Host "Error: No se encontró TIEMPO_EJECUCION en la compresión de $f" -ForegroundColor Red
        }

        # --- DESCOMPRESIÓN ---
        $nameOnly = [System.IO.Path]::GetFileNameWithoutExtension($f)
        $compressedFile = "$nameOnly" + "_compressed.dat"

        if (Test-Path $compressedFile) {
            $out_d = & $EXE $compressedFile 2 2>&1 | Out-String
            if ($out_d -match "TIEMPO_EJECUCION:\s+([\d\.]+)") {
                $tiempo_d = $Matches[1]
                "$f,$size,Descompresion,$tiempo_d" | Out-File -FilePath $OUTPUT_CSV -Append -Encoding utf8
            } else {
                Write-Host "Error: No se encontró TIEMPO_EJECUCION en la descompresión" -ForegroundColor Red
            }
        }
    }
}
Write-Host "`nPruebas finalizadas." -ForegroundColor Green