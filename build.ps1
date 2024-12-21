$buildDir = "build"
$destDir = "$buildDir\\.."

# Configuração do CMake
if (-Not (Test-Path "CMakeCache.txt")) {
    Write-Host "[+] Configurando CMake no modo Release..."
    cmake -S . -B build
    if ($LASTEXITCODE -ne 0) {
        Write-Host "[-] Erro ao configurar CMake. Verifique as mensagens de erro."
        Exit 1
    }
    Write-Host "[+] CMake configurado com sucesso."
} else {
    Write-Host "[+] CMake já está configurado. Pulando configuração."
}

# Compilação do projeto
Write-Host "Compilando o projeto no modo Release..."
cmake --build build --config Release
if ($LASTEXITCODE -ne 0) {
    Write-Host "[-] Erro ao compilar o projeto. Verifique as mensagens de erro."
    Exit 1
}
Write-Host "[+] Projeto compilado com sucesso!"

# Movendo arquivos (habilitar se necessário)
if (-Not (Test-Path $destDir)) {
    Write-Host "[+] Diretório de destino '$destDir' não existe. Criando o diretório..."
    New-Item -ItemType Directory -Path $destDir | Out-Null
}
$dllFile = "$buildDir\\bin\\Release\\svcheat.dll"
if (Test-Path $dllFile) {
    Write-Host "[+] Movendo '$dllFile' para '$destDir'..."
    Move-Item -Path $dllFile -Destination $destDir -Force
    Write-Host "[+] Arquivo DLL movido com sucesso!"
} else {
    Write-Host "[+] Arquivo DLL não encontrado em '$dllFile'. Verifique se o build foi bem-sucedido."
}

Write-Host "[!] Processo concluído com sucesso!"