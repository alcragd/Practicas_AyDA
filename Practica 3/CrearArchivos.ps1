# 1. Configuración
$carpetaNombre = "Pruebas"
$rutaBase = Get-Location
$rutaCarpeta = Join-Path $rutaBase $carpetaNombre

# Limpiar archivos anteriores
if (Test-Path $rutaCarpeta) {
    Write-Host "Limpiando archivos antiguos..." -ForegroundColor Yellow
    Remove-Item "$rutaCarpeta\test_*" -Force
} else {
    New-Item -ItemType Directory -Path $rutaCarpeta | Out-Null
}

# 2. Configurar el Generador de Aleatoriedad
Write-Host "Inicializando generador de ruido aleatorio..." -ForegroundColor Cyan
$rnd = New-Object System.Random

# Creamos un Buffer de 4 MB para escribir rápido
$bufferSize = 4MB 
$buffer = New-Object byte[] $bufferSize

# LLENAMOS EL BUFFER CON DATOS ALEATORIOS UNA VEZ
# (Reutilizar este bloque aleatorio es suficiente para engañar a Huffman
#  y es mucho más rápido que generar 1GB número por número)
$rnd.NextBytes($buffer)

# 3. Función de Generación
function Crear-Archivo-Random ($nombre, $totalBytes) {
    $rutaCompleta = Join-Path $rutaCarpeta $nombre
    $start = Get-Date

    try {
        $stream = [System.IO.File]::Create($rutaCompleta)
        $restante = [long]$totalBytes
        
        while ($restante -gt 0) {
            # Calculamos cuánto escribir
            $count = [Math]::Min($restante, $bufferSize)
            
            # Escribimos el buffer aleatorio
            # (Nota: Para archivos > 4MB, el patrón aleatorio se repite cada 4MB,
            # pero la distribución de frecuencias sigue siendo uniforme, que es lo que importa)
            $stream.Write($buffer, 0, [int]$count)
            $restante -= $count
        }
        
        $stream.Close()
        
        $duration = ((Get-Date) - $start).TotalSeconds
        Write-Host " -> Creado: $nombre ($($duration.ToString("N2")) s)" -ForegroundColor Gray
    } catch {
        $msg = $_.Exception.Message
        Write-Host "Error en $nombre : $msg" -ForegroundColor Red
    }
}

Write-Host "Generando archivos con RUIDO ALEATORIO..." -ForegroundColor Cyan

# --- BLOQUE BYTES ---
# Crear-Archivo-Random "test_100B.txt" 100
# Crear-Archivo-Random "test_250B.txt" 250
# Crear-Archivo-Random "test_500B.txt" 500
# Crear-Archivo-Random "test_750B.txt" 750
# Crear-Archivo-Random "test_900B.txt" 900

# # --- BLOQUE KB ---
# Crear-Archivo-Random "test_10KB.bin"  10kb
# Crear-Archivo-Random "test_50KB.bin"  50kb
# Crear-Archivo-Random "test_100KB.bin" 100kb
# Crear-Archivo-Random "test_500KB.bin" 500kb
# Crear-Archivo-Random "test_800KB.bin" 800kb

# # --- BLOQUE MB ---
# Crear-Archivo-Random "test_1MB.dat"   1mb
# Crear-Archivo-Random "test_10MB.dat"  10mb
# Crear-Archivo-Random "test_50MB.dat"  50mb
# Crear-Archivo-Random "test_100MB.dat" 100mb
# Crear-Archivo-Random "test_500MB.dat" 500mb 

# # --- BLOQUE GB ---
# # Probamos hasta 1GB.
# # Si tienes mucha RAM y quieres probar el límite, descomenta los siguientes.
# Crear-Archivo-Random "test_0_5GB.dat"   0.5gb
# Crear-Archivo-Random "test_1GB.dat"   1gb
Crear-Archivo-Random "test_1_2GB.dat"   1.2gb
Crear-Archivo-Random "test_1_5GB.dat"   1.5gb
Crear-Archivo-Random "test_1_8GB.dat"   1.8gb

# Crear-Archivo-Random "test_1.5GB.dat" 1.5gb

Write-Host "`n¡Archivos aleatorios listos! Ejecuta pruebas_final.ps1" -ForegroundColor Green