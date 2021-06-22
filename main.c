#include <gb/gb.h>
#include <rand.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>
#include "kafelki.c"
#include "ekran_tytulowy.c"
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
#include "konfiguracja.c"
#include "napis_menu.c"
#include "napis_opcje.c"
#include "napis_koniec.c"
#include "napis_koniec2.c"
#include "napis_koniec3.c"
#include "about.c"

UINT8 typWiersza=1; // 1-ABAB 2-AABB 3-ABBA
UINT8 dzwieki=0; // 0 - brak, 1 - dźwięk

void initRandom (void) {
    //zainicjuj ziarno liczb losowych
    UINT16 seed = LY_REG;
    seed |= (UINT16)DIV_REG << 8;
    initrand(seed);
}




void init(void) {
    DISPLAY_ON;
    //set_bkg_data(0,255,kafelki);
    set_sprite_data(0,20,sprite);
    initRandom();
    }

UINT8 blinkSpritePause(void) {
    UINT16 counter=0;
    UINT8 blink=1;
    UINT8 koniec=0;
    UINT8 keyPressed=0;
    SHOW_SPRITES;
    //SHOW_BKG;
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
        keyPressed=joypad();
        if (keyPressed) {
            koniec=1;
        }  
    
    }
    
    while (joypad()) {

    }
    HIDE_SPRITES;
    initRandom();
    return keyPressed;
}

void titleScreen() {
    //najpierw pokazujemy planszę początkową
    //HIDE_WIN;
    set_bkg_data(0,167,ekran_tytulowy);
    set_bkg_tiles(0,0,20,18,grafika);
    set_sprite_tile(0,0);
    set_sprite_tile(1,1);
    set_sprite_tile(2,2);
    move_sprite(0,140,150);
    move_sprite(1,148,150);
    move_sprite(2,156,150);
    SHOW_BKG;

    blinkSpritePause();
    
    //hide_sprite(0);
    //hide_sprite(1);
    //hide_sprite(2);

    initRandom();
    //HIDE_WIN;
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
        move_sprite(0,40,72+16*(wybor-1));
        move_sprite(1,48,72+16*(wybor-1));
        
        if (joypad() & J_A) {
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
    while (joypad()) {
    }
    return wybor;
}

void pokazWers(unsigned char wers [], UINT8 pozycja) {

    set_bkg_tiles(1,3*pozycja,18,2,wers);
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
        //WERS 1
        // dla dowolnego typu wiersza pierwszy wers jest zawsze na tej samej pozycji
        generujWers1(((UINT8)rand()) % (UINT8)wers1Count);
        //generujWers1(test);
        pokazWers(wers1,1);
        
        //WERS 2
        //dla typu 1 i 3 pozycja 2, dla typu 2 pozycja 3
        generujWers2(((UINT8)rand()) % (UINT8)wers2Count);
        //generujWers2(test);
        if (typWiersza==2) {
            pokazWers(wers2,3);
        }
        else {
            pokazWers(wers2,2);

        }

        //WERS 3
        //dla trybu 1 poz. 3, dla trybu 2 pozycja 2, dla trybu 3 pozycja 4
        generujWers3(((UINT8)rand()) % (UINT8)wers3Count);
        //generujWers3(test);
        switch (typWiersza) {
            case 1: pokazWers(wers3,3);
            break;
            case 2: pokazWers(wers3,2);
            break;
            case 3: pokazWers(wers3,4);
            break;
            
        }


        //WERS 4
        //dla trybu 1 poz. 4, dla trybu 2 pozycja 4, dla trybu 3 pozycja 3       
        generujWers4(((UINT8)rand()) % (UINT8)wers4Count);
        //generujWers4(test);
        if (typWiersza==3) {
            pokazWers(wers4,3);
        }
        else {
            pokazWers(wers4,4);

        }
        
        //napis: koniec, dalej
        set_bkg_tiles(1,16,18,1,napisDalej);
        
        //start
        
        for (temp=0;temp<4;temp++) {
            set_sprite_tile(temp,12+temp);
            set_sprite_tile(temp+4,16+temp);
            if (temp<2) {
                move_sprite(temp,92+8*temp,139);
                move_sprite(temp+4,20+8*temp,139);    
            }
            else {
                move_sprite(temp,92+8*(temp-2),147);
                move_sprite(temp+4,20+8*(temp-2),147);
            }
            
        }
       
        //delay (500);
        
        if (blinkSpritePause()==J_B) {
            koniec=1;
            
        }

    }
    
}


