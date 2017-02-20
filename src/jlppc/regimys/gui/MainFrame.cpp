#include "MainFrame.hpp"
#include <iostream>
#include "../start/main.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstring>
#include "../start/StringKeys.hpp"
#include "../start/main.hpp"

#define rLog rlog
#define charLineDialog 33
#define kget StringKeys::get
#define QUIT case SDL_QUIT:return;
#define ECHAP case SDLK_ESCAPE:return;
#define JOYQUIT case 7:return;
using namespace std;


namespace MainFrame {
	SDL_Window *frame = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event events;
	TTF_Font *font = NULL;
	SDL_Rect dialogP = {0, 0, 0, 0};
	SDL_Texture *dialogT = NULL;
	SDL_Rect textPlace = {0, 0, 0, 0};
	SDL_Color noir = {0, 0, 0};
	SDL_Joystick *manette = NULL;
	bool init = false;

	int printText(SDL_Renderer *renderer, string txt, string line2S, string line3S) {
		SDL_Texture *textUre = NULL;
		SDL_Surface *sfce = NULL;
		SDL_Texture *line2 = NULL;
		SDL_Surface *sfce2 = NULL;
		SDL_Texture *line3 = NULL;
		SDL_Surface *sfce3 = NULL;
		SDL_Rect posLineTwo;
		SDL_Rect posLineThree;



		sfce = TTF_RenderText_Blended(font, txt.c_str(), noir);
		textPlace.h = sfce->h;
		textPlace.w = sfce->w;
		textUre = SDL_CreateTextureFromSurface(renderer, sfce);


		sfce2 = TTF_RenderText_Blended(font, line2S.c_str(), noir);
		posLineTwo.h = sfce2->h;
		posLineTwo.w = sfce2->w;
		posLineTwo.x = textPlace.x;
		posLineTwo.y = textPlace.y + 32;
		line2 = SDL_CreateTextureFromSurface(renderer, sfce2);

		sfce3 = TTF_RenderText_Blended(font, line3S.c_str(), noir);
		posLineThree.h = sfce3->h;
		posLineThree.w = sfce3->w;
		posLineThree.x = textPlace.x;
		posLineThree.y = textPlace.y + 32 + 32;
		line3 = SDL_CreateTextureFromSurface(renderer, sfce3);

        SDL_RenderCopy(renderer, line3, NULL, &posLineThree);
		SDL_RenderCopy(renderer, line2, NULL, &posLineTwo);
		SDL_RenderCopy(renderer, textUre, NULL, &textPlace);
		SDL_DestroyTexture(line3);
		SDL_DestroyTexture(textUre);
		SDL_DestroyTexture(line2);
		SDL_FreeSurface(sfce);
		SDL_FreeSurface(sfce2);
		SDL_FreeSurface(sfce3);
		return 0;
	}

	void open() {
        //Initialisations
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == -1) {
			rerrLog << "Erreur d'initialisation de SDL." << endl;
			rlog << "Une erreur fatale s'est produite. Merci de consulter errLog.txt" << endl;
			gererErreur(SDL_GetError(), true);
		}

		if (IMG_Init(IMG_INIT_PNG) < 0) {
			rerrLog << "Erreur d'initialisation de SDL_Image" << endl;
			rlog << "Une erreur fatale s'est produite. Merci de consulter errLog.txt" << endl;
			gererErreur(IMG_GetError(), true);

		}

		if (TTF_Init() == -1) {
			rerrLog << "Erreur d'initialisation de SDL_ttf" << endl;
			rlog << "Une erreur fatale s'est produite. Merci de consulter errLog.txt" << endl;
			gererErreur(TTF_GetError(), true);
		}
        //Ouverture de la police
#ifdef WINDOWS
		font = TTF_OpenFont("ressources\\fonts\\arial.ttf", 32);
#else
		font = TTF_OpenFont("ressources/fonts/arial.ttf", 28);
#endif

		if (font == NULL) {
			rerrLog << "Erreur d'initialisation de la police d'�criture." << endl;
			rlog << "Une erreur fatale s'est produite. Merci de consulter errLog.txt" << endl;
			gererErreur(TTF_GetError(), true);
		}


