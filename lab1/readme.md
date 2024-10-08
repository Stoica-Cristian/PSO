# Preprocesare

gcc -E main.c -o main.i

# Compilare

gcc -S main.i -o main.S

# Asamblare

gcc -c main.S -o main.o

# Link-editare

gcc main.o -o main

# Obtinere directa fisier obiect

gcc -c main.c -o main.o

# Permite vizualizarea informațiilor din fișierele obiect
objdump -M intel -d filename

# Exercitiu 1

Utilitarul ar (archiver) pentru a crea o biblioteca statica. Optiuni:
    r - Adaugă fișierele specificate în arhivă. Dacă arhiva nu există, aceasta va fi creată
    c - Creează arhiva, dacă aceasta nu există
    s - Creează un index (tabel de simboluri) pentru arhivă
    d - Stergerea unui fisier din biblioteca
    t - Listarea continutului

eg: ar rcs libmylibrary.a obj1.o obj2.o ...
    ar d libmylibrary.a obj1.o
    ar t libmylibrary.a

Optiuni gcc:
    -L - Specifica compilatorului sa caute biblioteci în directorul specificat.
    -lmylib - Indica compilatorului să lege programul cu biblioteca 'libmymath.a'. Prefixul 'lib' si sufixul '.a' sunt 
     adaugate automat

gcc -static demo.c -o demo_static -L . -lmymath

error: /usr/bin/ld: cannot find -lc: No such file or directory

!!! Prin eliminarea -static functioneaza
UPDATE: sudo yum install glibc-static  - biblioteca libc statica

# Exercitiu 2

--creare bibliotecă
gcc -fPIC -c source1.c -o source1_shared.o

gcc -shared source1_shared.o source2_shared.o ... -o mylibrary.so

--linkare executabil cu biblioteca
gcc main.c -o main_shared -lmymath -L .

# Exercitiu 5

dynamic lib:
    LD_LIBRARY_PATH=. ./demo (your_program)

Linkare dinamică la run-time:

gcc main.c -ldl -o main
LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./main