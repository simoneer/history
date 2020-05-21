

#include "phone.h"


#define THREE_WIRE
#define FLIP
#define DASH 0x0E0E


void paint_screen (SCREEN *type, int count)
{

   int i;

//
// Draw keys on screen.
//

   area_clear (-1,640,-1, 200);         // Ensure screen is cleared. /* CL */

   for ( i=0; i<=count-1; i++ )
      {
      if (((type+i)->box_number) & NOBORDER)                            /* FC.2 */
          goto skipborder;                                              /* FC.2 */
#ifdef FLIP
      if (((type+i)->box_number) & UNSELECTABLE)                        /* FC.2 */
          {                                                             /* FC.2 */
          set_line_pat(DASH);                                           /* FC.2 */
          box ( 639-((type+i)->low_box_corner_x+3),                     /* FC.2 */
                199-((type+i)->low_box_corner_y),                       /* FC.2 */
                639-((type+i)->top_box_corner_x),                       /* FC.2 */
                199-((type+i)->top_box_corner_y-3),                     /* FC.2 */
                    1+LINE_PAT );                                       /* FC.2 */
          }                                                             /* FC.2 */
      else                                                              /* FC.2 */
          {                                                             /* FC.2 */
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->low_box_corner_y),
                639-((type+i)->top_box_corner_x),
                199-((type+i)->top_box_corner_y-3),
                 DFLT );

          // BOTTOM OF BOX SHADING
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->low_box_corner_y),
                639-((type+i)->low_box_corner_x+7),
                199-((type+i)->top_box_corner_y-5),
                 1+FILL_SOLID );

          // RIGHT SIDE OF BOX SHADING
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->top_box_corner_y-5),
                639-((type+i)->top_box_corner_x),
                199-((type+i)->top_box_corner_y-3),
                 1+FILL_SOLID );
          }
#else FLIP
      if (((type+i)->box_number) & UNSELECTABLE)                        /* FC.2 */
          {                                                             /* FC.2 */
          set_line_pat(DASH);                                           /* FC.2 */
          box ( (type+i)->low_box_corner_x+3,                           /* FC.2 */
                (type+i)->low_box_corner_y,                             /* FC.2 */
                (type+i)->top_box_corner_x,                             /* FC.2 */
                (type+i)->top_box_corner_y-3,                           /* FC.2 */
                    1+LINE_PAT );                                       /* FC.2 */
          }                                                             /* FC.2 */
      else                                                              /* FC.2 */
          {                                                             /* FC.2 */
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->low_box_corner_y,
                (type+i)->top_box_corner_x,
                (type+i)->top_box_corner_y-3,
                 DFLT );

          // BOTTOM OF BOX SHADING
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->low_box_corner_y,
                (type+i)->low_box_corner_x+7,
                (type+i)->top_box_corner_y-5,
                 1+FILL_SOLID );

          // RIGHT SIDE OF BOX SHADING
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->top_box_corner_y-5,
                (type+i)->top_box_corner_x,
                (type+i)->top_box_corner_y-3,
                 1+FILL_SOLID );
          }
#endif FLIP
skipborder:
      }

//
// Print alpha on keys
//

   for ( i=0; i<=count-1; i++ )
      {
      print_key (type, i, 0);      // print keys with 0 shift
      }
}