		//Annonce que l'initialisation principale est termin�e
		init = true;
		//Ouverture de la fenetre
		frame = SDL_CreateWindow("Pokemon Regimys", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN);
        //Cr�ation du renderer.
		renderer = SDL_CreateRenderer(frame, -1, SDL_RENDERER_ACCELERATED);
		if (frame == NULL || renderer == NULL) {
			rerrLog << "Erreur d'ouverture de la fenetre ou du renderer." << endl;
			rlog << "Une erreur fatale s'est produite. Merci de consulter errLog.txt" << endl;
			gererErreur(SDL_GetError(), true);
		}
		//Ouverture de la manette (Je sais pas si ca se dit "ouverture de la manette mais c'est pas grave)
		manette = SDL_JoystickOpen(0);
		if(manette == NULL){
            gererErreur("Aucune manette d�tect�e", false);
		}

		loop();

        SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(frame);
		SDL_JoystickClose(manette);
		TTF_CloseFont(font);

		TTF_Quit();
		atexit(IMG_Quit);
		SDL_Quit();
	}

	void loop(){
	    //D�claration des SDL_Rect et des SDL_Texture secondaires, necessaires a cette scene
		SDL_Rect fondP;
		SDL_Rect profP;
		SDL_Texture *fondT;
		SDL_Texture *profT;
        SDL_Texture *arrDial;
        SDL_Rect arrDialP;

        //Initialisation des tailles
		rlog << "[T = " << time(NULL) - Main::startTime << "] - Initialisation des SDL_Rect" << endl;
		fondP.h = 512;
		fondP.w = 512;
		fondP.x = 0;
		fondP.y = 0;
		dialogP.h = 150;
		dialogP.w = 512;
		dialogP.x = 0;
		dialogP.y = 362;
		profP.h = (300 / 3) * 2;
		profP.w = (180 / 3) * 2;
		profP.x = (fondP.w / 2) - (profP.w / 2) + 10;
		profP.y = ((fondP.h - dialogP.h) / 2) - (profP.h / 2) + 50;
		textPlace.x = 15;
		textPlace.y = 372;
        arrDialP.x = 512 - 75;
        arrDialP.y = 512 - 30;
        arrDialP.h = 10;
        arrDialP.w = 10;
		noir.r = 0;
		noir.g = 0;
		noir.b = 0;
		//Initialisation des images
		rlog << "[T = " << time(NULL) - Main::startTime << "] - Initialisation des sprites..." << endl;
#ifdef WINDOWS
		fondT = IMG_LoadTexture(renderer, "ressources\\backgrounds\\start\\startscene.png");
		profT = IMG_LoadTexture(renderer, "ressources\\sprites\\chara\\jlppc\\jlppc.png");
		dialogT = IMG_LoadTexture(renderer, "ressources\\backgrounds\\dialog\\dialog.png");
		arrDial = IMG_LoadTexture(renderer, "ressources\\sprites\\misc\\arrDial.png");
#else
		fondT = IMG_LoadTexture(renderer, "ressources/backgrounds/start/startscene.png");
		profT = IMG_LoadTexture(renderer, "ressources/sprites/chara/jlppc/jlppc.png");
		dialogT = IMG_LoadTexture(renderer, "ressources/backgrounds/dialog/dialog.png");
		arrDial = IMG_LoadTexture(renderer, "ressources/sprites/misc/arrDial.png");
#endif
        //Vesrification des probl�mes possibles
		if (fondT == NULL || profT == NULL || dialogT == NULL) {
			gererErreur(string("Erreur lors de l'initialisation d'une image.") + string(SDL_GetError()), false);
		}

		if (SDL_RenderCopy(renderer, fondT, NULL, &fondP) == -1) {
			rerrLog << "Erreur lors de l'affichage d'un �l�ment" << endl;
			gererErreur(SDL_GetError(), false);
		}
		if (SDL_RenderCopy(renderer, profT, NULL, &profP) == -1) {
			rerrLog << "Erreur lors de l'affichage d'un �l�ment" << endl;
		}
		if (SDL_RenderCopy(renderer, dialogT, NULL, &dialogP) == -1) {
			rerrLog << "Erreur lors de l'affichage d'un �l�ment" << endl;
		}
		//Initialisation des variables utiles pour la boucle
		SDL_RenderPresent(renderer);
		rlog << "[T = " << time(NULL) - Main::startTime << "] - Fin des initialisations" << endl;
		rlog << "[T = " << time(NULL) - Main::startTime << "] - Creation des variables utilitaires" << endl;
		bool continuer = true;
		long ancientTick = 0;
		//Phase 0
		string txtP0[] = {kget("jlppc.dialog.start.1"), kget("jlppc.dialog.start.2"), kget("jlppc.dialog.start.3"), kget("jlppc.dialog.start.4"), kget("jlppc.dialog.start.5"), kget("jlppc.dialog.start.6"), kget("jlppc.dialog.start.7"), kget("jlppc.dialog.start.8"), " "};//Deux cases == Deux lignes. 3 cases == Deux lignes + un nouveau dialogue
		//Phase 1
		//TODO
		int sizeOfTxt = 9;
		string txtEnCours[] = {string(" "), string(" "), string(" ")};
		SDL_Texture *textUre = NULL;
		SDL_Surface *sfce = NULL;
		int line = 0, i = 0, dialog = 0;
		bool changeDialog = false;
		int phase = 0;
		bool joypressed = false;

		rlog << "[T = " << time(NULL) - Main::startTime << "] - D�but de la boucle principale." << endl;
        //Boucle n�1
		while (continuer) {
			if ((SDL_GetTicks() - ancientTick) >= 50) {

				ancientTick = SDL_GetTicks();

                if(phase == 0){
                    SDL_PollEvent(&events);
                }else{
                    SDL_WaitEvent(&events);
                }

				switch (events.type) {

                    QUIT

					case SDL_KEYDOWN:
						switch (events.key.keysym.sym) {
							case SDLK_SPACE:
								if (changeDialog == false) {
									printText(renderer, txtP0[dialog], txtP0[dialog + 1], txtP0[dialog + 2]);
									line = 0;
									dialog++;
									dialog++;
									dialog++;
									i = 0;
									changeDialog = true;
									SDL_Delay(50);
								} else if (dialog != sizeOfTxt) {
								    txtEnCours[0] = string(" ");
                                    txtEnCours[1] = string(" ");
                                    txtEnCours[2] = string(" ");
									changeDialog = false;
								}else{
									    phase = 1;
                                }

								break;

								ECHAP
						}
						break;

					case SDL_JOYBUTTONDOWN:
						if (!joypressed) {
                            joypressed = true;
							switch (events.jbutton.button) {

								case 0:

									if (changeDialog == false) {
										printText(renderer, txtP0[dialog], txtP0[dialog + 1], txtP0[dialog + 2]);

										line = 0;
										dialog++;
										dialog++;
										dialog++;
										i = 0;
										changeDialog = true;
										SDL_Delay(50);
									} else if (dialog != sizeOfTxt) {
									    txtEnCours[0] = string(" ");
                                        txtEnCours[1] = string(" ");
                                        txtEnCours[2] = string(" ");
										changeDialog = false;
									}else{
									    phase = 1;
									}
									break;

                                JOYQUIT
							}
						}
                        break;

					/*case SDL_WINDOWEVENT:
						switch (events.window.event) {
							case SDL_WINDOWEVENT_RESIZED:
								break;
						}
						break;*/
				}


				if (phase == 0) {
                    SDL_RenderCopy(renderer, dialogT, NULL, &dialogP);
					if (!changeDialog) {

						if (!(i >= txtP0[line + dialog].size())) {

                            if(txtEnCours[line] == " "){
                                txtEnCours[line] = txtP0[line + dialog].c_str()[i];
                            }else{
                                txtEnCours[line] += txtP0[line + dialog].c_str()[i];
                            }


							i++;
						} else {
							if (line == 2) {

								line = 0;
								dialog++;
								dialog++;
								dialog++;
								i = 0;
								if(dialog == sizeOfTxt){
                                    phase = 1;
								}
								changeDialog = true;
							} else {
								line++;
								i = 0;
							}
						}



					}
					printText(renderer, txtEnCours[0], txtEnCours[1], txtEnCours[2]);
                    arrDialP.y = arrDialP.y + 1;
                    if(arrDialP.y - (512 - 30) > 5){
                        arrDialP.y = arrDialP.y - 6;
                    }
                    SDL_RenderCopy(renderer, arrDial, NULL, &arrDialP);
					SDL_RenderPresent(renderer);
				}else{
				    SDL_RenderPresent(renderer);
				    break;
				}




			} else {
				SDL_Delay(50 - (SDL_GetTicks() - ancientTick));
			}

		}

		rlog << "[T = " << time(NULL) - Main::startTime << "] - Fin de la boucle n�0" << endl;
        //rlog << "[T = " << time(NULL) - Main::startTime << "] - Entr�e dans la boucle n�1" << endl;


		SDL_DestroyTexture(textUre);
		SDL_DestroyTexture(dialogT);
		SDL_DestroyTexture(profT);
		SDL_DestroyTexture(fondT);
	}


}