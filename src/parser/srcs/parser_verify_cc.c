#include "cub3d.h"

#ifdef BONUS

t_bool		check_map_char(char ch)
{
	char *arr;

	arr = "0123456789NWSEs";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

t_bool		check_map_chars(char ch)
{
	char *arr;

	arr = "03456789NSEW";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}
#else

t_bool		check_map_chars(char ch)
{
	char *arr;

	arr = "02NSEW";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}

t_bool		check_map_char(char ch)
{
	char *arr;

	arr = "012NWSE";
	if (ft_strchr(arr, ch) != NULL)
		return (TRUE);
	return (FALSE);
}
#endif