void  print_key (SCREEN *type, int i, int shift)
{
   int style;

// ADJUST FONT TYPE FOR EACH KEY FOR THE FIRST KEY LINE
      switch ((type+i)->font1)
         {
         case 's':
            curr_font( font_small );
            style = font_small;
            break;
         case 'm':
            curr_font( font_medium );
            style = font_medium;
            break;
         case 'l':
            curr_font( font_large );
            style = font_large;
            break;
         case 'i':                                                      /* FC.2 */
            curr_font( font_icon );                                     /* FC.2 */
            style = font_icon;                                          /* FC.2 */
            break;                                                      /* FC.2 */
         default:
            break;
         }



// Adjust font rotation for each key
#ifdef FLIP
            switch ((type+i)->rotation1)
               {
               case '0':                                /* fc.2 */
                  font_rotate( style, _0_DEGREES );     /* fc.2 */
                  break;                                /* fc.2 */
               case '1':
                  font_rotate( style, _270_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _90_DEGREES );
                  break;
               default:
                  break;
               }
#else FLIP
            switch ((type+i)->rotation1)
               {
               case '0':                                /* fc.2 */
                  font_rotate( style, _180_DEGREES );   /* fc.2 */
                  break;                                /* fc.2 */
               case '1':
                  font_rotate( style, _90_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _270_DEGREES );
                  break;
               default:
                  break;
               }
#endif FLIP


// Adjust direction of print for each key
#ifdef FLIP
      switch ((type+i)->direction1)
         {
         case 'l':
            line_direction( TEXT_R_TO_L );
            break;
         case 'r':
            line_direction( TEXT_L_TO_R );
            break;
         case 't':
            line_direction( TEXT_B_TO_T );
            break;
         case 'b':
            line_direction( TEXT_T_TO_B );
            break;
         default:
            break;
         }
#else FLIP
      switch ((type+i)->direction1)
         {
         case 'l':
            line_direction( TEXT_L_TO_R );
            break;
         case 'r':
            line_direction( TEXT_R_TO_L );
            break;
         case 't':
            line_direction( TEXT_T_TO_B );
            break;
         case 'b':
            line_direction( TEXT_B_TO_T );
            break;
         default:
            break;
         }
#endif FLIP


// Adjust justification for each key
      switch ((type+i)->justification1)
         {
         case 's':
            line_justify (JUSTIFY_START);
            break;
         case 'c':
            line_justify (JUSTIFY_CENTER);
            break;
         case 'e':
            line_justify (JUSTIFY_END);
            break;
         default:
            break;
         }

#ifdef FLIP
      if ( (type+i)->direction1 == 'r' )
         {
         print_tabs ( (type+i)->text_1_x-shift,
                      (type+i)->text_1_y+shift,
                      (type+i)->text_1,
                      (type+i)->text_1_len );
         }
      else
         {
         print_font ( 639-((type+i)->text_1_x-shift),
                      199-((type+i)->text_1_y+shift),
                      (type+i)->text_1,
                      (type+i)->text_1_len);
         }
#else FLIP
      if ( (type+i)->direction1 == 'r' )
         {
         print_tabs ( (type+i)->text_1_x-shift,
                      (type+i)->text_1_y+shift,
                      (type+i)->text_1,
                      (type+i)->text_1_len );
         }
      else
         {
         print_font ( 639-((type+i)->text_1_x-shift),
                      199-((type+i)->text_1_y+shift),
                      (type+i)->text_1,
                      (type+i)->text_1_len);
         }
#endif FLIP






// ADJUST FONT TYPE FOR EACH KEY FOR THE SECOND KEY LINE
      switch ((type+i)->font2)
         {
         case 's':
            curr_font( font_small );
            style = font_small;
            break;
         case 'm':
            curr_font( font_medium );
            style = font_medium;
            break;
         case 'l':
            curr_font( font_large );
            style = font_large;
            break;
         case 'i':                                                      /* FC.2 */
            curr_font( font_icon );                                     /* FC.2 */
            style = font_icon;                                          /* FC.2 */
            break;                                                      /* FC.2 */
         default:
            break;
         }



// Adjust font rotation for each key
#ifdef FLIP
            switch ((type+i)->rotation2)
               {
               case '1':
                  font_rotate( style, _270_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _90_DEGREES );
                  break;
               default:
                  break;
               }
#else FLIP
            switch ((type+i)->rotation2)
               {
               case '1':
                  font_rotate( style, _90_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _270_DEGREES );
                  break;
               default:
                  break;
               }
#endif FLIP


// Adjust direction of print for each key
#ifdef FLIP
      switch ((type+i)->direction2)
         {
         case 'l':
            line_direction( TEXT_R_TO_L );
            break;
         case 'r':
            line_direction( TEXT_L_TO_R );
            break;
         case 't':
            line_direction( TEXT_B_TO_T );
            break;
         case 'b':
            line_direction( TEXT_T_TO_B );
            break;
         default:
            break;
         }
#else FLIP
      switch ((type+i)->direction2)
         {
         case 'l':
            line_direction( TEXT_L_TO_R );
            break;
         case 'r':
            line_direction( TEXT_R_TO_L );
            break;
         case 't':
            line_direction( TEXT_T_TO_B );
            break;
         case 'b':
            line_direction( TEXT_B_TO_T );
            break;
         default:
            break;
         }
#endif FLIP


// Adjust justification for each key
      switch ((type+i)->justification2)
         {
         case 's':
            line_justify (JUSTIFY_START);
            break;
         case 'c':
            line_justify (JUSTIFY_CENTER);
            break;
         case 'e':
            line_justify (JUSTIFY_END);
            break;
         default:
            break;
         }


#ifdef FLIP
      if ( (type+i)->direction2 == 'r' )
         {
         print_tabs ( (type+i)->text_2_x-shift,
                      (type+i)->text_2_y+shift,
                      (type+i)->text_2,
                      (type+i)->text_2_len );
         }
      else
         {
         print_font ( 639-((type+i)->text_2_x-shift),
                      199-((type+i)->text_2_y+shift),
                      (type+i)->text_2,
                      (type+i)->text_2_len);
         }
#else FLIP
      if ( (type+i)->direction2 == 'r' )
         {
         print_tabs ( (type+i)->text_2_x-shift,
                      (type+i)->text_2_y+shift,
                      (type+i)->text_2,
                      (type+i)->text_2_len );
         }
      else
         {
         print_font ( 639-((type+i)->text_2_x-shift),
                      199-((type+i)->text_2_y+shift),
                      (type+i)->text_2,
                      (type+i)->text_2_len);
         }
#endif FLIP

}




