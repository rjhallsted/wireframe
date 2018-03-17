/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhallste <rhallste@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 22:30:15 by rhallste          #+#    #+#             */
/*   Updated: 2018/03/16 18:45:24 by rhallste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define FDF_WINWIDTH 800
# define FDF_WINHEIGHT 600
# define FDF_POINT_SEP 5
# define FDF_ZMOD 2

typedef struct		s_fdf_point3d
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}					t_fdf_point3d;

typedef struct		s_fdf_point2d
{
	unsigned int	x;
	unsigned int	y;
	unsigned long	color;
}					t_fdf_point2d;

typedef struct		s_fdf_window
{
	unsigned int	width;
	unsigned int	height;
}					t_fdf_window;

typedef struct		s_fdf_matrix
{
	unsigned int	width;
	unsigned int	height;
	t_fdf_point3d	**points3d;
	t_fdf_point2d	**points2d;
}					t_fdf_matrix;

/*
** Parsing
*/
t_fdf_point3d	**fdf_parse_file(int fd, unsigned int *width, unsigned int *height);

/*
** Transformations
*/
t_fdf_point2d	**fdf_iso_proj(t_fdf_point3d **points3d, unsigned int width, unsigned int height);
void			fdf_scale_to_window(t_fdf_point3d **points3d, unsigned long factor, unsigned int width, unsigned int height);
unsigned long	fdf_calc_scale_factor(unsigned int width, unsigned int height);

/*
** Drawing
*/
void			*fdf_draw_line(t_fdf_point2d *p1, t_fdf_point2d *p2,
								void *mlx_ptr, void *win_ptr);

/*
** Errors
*/
void			fdf_usage_error(void);
void			fdf_fileopen_error(char *filename);
void			fdf_shortline_error();

#endif
