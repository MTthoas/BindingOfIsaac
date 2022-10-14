#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
#define LARGEUR_TILE 24  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 16
 
#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13


 
 
 
void Afficher(SDL_Renderer *renderer,SDL_Texture *texture, SDL_Surface* tileset,int nombre_blocs_largeur,int nombre_blocs_hauteur)
{

    
    int i,j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_dest.w = LARGEUR_TILE;
    Rect_dest.h = HAUTEUR_TILE;
    Rect_source.w = LARGEUR_TILE;
    Rect_source.h = HAUTEUR_TILE;
    texture=SDL_CreateTextureFromSurface(renderer,tileset);

    
    for(i=0;i<nombre_blocs_largeur;i++)
    {
        for(j=0;j<nombre_blocs_hauteur;j++)
        {
            Rect_dest.x = i*LARGEUR_TILE;
            Rect_dest.y = j*HAUTEUR_TILE;
            Rect_source.x = (98-'0')*LARGEUR_TILE;
            Rect_source.y = 0;
            //SDL_QueryTexture(texture,NULL,NULL,&Rect_dest.w,&Rect_dest.h);
            SDL_RenderCopy(renderer, texture, &Rect_source, &Rect_dest);
            //SDL_BlitSurface(tileset,NULL,screen,&Rect_dest);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}
 
int main(int argc,char** argv)
{

    (void)argc;
    (void)argv;

    SDL_Surface *tileset;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
     
        // prepare SDL
        SDL_Window * window = SDL_CreateWindow("Tile",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR,HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR,0);
        SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        SDL_Texture *texture = NULL;
        //screen = SDL_GetWindowSurface(window);
        tileset = IMG_Load("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/ProjectUtumno_full.png");
 
    if (!tileset)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        SDL_Quit();
        system("pause");
        exit(-1);
    }
    Afficher(renderer,texture,tileset,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);
 
    do
    {
        SDL_WaitEvent(&event);
    } while (event.type!=SDL_KEYDOWN);
     
    SDL_FreeSurface(tileset);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}