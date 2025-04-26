// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include <graphics.h>

extern vbe_mode_info_t mode_info;



int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}





int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (set_vbe_mode(mode) != 0) return 1;
  sleep(delay);
  return vg_exit();
}


/*
https://pages.up.pt/~up722898/aulas/lcom2425/lab5/lab5_5.html
This function shall:
1. map the video memory to the process' address space
2. change the video mode to that in its argument
3. draw a rectangle
4. reset the video mode to Minix's default text mode and return, upon receiving the break code of the ESC key (0x81)

Note that actions 1 and 2 could have been swapped. 
However, the LCF tests are not flexible, and require 1 to be performed before 2. 
This applies also to the other test functions that access the VRAM.
*/
int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  
  if (set_frame_buffer(mode) != 0) {return 1;}
  if (set_vbe_mode(mode) != 0) {return 1;}
  
  uint32_t new_color;
  if (normalize_color(color, &new_color) != 0) {return 1;}
  if (vg_draw_rectangle(x, y, width, height, new_color) != 0) {return 1;}

  if (wait_for_ESC() != 0) {return 1;}
  return vg_exit();
}




//see instructions here https://pages.up.pt/~up722898/aulas/lcom2425/lab5/lab5_5.html or slide 7C4 page 11
int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  if (set_frame_buffer(mode) != 0) {return 1;}
  if (set_vbe_mode(mode) != 0) {return 1;}

  int height = mode_info.YResolution / no_rectangles;
  int width = mode_info.XResolution / no_rectangles;

  for (int i = 0; i < no_rectangles; i++) {
    for (int j = 0; j < no_rectangles; j++) {
      
      uint32_t color;

      //If the color model is direct then the components of the rectangle with coordinates (row, col) are given by: 
      if (mode_info.MemoryModel == 0x06) { //slide 7video1 page 9/23?
        uint32_t R = ((first >> mode_info.RedFieldPosition) + j * step) % (1 << mode_info.RedMaskSize);
        uint32_t G = ((first >> mode_info.GreenFieldPosition) + i * step) % (1 << mode_info.GreenMaskSize);
        uint32_t B = ((first >> mode_info.BlueFieldPosition) + (i + j) * step) % (1 << mode_info.BlueMaskSize);
        color = (R << mode_info.RedFieldPosition) | (G << mode_info.GreenFieldPosition) | (B << mode_info.BlueFieldPosition);
      } 
      //If the color model is indexed then the (index of the) color of the rectangle with coordinates (row, col) is given by: 
      else {
        color = (first + (i * no_rectangles + j) * step) % (1 << mode_info.BitsPerPixel);
      }

      if (vg_draw_rectangle(j*width, i*height, width, height, color) != 0) {
        printf("Error drawing rectangle\n");
        return 1;
      }

    }
  }

  if (wait_for_ESC() != 0) {return 1;}
  return vg_exit();
}






// see:
// ppt 8xpm-1 till page 9
// https://pages.up.pt/~up722898/aulas/lcom2425/lab5/src/doc/group__lab5.html#gaa6590a9732657b667e741d4f4ac22bf6
int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  
  if (set_frame_buffer(0x105) != 0) {return 1;}
  if (set_vbe_mode(0x105) != 0) {return 1;}

  if (print_xpm(xpm, x, y) != 0) {return 1;}
  
  if (wait_for_ESC() != 0) {return 1;}
  return vg_exit();
}





int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

