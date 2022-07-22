org 0x7c00
global _start


_start:

  mov ax,25
  mov al,25
  mov ah,25
  
  mov bx,25
  mov bl,25
  mov bh,25
  
  mov cx,25
  mov cl,25
  mov ch,25
  
   
  mov dx,25
  mov dl,25
  mov dh,25
  
  mov ax,bx
  mov al,bl
  mov ah,bh

  mov bx,ax
  mov bl,al
  mov bh,ah

  mov cx,dx
  mov cl,dl
  mov ch,dh

  mov dx,cx
  mov dl,cl
  mov dh,ch
  
  sub dh,ch
  sub dx,cx
  sub dl,cl
 
  add dh,ch
  add dx,cx
  add dl,cl

  add dh,20

  ;low-level
  cmp dh,ch 
  cmp dl,cl
  ;high level
  cmp dx,cx

  mov sp,20
  mov bp,20
  mov bp,sp
  mov sp,bp

  




  jle _start
  

  hlt

times 510-($-$$) db 0
dw 0xAA55
