# turbo-wieszcz-gameboy
Port of Turbo Wieszcz++ for Gameboy. 
Original idea: https://github.com/monstergdc/TurboWieszcz-Python


You need gbdk-2020 https://github.com/gbdk-2020/gbdk-2020 to compile:
Just write:

{..place where gbdk-2020 is unpacked}gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c


{..place where gbdk-2020 is unpacked}gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o tw_0_6.gb main.o 

For *.gbr and *.gbm files use Gameboy Tile Designer and Gameboy Map Builder by Harry Mulder:

http://www.devrs.com/gb/hmgd/intro.html
