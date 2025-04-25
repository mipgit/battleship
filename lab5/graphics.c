#include <lcom/lcf.h>
#include <graphics.h>
#include <machine/int86.h>




//3.1 set the graphics mode
//https://pages.up.pt/~up722898/aulas/lcom2425/lab5/lab5_3.html
int(set_vbe_mode)(uint16_t mode) {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ah = 0x4F;
  reg86.al = 0x02;
  //same as doing reg.ax = 0x4F02; 
  reg86.bx = mode | BIT(14); 
  if(sys_int86(&reg86) != 0) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }
  return 0;
}









