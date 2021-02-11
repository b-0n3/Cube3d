#include "cub3d.h"

double  normelize_angel(double angle)
{
	angle = fmod(angle , 2 * M_PI);
	if (angle < 0)
		angle += ((360  * M_PI) / 180); 
	return angle;
}

void free_player(void *item)
{
	t_player *pla;

	pla = (t_player *) item;
	pla->wall_rays.free(&pla->wall_rays, &free_ray);
	pla->sprit_rays.free(&pla->sprit_rays , &free_ray_sp);
	free(pla->pos);
}
