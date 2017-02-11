// misc.cpp
//

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mouse.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(a, b) _mkdir(a)
#else /* _WIN32 */
#include <sys/stat.h>
#endif /*! _WIN32 */

#include "misc.h"
#include "blupi.h"
#include "def.h"

// Variables globales

extern bool		g_bFullScreen;	// false si mode de test
extern int		g_mouseType;


// Affiche un message de debug.

void OutputDebug(const char *pMessage)
{
	SDL_LogDebug (SDL_LOG_CATEGORY_APPLICATION, "%s", pMessage);
}

// Conversion de la position de la souris.

POINT ConvLongToPos(LPARAM lParam)
{
	POINT	pos;

	pos.x = LOWORD(lParam);  // horizontal position of cursor
	pos.y = HIWORD(lParam);  // vertical position of cursor

//	if ( !g_bFullScreen )
//	{
//		pos.y -= GetSystemMetrics(SM_CYCAPTION);
//	}

	return pos;
}


// R�initialise le g�n�rateur al�atoire.

void InitRandom()
{
	srand(1);
}

// Retourne un nombre al�atoire compris entre
// deux bornes (inclues).

int Random(int min, int max)
{
	long	n;

	n = rand();
	n = min+(n%(max-min+1));

	return (int)n;
}


// Retourne le nom de dossier en cours.

std::string GetBaseDir ()
{
	static std::string basePath;

	if (!basePath.size ())
	{
		auto sdlBasePath = SDL_GetBasePath ();
		sdlBasePath[strlen (sdlBasePath) - 1] = '\0';
		basePath = sdlBasePath;
		std::replace (basePath.begin (), basePath.end (), '\\', '/');
		basePath = basePath.substr (0, basePath.find_last_of ("//") + 1);
		SDL_free (sdlBasePath);
	}

	return basePath;
}

// Ajoute le chemin permettant de lire un fichier
// utilisateur.

void AddUserPath(char *pFilename)
{
	char					*temp;
	char*					pText;
	size_t					pos;
	char					last;

	temp = SDL_GetPrefPath ("Epsitec SA", "Planet Blupi");

	pText = strstr(pFilename, "/");
	if ( pText != nullptr )
	{
		pos = strlen(temp)+(pText-pFilename)+1;
		strcat(temp, pFilename);
		last = temp[pos];
		temp[pos] = 0;
		mkdir (temp, 755);
		temp[pos] = last;
	}
	else
	{
		strcat(temp, pFilename);
	}

	strcpy(pFilename, temp);
	SDL_free (temp);
}
