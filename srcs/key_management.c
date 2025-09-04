/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgerard <lgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:03:37 by lgerard           #+#    #+#             */
/*   Updated: 2025/09/04 21:45:32 by lgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_key_in(int keycode, t_dmlx *mlx)
{
	if (keycode == XK_ESCAPE)
		return (error(mlx, "Regular end of session on esc key press", 0));
	if (keycode == XK_PLUS && mlx->key[0] == 0)
		mlx->key[0] = 1;
	if (keycode == XK_MINUS && mlx->key[1] == 0)
		mlx->key[1] = 1;
	if (keycode == XK_SPACE && mlx->key[2] == 0)
		mlx->key[2] = 1;
	if (keycode == XK_UP && mlx->key[3] == 0)
		mlx->key[3] = 1;
	if (keycode == XK_DOWN && mlx->key[4] == 0)
		mlx->key[4] = 1;
	if (keycode == XK_RIGHT && mlx->key[5] == 0)
		mlx->key[5] = 1;
	if (keycode == XK_LEFT && mlx->key[6] == 0)
		mlx->key[6] = 1;
	if (keycode == XK_KP7 && mlx->key[7] == 0)
		mlx->key[7] = 1;
	if (keycode == XK_KP4 && mlx->key[8] == 0)
		mlx->key[8] = 1;
	if (keycode == XK_KP8 && mlx->key[9] == 0)
		mlx->key[9] = 1;
	if (keycode == XK_KP5 && mlx->key[10] == 0)
		mlx->key[10] = 1;
	if (keycode == XK_KP9 && mlx->key[11] == 0)
		mlx->key[11] = 1;
	if (keycode == XK_KP6 && mlx->key[12] == 0)
		mlx->key[12] = 1;
	if (keycode == XK_KP1 && mlx->key[13] == 0)
		mlx->key[13] = 1;
	if (keycode == XK_KP0 && mlx->key[14] == 0)
		mlx->key[14] = 1;
	return (0);
}

int	ft_key_out(int keycode, t_dmlx *mlx)
{
	if (keycode == XK_PLUS)
		mlx->key[0] = 0;
	if (keycode == XK_MINUS)
		mlx->key[1] = 0;
	if (keycode == XK_SPACE)
		mlx->key[2] = 0;
	if (keycode == XK_UP)
		mlx->key[3] = 0;
	if (keycode == XK_DOWN)
		mlx->key[4] = 0;
	if (keycode == XK_RIGHT)
		mlx->key[5] = 0;
	if (keycode == XK_LEFT)
		mlx->key[6] = 0;
	if (keycode == XK_KP7)
		mlx->key[7] = 0;
	if (keycode == XK_KP4)
		mlx->key[8] = 0;
	if (keycode == XK_KP8)
		mlx->key[9] = 0;
	if (keycode == XK_KP5)
		mlx->key[10] = 0;
	if (keycode == XK_KP9)
		mlx->key[11] = 0;
	if (keycode == XK_KP6)
		mlx->key[12] = 0;
	if (keycode == XK_KP1)
		mlx->key[13] = 0;
	if (keycode == XK_KP0)
		mlx->key[14] = 0;
		
	return (0);
}

void	ft_key_init(t_dmlx *mlx)
{
	mlx->key[0] = 0;
	mlx->key[1] = 0;
	mlx->key[2] = 0;
	mlx->key[3] = 0;
	mlx->key[4] = 0;
	mlx->key[5] = 0;
	mlx->key[6] = 0;
	mlx->key[7] = 0;
	mlx->key[8] = 0;
	mlx->key[9] = 0;
	mlx->key[10] = 0;
	mlx->key[11] = 0;
	mlx->key[12] = 0;
	mlx->key[13] = 0;
	mlx->key[14] = 0;
}

int	ft_hook_loop0(t_dmlx *mlx, int *update)
{
	if (mlx->key[4])
	{
		move_cmds(mlx, 1);
		(*update) = 1;
	}
	if (mlx->key[5])
	{
		move_cmds(mlx, 2);
		(*update = 1);
	}
	if (mlx->key[6])
	{
		move_cmds(mlx, 3);
		(*update = 1);
	}
	if (mlx->key[7])
	{
		angle_change(mlx, 0);
		(*update = 1);
	}
	if (mlx->key[8])
		{
		angle_change(mlx, 1);
		(*update = 1);
	}
	if (mlx->key[9])
	{
		angle_change(mlx, 2);
		(*update = 1);
	}
	if (mlx->key[10])
	{
		angle_change(mlx, 3);
		(*update = 1);
	}
	if (mlx->key[11])
	{
		angle_change(mlx, 4);
		(*update = 1);
	}
	if (mlx->key[12])
	{
		angle_change(mlx, 5);
		(*update = 1);
	}
	if (mlx->key[13])
	{
		angle_change(mlx, 6);
		(*update = 1);
	}
	if (mlx->key[14])
	{
		angle_change(mlx, 7);
		(*update = 1);
	}
	if ((*update))
	{
		fill_img(mlx, 0);
		draw_lines(mlx, mlx->map);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		swap_img(mlx, 1);
	}
	return (0);
}

int	ft_hook_loop(t_dmlx *mlx)
{
	int	update;

	update = 0;
	if (mlx->key[0])
	{
		magn_change(mlx, 0);
		update = 1;
	}
	if (mlx->key[1])
	{
		magn_change(mlx, 1);
		update = 1;
	}
	if (mlx->key[2])
	{
		reset_cmds(mlx);
		update = 1;
	}
	if (mlx->key[3])
	{
		move_cmds(mlx, 0);
		update = 1;
	}
	ft_hook_loop0(mlx, &update);
	return (0);
}
