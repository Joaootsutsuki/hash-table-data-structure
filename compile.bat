@echo off
REM ============================================
REM Compilacao - Tabela Hash
REM
REM ============================================

echo.
echo ========================================
echo   COMPILANDO TABELA HASH
echo ========================================
echo.

REM Limpa compilacao anterior
if exist *.o del *.o
if exist hash_table.exe del hash_table.exe

echo [1/7] Compilando main.c...
gcc -Wall -Wextra -O2 -std=c99 -c main.c -o main.o
if errorlevel 1 goto erro

echo [2/7] Compilando hash_table_ops.c...
gcc -Wall -Wextra -O2 -std=c99 -c hash_table_ops.c -o hash_table_ops.o
if errorlevel 1 goto erro

echo [3/7] Compilando hash_functions.c...
gcc -Wall -Wextra -O2 -std=c99 -c hash_functions.c -o hash_functions.o
if errorlevel 1 goto erro

echo [4/7] Compilando sorting.c...
gcc -Wall -Wextra -O2 -std=c99 -c sorting.c -o sorting.o
if errorlevel 1 goto erro

echo [5/7] Compilando statistics.c...
gcc -Wall -Wextra -O2 -std=c99 -c statistics.c -o statistics.o
if errorlevel 1 goto erro

echo [6/7] Compilando file_utils.c...
gcc -Wall -Wextra -O2 -std=c99 -c file_utils.c -o file_utils.o
if errorlevel 1 goto erro

echo [7/7] Linkando executavel...
gcc main.o hash_table_ops.o hash_functions.o sorting.o statistics.o file_utils.o -o hash_table.exe -lm
if errorlevel 1 goto erro

echo.
echo ========================================
echo   COMPILACAO CONCLUIDA COM SUCESSO!
echo ========================================
echo.
echo Executavel criado: hash_table.exe
echo.
echo Para executar digite: hash_table.exe
echo Ou simplesmente: hash_table
echo.

REM Limpa arquivos objeto
del *.o

goto fim

:erro
echo.
echo ========================================
echo   ERRO NA COMPILACAO!
echo ========================================
echo.
echo Verifique os erros acima e corrija.
echo.
pause
exit /b 1

:fim
pause