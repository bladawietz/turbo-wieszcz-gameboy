#include <gb/gb.h>
#include <rand.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>
#include "kafelki.c"
#include "grafika.c"
#include "tloWiersza.c"
#include "menu.c"
#include "sprite.c"
#include "koniec.c"
#include "tytuly.c"
#include "wersy1.c"
#include "wersy2.c"
#include "wersy3.c"
#include "wersy4.c"

void initRandom (void) {
    //zainicjuj ziarno liczb losowych
    UINT16 seed = LY_REG;
    seed |= (UINT16)DIV_REG << 8;
    initrand(seed);
}




void init(void) {
    DISPLAY_ON;
    set_bkg_data(0,233,kafelki);
    set_sprite_data(0,12,sprite);
    initrand (0);
    }

UINT8 blinkSpritePause(void) {
    UINT16 counter=0;
    UINT8 blink=1;
    UINT8 koniec=0;
    UINT8 keyPressed=0;
    SHOW_SPRITES;
    SHOW_BKG;
    while (!koniec) {
        counter++;
        if (counter>2500) {
            counter=0;
            blink=!blink;
        
            if (blink) {
                HIDE_SPRITES;
                }
            else {
                SHOW_SPRITES;
                }
        
        
        }
    if (joypad() & J_START) {
        keyPressed=1;
        koniec=1;
        }    
    if (joypad() & J_SELECT) {
        keyPressed=2;
        koniec=1;
        }
    }
    HIDE_SPRITES;
    initRandom();
    return keyPressed;
}

void titleScreen() {
    //najpierw pokazujemy planszę początkową
    HIDE_WIN;
    set_bkg_tiles(0,0,20,18,grafika);
    set_sprite_tile(0,0);
    set_sprite_tile(1,1);
    set_sprite_tile(2,2);
    move_sprite(0,140,150);
    move_sprite(1,148,150);
    move_sprite(2,156,150);
    
    blinkSpritePause();
    
    hide_sprite(0);
    hide_sprite(1);
    hide_sprite(2);

    initRandom();
    
}

void generujTytul (UINT8 titlenumber) {
    UINT8 i;
    for (i=0;i<18;i++) {
        tytul[i]=tytuly[titlenumber*18+i];
    }

}
void generujWers1 (UINT8 wersNumber) {
    UINT8 i;
    for (i=0;i<36;i++) {
        wers1[i]=wersy1[wersNumber*36+i];
    }

}

void generujWers2 (UINT8 wersNumber) {
    UINT8 i;
    for (i=0;i<36;i++) {
        wers2[i]=wersy2[wersNumber*36+i];
    }

}

void generujWers3 (UINT8 wersNumber) {
    UINT8 i;
    for (i=0;i<36;i++) {
        wers3[i]=wersy3[wersNumber*36+i];
    }

}

void generujWers4 (UINT8 wersNumber) {
    UINT8 i;
    for (i=0;i<36;i++) {
        wers4[i]=wersy4[wersNumber*36+i];
    }

}

void hide_selected_sprites(UINT8 fromSprite, UINT8 toSprite) {
    UINT8 temp;
    for (temp=fromSprite;temp<toSprite;temp++) {
        hide_sprite(temp);
    }

}

UINT8 menuWyboru (void) {
    UINT8 wybor=1;
    UINT8 koniec=0;
    UINT16 animCount=0;
    UINT8 klatka=1;
    HIDE_WIN;
    HIDE_SPRITES;
    set_bkg_tiles(0,0,20,18,tloWiersza);
    set_bkg_tiles(7,6,7,7,menu);
    set_sprite_tile(0,3);
    hide_selected_sprites(0,4);
    SHOW_SPRITES;
    SHOW_BKG;
    delay (200);
    while (!koniec) {
        
        animCount++;
        if (animCount==1000) {
            animCount=0;
            klatka++;
            if (klatka==4) {
                klatka=1;
            }
        }
        set_sprite_tile(1,3+klatka);
        move_sprite(0,40,64+16*(wybor-1));
        move_sprite(1,48,64+16*(wybor-1));
        
        if (joypad() & J_START) {
            koniec=1;
        }

        if (joypad() & J_UP) {
            wybor--;
            if (wybor==0) {
                wybor=4;
                }
            delay (200);
        }
        if (joypad() & J_DOWN) {
            wybor++;
            if (wybor==5) {
                wybor=1;
                }
            delay (200);
        }
    }
    return wybor;
}


void generuj(void) {
    UINT8 koniec=0;
    UINT8 temp;
    //UINT8 test=0;
    HIDE_BKG;
    HIDE_SPRITES;
    set_bkg_tiles(0,0,20,18,tloWiersza);
    SHOW_BKG;
    generujTytul(((UINT8)rand()) % (UINT8)tytulCount);
    //generujTytul(test);
    set_bkg_tiles(1,1,18,1,tytul);
    while (!koniec) {
        generujWers1(((UINT8)rand()) % (UINT8)wers1Count);
        //generujWers1(test);
        set_bkg_tiles(1,3,18,2,wers1);
        generujWers2(((UINT8)rand()) % (UINT8)wers2Count);
        //generujWers2(test);
        set_bkg_tiles(1,6,18,2,wers2);
        generujWers3(((UINT8)rand()) % (UINT8)wers3Count);
        //generujWers3(test);
        set_bkg_tiles(1,9,18,2,wers3);
        generujWers4(((UINT8)rand()) % (UINT8)wers4Count);
        //generujWers4(test);
        set_bkg_tiles(1,12,18,2,wers4);
        
        //napis: koniec, dalej
        set_bkg_tiles(1,16,18,1,napisDalej);
        
        //start
        set_sprite_tile(0,8);
        set_sprite_tile(1,9);
        set_sprite_tile(2,10);
        set_sprite_tile(3,11);
        
        for (temp=0;temp<2;temp++) {
            move_sprite(temp,92+8*temp,143);
            move_sprite(temp+2,20+8*temp,143);
            }
    
        /*test++;
        if (test==32) {
            test=0;
        }
        */
        delay (500);
        
        if (blinkSpritePause()==2) {
            koniec=1;
            HIDE_SPRITES;
        }

    }
    
}


void opcje (void) {


}


void autorzy (void) {


}

void cierpienie (void) {
    set_bkg_tiles(0,0,20,18,tloWiersza);
    set_bkg_tiles(5,6,11,3,cierpienieTekst);
    set_sprite_tile(0,0);
    set_sprite_tile(1,1);
    set_sprite_tile(2,2);
    move_sprite(0,80,130);
    move_sprite(1,88,130);
    move_sprite(2,96,130);
    delay (200);

    blinkSpritePause();
    
    hide_sprite(0);
    hide_sprite(1);
    hide_sprite(2);
    
}


void main () {
    UINT8 i=0;
    
    init();
    titleScreen();
    
    //głowna pętla programu

    while (1) {
        
        switch (menuWyboru()) {
            case 1: generuj();
                    break;
            
            case 2: opcje();
                    break;
            
            case 3: autorzy();
                    break;

            case 4: cierpienie();
                    break;
        }
    }
    
}
