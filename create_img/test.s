org 0x7c00
global _start


_start:
  mov cx,20
  mov ah,0Eh
  mov al,'H'
  mov bh,0Eh
  mov bl,0
  int 0x10
 
  mov ah,0Eh
  mov al,'E'
  mov bh,0Eh
  mov bl,10
  int 0x10
 
  mov ah,0Eh
  mov al,'L'
  mov bh,0Eh
  mov bl,20
  int 0x10

 
  mov ah,0Eh
  mov al,'L'
  mov bh,0Eh
  mov bl,30
  int 0x10
 
 
  mov ah,0Eh
  mov al,'O'
  mov bh,0Eh
  mov bl,40
  int 0x10
 
  hlt

times 510-($-$$) db 0
dw 0xAA55
