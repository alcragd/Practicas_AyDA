# 1. Configuración
$EXE = "./huffman.exe"
$OUTPUT_CSV = "CSV/resultados_huffman.csv"

# Crear carpeta CSV si no existe
if (!(Test-Path "CSV")) { New-Item -ItemType Directory -Path "CSV" | Out-Null }

# 2. Encabezado CONSOLIDADO (Una sola fila de títulos)
"Archivo,Tamano_Original_Bytes,Tamano_Comprimido_Bytes,Tiempo_Compresion_Seg,Tiempo_Descompresion_Seg" | Out-File -FilePath $OUTPUT_CSV -Encoding utf8

# 3. Lista de archivos (Asegúrate que las rutas sean correctas)
$archivos = @("Pruebas/test_0_5GB.dat","Pruebas/test_1GB.dat","Pruebas/test_1_2GB.dat","Pruebas/test_1_5GB.dat","Pruebas/test_1_8GB.dat") 

Write-Host "Iniciando pruebas..." -ForegroundColor Cyan

foreach ($f in $archivos) {
    if (Test-Path $f) {
        # --- PREPARACIÓN DE DATOS ---
        $sizeOrig = (Get-Item $f).Length
        
        # 1. Nombre limpio para el CSV (ej. "P5.bmp")
        $nombreCorto = [System.IO.Path]::GetFileName($f)
        
        # 2. Ruta real del archivo comprimido para el sistema (ej. "Pruebas/P5_compressed.dat")
        $compressedFile = $f -replace '\.[^.]+$', '_compressed.dat'

        # Inicializar variables de resultados en 0 o "N/A"
        $sizeComp = 0
        $tiempo_c = "N/A"
        $tiempo_d = "N/A"

        Write-Host "Procesando: $nombreCorto ($sizeOrig bytes)..." -NoNewline -ForegroundColor Yellow

        # --- FASE 1: COMPRESIÓN ---
        $out_c = & $EXE $f 1 2>&1 | Out-String
        if ($out_c -match "TIEMPO_EJECUCION:\s+([\d\.]+)") {
            $tiempo_c = $Matches[1]
            
            # Verificar si se creó el archivo para obtener su peso
            if (Test-Path $compressedFile) {
                $sizeComp = (Get-Item $compressedFile).Length
            }
        }

        # --- FASE 2: DESCOMPRESIÓN ---
        # Solo intentamos descomprimir si existe el archivo comprimido
        if (Test-Path $compressedFile) {
            $out_d = & $EXE $compressedFile 2 2>&1 | Out-String
            if ($out_d -match "TIEMPO_EJECUCION:\s+([\d\.]+)") {
                $tiempo_d = $Matches[1]
            }
        }

        # --- ESCRITURA FINAL (Una sola vez por archivo) ---
        # Se escribe todo en una sola línea: Nombre, PesoOrig, PesoComp, TiempoC, TiempoD
        "$nombreCorto,$sizeOrig,$sizeComp,$tiempo_c,$tiempo_d" | Out-File -FilePath $OUTPUT_CSV -Append -Encoding utf8
        
        Write-Host " [OK]" -ForegroundColor Green
    } else {
        Write-Host "`nAdvertencia: No se encuentra $f" -ForegroundColor DarkGray
    }
}

Write-Host "`nResultados guardados en $OUTPUT_CSV" -ForegroundColor Green