int  scan_screen (SCREEN *type, int count)
{



#define  TIMEOUT  15

   unsigned int cmd;
           int  i;
           int  right_button=0;            // Init to button up
   static  int  curr_key=0;                // Current key value
   static  int  last_key=0;                // Last key value
   static  int  typo_cnt=0;                // Timer for typomatic keying.
   static  int  key_state=0;               // Key pressed state memory.
           int  x,y;                       // Mouse location
           char keyval;                    // Keyboard input value



// mouse_show_crsr();                      // display the mouse cursor

//
// Loop - until the left mouse button is pressed.
//
      asm  mov ax, 01h                 // Show cursor
      asm  int 33h

   while ((right_button & 1) == 0)
      {
      asm  mov ah, 0bh                 // Allow control break to work
      asm  int 21h

      asm  mov ax, 03h                 // Get button status
      asm  int 33h
      asm  mov right_button, bx
      }

      asm  mov ax, 02h                 // Hide cursor
      asm  int 33h
//
// Loop and display selection until finger is lifted.
//
//

   while ((right_button & 1) == 1)
      {


// get x,y position & translate to key number

      asm  mov ax, 03h                 // Get button status
      asm  int 33h
      asm  mov right_button, bx

      asm  mov x, cx                   // Get x & y values
      asm  mov y, dx



// SEE IF THERE IS AN ACTIVE KEY
      for (i=0; i<=count-1; i++)
         {
#ifdef FLIP
         if ( ( 639-((type+i)->low_activ_corner_x) >= x ) &&
              ( 639-((type+i)->top_activ_corner_x) <= x ) &&
              ( 199-((type+i)->low_activ_corner_y) >= y )  &&
              ((((type+i)->box_number) & UNSELECTABLE)== 0)  &&         /* FC.2 */
              ( 199-((type+i)->top_activ_corner_y) <= y )    )
#else FLIP
         if ( ( (type+i)->low_activ_corner_x <= x ) &&
              ( (type+i)->top_activ_corner_x >= x ) &&
              ( (type+i)->low_activ_corner_y <= y ) &&
              ((((type+i)->box_number) & UNSELECTABLE)== 0)  &&         /* FC.2 */
              ( (type+i)->top_activ_corner_y >= y )    )
#endif FLIP
            {                           /* get key#, but mask flags out */
            curr_key = ((type+i)->box_number) & 0x0FFF;                 /* FC.2 */
            break;
            }
         }



// KEY ACTION IS DETERMINED BY THE FOLLOWING STATE MACHINE:
//  - NO KEYS EVER ACTIVE & INACTIVE AREA ENTERED => NO ACTION
//
//  - NO KEYS EVER ACTIVE &   ACTIVE AREA ENTERED => LIGHT KEY
//
//  - KEY HAS BEEN ACTIVE & INACTIVE AREA ENTERED => TURN LAST KEY OFF
//
//  - KEY HAS BEEN ACTIVE &   ACTIVE AREA ENTERED => TURN LAST KEY OFF &
//                                                   TURN NEW  KEY ON

      switch (key_state)
         {
         case 0:
            if (count == i)                      // box is not defined
               {
               key_state = 0;
               typo_cnt = 0;
               }
            else
               {
               box_on (type, curr_key);          // box is defined
               last_key = curr_key;
               key_state = 1;
               typo_cnt = 0;
               }
            break;
         case 1:
            if (count == i)
               {
               box_off (type, last_key);         // box is not defined
               key_state = 0;
               typo_cnt = 0;
               }
            else
               {
               if (curr_key != last_key)         // box is defined
                  {
                  box_on (type, curr_key);
                  box_off (type, last_key);
                  last_key = curr_key;
                  key_state = 1;
                  typo_cnt = 0;
                  }
               }
            break;
         }


// TIMER TO PERFORM TYPOMATIC OPERATION.
      delay (100);

      typo_cnt ++;

      if (typo_cnt >= TIMEOUT + 2)
         {
         typo_cnt = TIMEOUT;
         break;
         }
      }


// TURN OFF BOX IF LEFT BUTTON RELEASED
   if ((mouse_state.buttons & 1) == 0)
      {
      if ((((type+i)->box_number) & _ON_FLAG_) != FALSE)                /* FC.2 */
         box_off (type, last_key);

      if ((curr_key == last_key) && (curr_key > 0))  key_state = 0;



// Give user some audible feedback when he hits a valid key.

#define PCSOUND

      if (count != i)
         {
         #ifdef PCSOUND
            sound (500);                           /* FC.2 */
            delay (100);                           /* FC.2 */
            nosound ();
         #else PCSOUND
         #endif PCSOUND
         }
      }

   if (count == i)  curr_key = 100;    // Prevent inactive key data entry

   return (curr_key);
}




