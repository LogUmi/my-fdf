/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:11:55 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/04 21:45:54 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	test_isometric(t_map **map, double new_x, double new_y, t_dmlx *mlx)
{
	t_map	*a;
	double	xz;
	double	yz;

	a = *map;
	while (a)
	{
		xz = a->x * cos(mlx->zangle) - a->y * sin(mlx->zangle);
		yz = a->y * cos(mlx->zangle) + a->x * sin(mlx->zangle);
		new_x = (xz - yz) * cos(mlx->iangle);
		new_y = (xz + yz) * sin(mlx->iangle);
		new_y -= a->z * cos(mlx->iangle) * mlx->zfact;
		if (new_x < mlx->xmin)
			mlx->xmin = new_x;
		if (new_y < mlx->ymin)
			mlx->ymin = new_y;
		if (new_x > mlx->xmax)
			mlx->xmax = new_x;
		if (new_y > mlx->ymax)
			mlx->ymax = new_y;
		a = a->next;
	}
}

void	set_side_down(t_map *a, t_map *b)
{
	if (b->y == a->y)
		a->side = b;
	else
		a->side = NULL;
	b = a;
	a->down = NULL;
	while (b)
	{
		if (a->x == b->x && a->y == (b->y - 1))
		{
			a->down = b;
			b = NULL;
		}
		else
			b = b->next;
	}
}

void	set_map(t_map **map, t_map *a, t_map *b)
{
	a = *map;
	while (a)
	{
		if (a->next != NULL)
		{
			b = a->next;
			set_side_down(a, b);
		}
		else
		{
			a->side = NULL;
			a->down = NULL;
		}
		a = a->next;
	}
}

void	get_magn(t_dmlx *mlx, double dx, double dy)
{
	int		little;
	double	div;

	if (mlx->swidth < mlx->sheight)
		little = mlx->swidth;
	else
		little = mlx->sheight;
	div = (double)little / mlx->maxdiag;
	if (div >= 1)
		mlx->magn = floor(div * 0.9);
	else
		mlx->magn = div - 0.1;
	mlx->height = (mlx->maxdiag * mlx->magn);
	mlx->width = (mlx->maxdiag * mlx->magn);
	mlx->crefx = (((mlx->width - mlx->magn * dx) / 2) - mlx->xmin * mlx->magn);
	mlx->crefy = (((mlx->height - mlx->magn * dy) / 2) - mlx->ymin * mlx->magn);
}

void	size_img(t_dmlx *vars)
{
	double	c[2];

	c[0] = 0;
	c[1] = 0;
	vars->xmin = 0;
	vars->xmax = 0;
	vars->ymin = 0;
	vars->ymax = 0;
	test_isometric(vars->map, 0, 0, vars);
	c[0] = fabs(vars->xmax - vars->xmin);
	c[1] = fabs(vars->ymax - vars->ymin);
	vars->maxdiag = ceil(sqrt(c[0] * c[0] + c[1] * c[1]));
	get_magn(vars, c[0], c[1]);
}