void opcje (void) {
    UINT8 koniec=0;
    UINT8 opcja=1; // 1 - rodzaj wiersza, 2 -dźwięki
    UINT8 klatka=1;
    UINT8 licznik=0;
    UINT8 i=0;
    unsigned char falkaTMP[] ={0,0,0,0,0,0,0,0,0,0,0,0};

    set_bkg_tiles(0,0,20,18,tloWiersza);
    set_bkg_tiles(6,2,10,3,napis_opcje);
    set_bkg_tiles(3,7,14,7,konfiguracja);
    hide_selected_sprites(0,3);
    
    
    while (!koniec) {
        licznik++;
        if (licznik>250) {
            licznik=0;
            if (klatka==1) {
                klatka=2;
                for (i=0;i<12;i++) {
                    falkaTMP[i]=falkaOpcje_2[i];
                }
            }
            else {
                klatka=1;
                for (i=0;i<12;i++) {
                    falkaTMP[i]=falkaOpcje_1[i];
                }
            }

        }
        
        switch (opcja) {
            case 1: set_bkg_tiles(3+5*(typWiersza-1),10,4,1,falkaTMP);
                    set_bkg_tiles(3+9-7*dzwieki,14,3,1,falkaOpcje_1);
                    
                    if ( (joypad() & J_LEFT) && (typWiersza>1) ){
                        set_bkg_tiles(3+5*(typWiersza-1),10,4,1,falkaBlank);
                        while (joypad()) {
                            }   
                        typWiersza--;
                    }
                    if ( (joypad() & J_RIGHT) && (typWiersza<3) ){
                        set_bkg_tiles(3+5*(typWiersza-1),10,4,1,falkaBlank);
                        while (joypad()) {
                        }
                        typWiersza++;
                    }
                    break;
            
            case 2: set_bkg_tiles(3+5*(typWiersza-1),10,4,1,falkaOpcje_1);
                    set_bkg_tiles(3+9-7*dzwieki,14,3,1,falkaTMP);
                    
                    if ( (joypad() & J_LEFT) && (dzwieki<1) ){
                        set_bkg_tiles(3+9-7*dzwieki,14,3,1,falkaBlank);
                        while (joypad()) {
                            }   
                        dzwieki++;
                    }
                    if ( (joypad() & J_RIGHT) && (dzwieki>0) ){
                        set_bkg_tiles(3+9-7*dzwieki,14,3,1,falkaBlank);
                        while (joypad()) {
                        }
                        dzwieki--;
                    }
                    break;
                    
        }
        
        if ( (joypad() & J_B) || (joypad() & J_A)  || (joypad() & J_START) || (joypad() & J_SELECT) ) {
            koniec=1;
        }
        if (joypad() & J_DOWN) {
            if (opcja==1) {
                opcja=2;
            }
        }
        if (joypad() & J_UP) {
            if (opcja==2) {
                opcja=1;
            }
            

        }
        
        
        
        
        
    }
    
    
        

}


void autorzy (void) {
    set_bkg_tiles(0,0,20,18,tloWiersza);
    set_bkg_tiles(3,7,10,6,about);
    hide_selected_sprites(0,3);
    delay (200);
    while (!joypad()) {
    }


}

void cierpienie (void) {
    
    UINT8 koniec=0;
    UINT8 animCount=0;
    UINT8 klatka=1;
    UINT8 dklatka=0; // 0 -dodawanie, 1 - odejmowanie
        
    set_bkg_tiles(0,0,20,18,tloWiersza);
    set_bkg_tiles(5,3,10,3,napis_koniecL);
    set_bkg_tiles(5,8,11,3,cierpienieTekst);
    
    set_sprite_tile(0,0);
    set_sprite_tile(1,1);
    set_sprite_tile(2,2);
    move_sprite(0,80,130);
    move_sprite(1,88,130);
    move_sprite(2,96,130);
        
    //delay (200);
    
    while (!koniec) {
        animCount++;
        if (animCount==100) {
            animCount=0;
            if (dklatka==0) {
                klatka++;
            }
            else {
                klatka--;
            } 

            if (klatka==4) {
                klatka=2;
                dklatka=1;
            }
            if (klatka==0) {
                klatka=2;
                dklatka=0;
            }
        
            if (klatka!=2) {
                HIDE_SPRITES;
            }
            else {
                SHOW_SPRITES;
            }
        }

        switch (klatka) {
            case 1: set_bkg_tiles(5,3,10,3,napis_koniecL);
                    break;
            case 2: set_bkg_tiles(5,3,10,3,napis_koniecM);
                    break;
            case 3: set_bkg_tiles(5,3,10,3,napis_koniecP);
                    break;
        }
    
    if (joypad()) {
        koniec=1;
    }
    
    }
    
    
}


void main () {
      
    init();
    titleScreen();
    
    DISPLAY_OFF;
    set_bkg_data(0,255,kafelki);
    DISPLAY_ON; 
    //głowna pętla programu
    
    while (1) {
        
        set_bkg_tiles(0,0,20,18,tloWiersza);
        set_bkg_tiles(7,7,7,7,menu);
        set_bkg_tiles(6,2,10,3,napis_menu);
        set_sprite_tile(0,3);
        hide_selected_sprites(0,8);

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