// SHIFTS TEXT AND HIGHLIGHTS BOX
void box_on (SCREEN *type, int i)
{
   char dim_pat[] = {1, 2, 0x88, 0x22};

   set_fill_pat (dim_pat, 1, 0);

//    if ((((type+i)->box_number) & _ON_FLAG_) == FALSE)                /* FC.2 */
          (type+i)->box_number |= _ON_FLAG_;   /* Keep track of ON state */ /* FC.2 */
//    else                                                              /* FC.2 */
//        return;                       /* else NOP if already ON */    /* FC.2 */

#ifdef FLIP
      if ((((type+i)->box_number) & NOBORDER) == FALSE)                 /* FC.2 */
        area_clear ((type+i)->low_box_corner_x,
                    (type+i)->top_box_corner_x,
                    (type+i)->low_box_corner_y,
                    (type+i)->top_box_corner_y);

        box( 639-((type+i)->low_box_corner_x+3),
             199-((type+i)->low_box_corner_y),
             639-((type+i)->top_box_corner_x),
             199-((type+i)->top_box_corner_y-3),
              1+XOR_PEL+FILL_PAT );
#else FLIP
      if ((((type+i)->box_number) & NOBORDER) == FALSE)                 /* FC.2 */
        area_clear ((type+i)->low_box_corner_x,
                    (type+i)->top_box_corner_x,
                    (type+i)->low_box_corner_y,
                    (type+i)->top_box_corner_y);

        box( (type+i)->low_box_corner_x+3,
             (type+i)->low_box_corner_y,
             (type+i)->top_box_corner_x,
             (type+i)->top_box_corner_y-3,
              1+XOR_PEL+FILL_PAT );
#endif FLIP

      if ((((type+i)->box_number) & NOBORDER) == FALSE)                 /* FC.2 */
        print_key (type, i, 5);
}

