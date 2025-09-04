/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:30:37 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/04 21:44:37 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	set_isometric(t_dmlx *m, t_map *a, t_map *b, t_line *l)
{
	double	xz;
	double	yz;
	double 	xy;
	double 	zy;
	double	xx;
	double	yy;

	xz = a->x * cos(m->zangle + m->az) - a->y * sin(m->zangle + m->az);
	yz = a->y * cos(m->zangle + m->az) + a->x * sin(m->zangle + m->az);
	zy = a->z * cos(m->yangle + m->ay) - xz * sin(m->yangle + m->ay);
	xy = xz * cos(m->yangle + m->ay) + a->z * sin(m->yangle + m->ay);
	xx = (xy - yz) * cos (m->iangle + m->ax);
	yy = (xy + yz) * sin (m->iangle + m->ax) - zy * cos(m->iangle + m->ax) * (m->zfact *m->pzf);
	l->x1 = xx * m->magn * m->pm + m->crefx + m->px;
	l->y1 = yy * m->magn * m->pm + m->crefy + m->py;
	xz = b->x * cos(m->zangle + m->az) - b->y * sin(m->zangle + m->az);
	yz = b->y * cos(m->zangle + m->az) + b->x * sin(m->zangle + m->az);
	zy = b->z * cos(m->yangle + m->ay) - xz * sin(m->yangle + m->ay);
	xy = xz * cos(m->yangle + m->ay) + b->z * sin(m->yangle + m->ay);
	xx = (xy - yz) * cos (m->iangle + m->ax);
	yy = (xy + yz) * sin (m->iangle+ m->ax) - zy * cos(m->iangle + m->ax) * (m->zfact * m->pzf);
	l->x2 = xx * m->magn * m->pm + m->crefx + m->px;
	l->y2 = yy * m->magn * m->pm + m->crefy + m->py;
	return (cpy_line(m, a, b, l));
}

int	cpy_line(t_dmlx *mlx, t_map *a, t_map *b, t_line *l)
{
	if (a->color != b->color && a->z == 0 && mlx->c42 != 0)
		l->c1 = mlx->optdefcol;
	else
		l->c1 = a->color;
	if (b->color != a->color && b->z == 0 && mlx->c42 != 0)
		l->c2 = mlx->optdefcol;
	else
		l->c2 = b->color;
	if (abs(l->x2 - l->x1) > abs(l->y2 - l->y1))
		l->npoint = abs(l->x2 - l->x1) + 1;
	else
		l->npoint = abs(l->y2 - l->y1) + 1;
	l->num = 0;
	return (on_screen(mlx, l));
}

void	put_pixel(t_dmlx *mlx, t_line *l)
{
	char				*dst;
	unsigned long long	ofst;
	unsigned int		color;

	ofst = (unsigned long long)(l->y1 * mlx->llen + (l->x1 * (mlx->bpp / 8)));
	color = intercolor(l->c1, l->c2, (double)l->num / (double)l->npoint);
	l->num++;
	if (l->x1 < 0 || l->y1 < 0 || l->x1 >= mlx->width || l->y1 >= mlx->height)
		return ;
	dst = mlx->addr + ofst;
	*(unsigned int *)dst = color;
}

void	draw_line(t_dmlx *mlx, t_line *l)
{
	int	dl[6];

	dl[0] = abs(l->x2 - l->x1);
	dl[1] = abs(l->y2 - l->y1);
	dl[2] = direction (l->x1, l->x2);
	dl[3] = direction(l->y1, l->y2);
	dl[4] = dl[0] - dl[1];
	dl[5] = 2 * dl[4];
	while (l->x1 != l->x2 || l->y1 != l->y2)
	{
		put_pixel(mlx, l);
		if (dl[5] > -dl[1])
		{
			dl[4] -= dl[1];
			l->x1 += dl[2];
		}
		if (dl[5] < dl[0])
		{
			dl[4] += dl[0];
			l->y1 += dl[3];
		}
		dl[5] = 2 * dl[4];
	}
}

void	draw_lines(t_dmlx *mlx, t_map **map)
{
	t_map	*a;
	t_line	line;

	a = *map;
	while (a)
	{
		if (a->side != 0)
		{
			if (set_isometric(mlx, a, (t_map *)a->side, &line) != 0)
				draw_line(mlx, &line);
		}
		if (a->down != NULL)
		{
			if (set_isometric(mlx, a, (t_map *)a->down, &line) != 0)
				draw_line(mlx, &line);
		}
		a = a->next;
	}
}

/* draw line
dl[0] = distance_x = abs(b.x - a.x)
dl[1] = distance_y = abs(b.y - a.y)
dl[2] = direction_x = 1 if (a.x < b.x) else -1
dl[3] = direction_y = 1 if (a.y < b.y) else -1
dl[4] = gap = distance_x - distance_y;
dl[5] = indicateur de changement d'axe = 2 * gap
*/