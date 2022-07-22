nasm -f bin test.s -o test.o;

objdump -D -b binary -mi386 -Maddr16,data16 test.o;