// DISPLAYS ORIGINAL BOX
void box_off (SCREEN *type, int i)
{

//    if ((((type+i)->box_number) & _ON_FLAG_) == FALSE)                /* FC.2 */
//        return;                       /* else NOP if already OFF */   /* FC.2 */
//    else                                                              /* FC.2 */
          (type+i)->box_number &= ~_ON_FLAG_;  /* Keep track of OFF state */ /* FC.2 */

        set_fill_solid( DFLT );
        if (((type+i)->box_number) & NOBORDER)                          /* FC.2 */
            {                           /* if no boxes or border */     /* FC.2 */
            box_on(type,i);             /* only flip fill pattern */    /* FC.2 */
            return;                                                     /* FC.2 */
            }

#ifdef FLIP
   area_clear ((type+i)->low_box_corner_x,
               (type+i)->top_box_corner_x,
               (type+i)->low_box_corner_y,
               (type+i)->top_box_corner_y);

      if (((type+i)->box_number) & UNSELECTABLE)                        /* FC.2 */
          {                                                             /* FC.2 */
          set_line_pat(DASH);                                           /* FC.2 */
          box ( 639-((type+i)->low_box_corner_x+3),                     /* FC.2 */
                199-((type+i)->low_box_corner_y),                       /* FC.2 */
                639-((type+i)->top_box_corner_x),                       /* FC.2 */
                199-((type+i)->top_box_corner_y-3),                     /* FC.2 */
                    1+LINE_PAT );                                       /* FC.2 */
          }                                                             /* FC.2 */
      else                                                              /* FC.2 */
          {                                                             /* FC.2 */
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->low_box_corner_y),
                639-((type+i)->top_box_corner_x),
                199-((type+i)->top_box_corner_y-3),
                 DFLT );

          // BOTTOM OF BOX SHADING
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->low_box_corner_y),
                639-((type+i)->low_box_corner_x+7),
                199-((type+i)->top_box_corner_y-5),
                 1+FILL_SOLID );

          // RIGHT SIDE OF BOX SHADING
          box ( 639-((type+i)->low_box_corner_x+3),
                199-((type+i)->top_box_corner_y-5),
                639-((type+i)->top_box_corner_x),
                199-((type+i)->top_box_corner_y-3),
                 1+FILL_SOLID );
          }
#else FLIP
   area_clear ((type+i)->low_box_corner_x,
               (type+i)->top_box_corner_x,
               (type+i)->low_box_corner_y,
               (type+i)->top_box_corner_y);

      if (((type+i)->box_number) & UNSELECTABLE)                        /* FC.2 */
          {                                                             /* FC.2 */
          set_line_pat(DASH);                                           /* FC.2 */
          box ( (type+i)->low_box_corner_x+3,                           /* FC.2 */
                (type+i)->low_box_corner_y,                             /* FC.2 */
                (type+i)->top_box_corner_x,                             /* FC.2 */
                (type+i)->top_box_corner_y-3,                           /* FC.2 */
                    1+LINE_PAT );                                       /* FC.2 */
          }                                                             /* FC.2 */
      else                                                              /* FC.2 */
          {                                                             /* FC.2 */
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->low_box_corner_y,
                (type+i)->top_box_corner_x,
                (type+i)->top_box_corner_y-3,
                 DFLT );

          // BOTTOM OF BOX SHADING
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->low_box_corner_y,
                (type+i)->low_box_corner_x+7,
                (type+i)->top_box_corner_y-5,
                 1+FILL_SOLID );

          // RIGHT SIDE OF BOX SHADING
          box ( (type+i)->low_box_corner_x+3,
                (type+i)->top_box_corner_y-5,
                (type+i)->top_box_corner_x,
                (type+i)->top_box_corner_y-3,
                 1+FILL_SOLID );
          }
#endif FLIP

   print_key (type, i, 0);

}



void type_font (int x, int y, char *text, int length,
                char font, char rot, char just)
{
   int style;

// Adjust font type for each key
      switch (font)
         {
         case 's':
            curr_font( font_small );
            style = font_small;
            break;
         case 'm':
            curr_font( font_medium );
            style = font_medium;
            break;
         case 'l':
            curr_font( font_large );
            style = font_large;
            break;
         case 'i':
            curr_font( font_icon );                                     /* FC.2 */
            style = font_icon;                                          /* FC.2 */
            break;                                                      /* FC.2 */
         default:
            break;
         }

// Adjust font rotation
#ifdef FLIP
            switch (rot)
               {
               case '1':
                  font_rotate( style, _270_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _90_DEGREES );
                  break;
               default:
                  break;
               }
#else FLIP
            switch (rot)
               {
               case '1':
                  font_rotate( style, _90_DEGREES );
                  break;
               case '2':
                  font_rotate( style, _180_DEGREES );
                  break;
               case '3':
                  font_rotate( style, _270_DEGREES );
                  break;
               default:
                  break;
               }
#endif FLIP

// Adjust justification for each key
      switch (just)
         {
         case 's':
            line_justify (JUSTIFY_START);
            break;
         case 'c':
            line_justify (JUSTIFY_CENTER);
            break;
         case 'e':
            line_justify (JUSTIFY_END);
            break;
         default:
            break;
         }


#ifdef FLIP
      print_font (639-x, 199-y, text, length);
#else FLIP
      print_font (x, y, text, length);
#endif FLIP
}




