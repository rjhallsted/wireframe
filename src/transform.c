/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhallste <rhallste@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:15:30 by rhallste          #+#    #+#             */
/*   Updated: 2018/03/17 04:08:41 by rhallste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "../libft/inc/libft.h"
#include "../inc/fdf.h"

static t_fdf_point2d	calc_proj(t_fdf_point3d point3d)
{
	t_fdf_point2d	proj;
	static double	sqrt3;
	static double	sqrt6;
	double			tmp;
	
	if (!sqrt3)
	{
		sqrt3 = sqrt(3);
		sqrt6 = sqrt(6);
	}
	tmp = ((point3d.x * sqrt3) - (point3d.z * sqrt3)) / sqrt6;
	proj.x = (unsigned int)ceil(tmp);
	tmp = (point3d.x + (2 * point3d.y) + point3d.z) / sqrt6;
	proj.y = (unsigned int)ceil(tmp);
	proj.color = 0xffffff;
	return (proj);
}

t_fdf_point2d	**fdf_iso_proj(t_fdf_point3d **points3d, unsigned int width, unsigned int height)
{
	t_fdf_point2d	**points2d;
	unsigned int	w;
	unsigned int	h;
	
	if(!(points2d = ft_memalloc(sizeof(t_fdf_point2d *) * height)))
		return (NULL);
	h = 0;
	while (h < height)
	{
		if (!(points2d[h] = ft_memalloc(sizeof(t_fdf_point2d) * width)))
			return (NULL);
		w = 0;
		while (w < width)
		{
			points2d[h][w] = calc_proj(points3d[h][w]);
			w++;
		}
		h++;
	}
	return (points2d);
}

double	fdf_calc_scale_factor(unsigned int width, unsigned int height)
{
	double ideal;
	double ideal_height;

	width *= FDF_POINT_SEP;
	height *= FDF_POINT_SEP;
	ideal = ((double)FDF_WINWIDTH / 1.5) / (double)width;
	ideal_height= (double)FDF_WINHEIGHT / 1.2;
	if (height * ideal > ideal_height)
		ideal *= (ideal_height / (height * ideal));
	return (ideal);
}

void			fdf_scale_to_window(t_fdf_point3d **points3d, double factor, unsigned int width, unsigned height)
{
	unsigned int w;	
	unsigned int h;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			points3d[h][w].x = points3d[h][w].x * factor;
			points3d[h][w].y = points3d[h][w].y * factor;
			points3d[h][w].z = points3d[h][w].z * factor;
			w++;
		}
		h++;
	}
}
