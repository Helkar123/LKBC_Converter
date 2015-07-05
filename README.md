# LKBC_Converter
World of Warcraft M2 model converter from version 08 (_Wrath of the Lich King_) to 07-04 (_The Burning Crusade_).
Written in ANSI C, documented with Doxygen, tested with CuTest, made with love and tears.

##What's yet to be implemented :
* Texture Animations (like flowing lava) 
* Lights (lamps, torchs..)
* Ribbons (trails like Al'ar)
* Particles (Spells, glowing effects..)
	
This is still heavy work in progress.
  
  
##Frequently Asked Questions :
###Can we convert Warlords of Draenor character models ?
Not yet. I don't know if we'll ever be able to. It would be the pinnacle of this project.
Since 0.3, the converter often won't crash when converting them. But they are... twisted.

###Can we use it on creatures or only with static objects ?
This converted is aimed at converting creatures, something that had never been done previously by any LKBC conversion tool.
Not all of them are working perfectly, but the code is getting better every day.

###My model is not working !
In most cases, you're just using a model which has unsupported features, like particles or lights. 
But errors can happen elsewhere too. Report your problem in the issue section ;) !
Don't forget to add the name of your model and the nature of the problem.
  
  
##Credits :
Original idea and structures by Stan84.
Thanks to Stan84, PhilipTNG, Schlumpf and all the people who contributed to M2&M2/WotLK pages on the WoWDev wiki.
Thanks to OneSadCookie for its https://github.com/OneSadCookie/fcaseopen

If you want to contribute and have pure C (I don't want a line of C++ in this program !) knowledge, feel free to send me a message. ;)