void area_clear (int x1, int x2, int y1, int y2)
{
#ifdef FLIP
   box ( 639-x1-1, 199-y1-1, 639-x2+1, 199-y2+1, 1+FILL_SOLID );
   box ( 639-x1-1, 199-y1-1, 639-x2+1, 199-y2+1, 1+XOR_PEL+FILL_SOLID );
#else FLIP
   box ( x1+1, y1+1, x2-1, y2-1, 1+FILL_SOLID );
   box ( x1+1, y1+1, x2-1, y2-1, 1+XOR_PEL+FILL_SOLID );
#endif FLIP
}




void start_phone (void)
{
int _AX;
        asm mov ax,0                    /* check for mouse - Fc.1 */
        asm int 33h
        asm mov _AX,ax
        if (_AX != -1)
            {
            printf("Mouse not installed!\n");
            exit(0);
            }
#ifdef THREE_WIRE
   int _segment;
   int _offset;

// ***************** START UP PHONE VIA 3W BIOS ***********************

asm      mov ah, 9aH             // get address of 3w status
asm      int 15H

asm      mov _offset,bx          // save offset of 3w status
asm      mov tw_stat_off,bx      // save offset of 3w status
asm      mov _segment,es         // save segment of 3w status
asm      mov tw_stat_seg,bx      // save segment of 3w status

asm      mov ax, 0000H           // clear general 3w status
asm      mov es:[bx], ax


// APP SHOULD CLEAR WATCHDOG TIMER <----------------------- ADD LATER

// SEND ADDR & PRODUCT CODE FOR HANDSET & PERIPHERAL TO TW I/F
asm      mov bx, 6040H           // handset
asm      mov cx, 0a000H          // peripheral
asm      mov ah, 99H
asm      int 15H

// APP SHOULD POWER ON PHONE HERE <----------------------- ADD LATER

// WAIT UNTIL 3W BIOS CAN ACCEPT A COMMAND
asm      mov es,_segment         // point to 3w general status
asm      mov bx,_offset

waitlp1:
asm      mov ax,0002H            // wait until command can be accepted
asm      and ax,es:[bx]
asm      jnz waitlp1

// SEND HANDSET AND PERIPHERAL SWITCH HOOK TO PHONE
asm      mov bx,606bH
asm      mov ah,98H
asm      int 15H


/*
asm      mov cx,0a01fH
asm      mov ah,98H
asm      int 15H   */
#endif THREE_WIRE
}




void tw_command (unsigned int cmd, int release)
{
#ifdef THREE_WIRE
   int _segment;
   int _offset;

// DELAY BETWEEN COMMANDS TO ALLOW DIGITS TO DISPLAY
   delay (200);

asm      mov ah, 9aH             // get address of 3w status
asm      int 15H

asm      mov _offset,bx          // save offset of 3w status
asm      mov _segment,es         // save segment of 3w status

// WAIT UNTIL 3W BIOS CAN ACCEPT A COMMAND
asm      mov es,_segment         // point to 3w general status
asm      mov bx,_offset

waitlp2:
asm      mov ax,0002H            // wait until command can be accepted
asm      and ax,es:[bx]
asm      jnz waitlp2

// GIVE COMMAND TO 3W BIOS
#endif THREE_WIRE
asm      mov bx, 6040h
asm      or  bx, cmd
asm      mov cmd, bx
asm      mov ah, 98H

#ifdef THREE_WIRE
asm      int 15H
#endif THREE_WIRE



// SEND RELEASE COMMAND TO 3W BIOS
   if (release)
      {
      asm      mov bx, 607fH
      asm      mov ah, 98H
#ifdef THREE_WIRE
      asm      int 15H
#endif THREE_WIRE
      }
}




void flush (void)
{
#ifdef THREE_WIRE
   delay (100);                  // don't flush too quickly
asm      mov ah, 9bH             // get address of 3w status
asm      int 15H
#endif THREE_WIRE
}




void dial_num (void)
{
   int i;
   unsigned int cmd;

                                       // dial phone number
   for (i=0; i<strlen (curr_phone_num); ++i)
      {
                                       // dial digit
      tw_command (xlat_key (curr_phone_num[i]), RELEASE);
      }

   delay (2000);

   cmd = 0x13;                         // send 'send' command
   tw_command (cmd, RELEASE);

}




