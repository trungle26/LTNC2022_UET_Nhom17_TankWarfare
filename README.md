 - About the project:  
 	Tank Warfare is a fascinating, two-player shooting game in which the players, 
        each controlling a tank, attempt to shoot each other. This game has a top-down view of the
        tanks and the map; the map comprises of walls and fences, as well as many other subtle 
        elements such as grass, graves, flowers, ..etc.
         									
		When the game begins, both tanks have 10 health points and 10 bullets, every time a tank 
		is struck by the opponent's bullet it loses health. The game continues until one of the two
		tanks have zero health, when the players will have 2 options to restart the game(normal mode
		and reborn mode). In reborn mode, the winner of the previous round becomes the underdog since
		the opponent reborns with double the health and double the bullets.

		Players can heal the tank, reload their ammunitions and enable "Allah mode". Note that once
		switched to "Allah mode" there is no switching back until the end of the game, and each time
		the tank is healing or reloading it cannot be controlled for a short period of time.

		There are 2 ways players can approach the game. They can play in normal mode or they can 
		enable "Allah mode" to do more damage to the opponent but risk losing health as time goes by.
		In "Allah mode" bullets can pass through the wall, so players can choose to hide from opponent
		and shoot from distance. But players need to pay attention to the health of the tank and	
		regenarate tank's health when it's close to zero.
        
This project is named "LTNC2022_UET_Nhom17_TankWarfare" as part of class INT2215 22.

- How to run this project
	+ Create new folder in computer
	+ Open Command Prompt or PowerShell in this folder
	+ Enter these lines
	
                git init
        +
        
                git clone https://github.com/trungle26/LTNC2022_UET_Nhom17_TankWarfare.git
	+ If you use Command Prompt: open Command Prompt in run_from_cmd folder, enter these 2 lines
		
                g++ -Isrc/Include -Lsrc/lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
        +
        
                main
	+ If you use PowerShell: open PowerShell in run_from_cmd folder, enter these 2 lines
		
                g++ -Isrc/Include -Lsrc/lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
        +
        
                ./main.exe

- Contributors:
	
        + Le Duc Trung: early game structure, tank functions, map drawing and rendering, tank collision, game graphics
	
        + Doan Vu Quang Phu: menu making, sound and music handling, linking menu fuctions with game, create makefile file
	
        + Tran Ba Hoang: game modes, ammo and health structure, tank functions, projectiles functions, bullet collision