unsigned int xlat_key (char digit)
{
   unsigned int cmd;

// CONVERT PARAMETER TO MICROTAC KEYCODE
   switch (digit)
      {
      case '1':
         cmd = 1;
         break;
      case '2':
         cmd = 2;
         break;
      case '3':
         cmd = 3;
         break;
      case '4':
         cmd = 5;
         break;
      case '5':
         cmd = 6;
         break;
      case '6':
         cmd = 7;
         break;
      case '7':
         cmd = 9;
         break;
      case '8':
         cmd = 0xa;
         break;
      case '9':
         cmd = 0xb;
         break;
      case '*':
         cmd = 0xd;
         break;
      case '0':
         cmd = 0xe;
         break;
      case '#':
         cmd = 0xf;
         break;
      default:
         break;
      }
   return (cmd);
}



void  put_backstk ()
{
   char far *cmd_line;
   char *endptr;

   if (strncmpi (new_screen, "   ", 3) != 0)
      {
// FROM ENV, GET ADDRESS WHERE NEW SCREEN CALLING SEQUENCE WILL BE PLACED
      cmd_line = (char far *) strtoul (getenv ("NAVSTACK"), &endptr, 16);
// COPY NEW CALLING SEQUENCE INTO NAVIGATION AREA
      _fstrcpy (cmd_line, call_seq);
      ret_code = 2;
      }
   else
      ret_code = 0;
}




void  print_tabs (int x, int y, char *text, int len)
{
#define CHARSP   12

   int i;
   char temp[1];

   for (i=0; i<=len; i++)
      {
      strncpy (temp, &text[i], 1);
      type_font ( x, y, temp, 1, 'm', '3', 's');
      x = x-CHARSP;
      }
}




void feat_select (int feat_num)
{
   unsigned int cmd;
   int i;

   cmd = HANDSET_ADDR | 0x1a;          // send function key
   tw_command (cmd, NORELEASE);
   cmd = HANDSET_ADDR | 0x01;          // send 1
   tw_command (cmd, NORELEASE);

   for (i=1; i<=feat_num; i++)
      {
      cmd = HANDSET_ADDR | 0x0f;       // send # to select feature
      tw_command (cmd, NORELEASE);
      }

   cmd = HANDSET_ADDR | 0x12;          // send clr to toggle feature
   tw_command (cmd, NORELEASE);

   cmd = HANDSET_ADDR | 0x17;          // send end to leave
   tw_command (cmd, RELEASE);
}






void tw_read_display ()
{
   int i;
   int time_out = 0;
   unsigned int temp;
   unsigned int disp_seg = tw_stat_seg;
   unsigned int disp_off = tw_stat_off + 30;
   unsigned int mod7_off = tw_stat_off + 44;



// WAIT UNTIL 7 SEGMENT DISPLAY IS VALID
   while (1)
      {
      asm      mov bx, mod7_off
      asm      mov es, disp_seg
      asm      mov ax,es:[bx]
      asm      mov temp, ax

      if (temp == 6)  break;
      delay (100);
      time_out ++;
      if (time_out == 20)  break;
      }


// READ SEVEN SEGMENT CONTENT
   for (i=0; i<=6; i++)
      {
      asm      mov bx, disp_off
      asm      mov es, disp_seg
      asm      mov ax,es:[bx]
      asm      and ax, 0ffh
      asm      mov temp, ax
      asm      inc bx
      asm      inc bx
      asm      mov disp_off,bx


      sev_seg[i] = temp;
      }
}





void ss_to_char ()
{
   int i;

   for (i=0; i<=6; i++)
      {
      switch (sev_seg[i])
         {
         case SS_ZERO:
            strcat (sev_seg_ch, " ");
            break;
         case SS_ONE:
            strcat (sev_seg_ch, "1");
            break;
         case SS_TWO:
            strcat (sev_seg_ch, "2");
            break;
         case SS_THREE:
            strcat (sev_seg_ch, "3");
            break;
         case SS_FOUR:
            strcat (sev_seg_ch, "4");
            break;
         case SS_FIVE:
            strcat (sev_seg_ch, "5");
            break;
         case SS_SIX:
            strcat (sev_seg_ch, "6");
            break;
         case SS_SEVEN:
            strcat (sev_seg_ch, "7");
            break;
         case SS_EIGHT:
            strcat (sev_seg_ch, "8");
            break;
         case SS_NINE:
            strcat (sev_seg_ch, "9");
            break;
         default:
            strcat (sev_seg_ch, " ");
            break;
         }
      }
}
