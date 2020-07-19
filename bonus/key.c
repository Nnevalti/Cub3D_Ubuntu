/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:50:22 by vdescham          #+#    #+#             */
/*   Updated: 2020/03/02 17:50:24 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

int		key_pressed(int key, t_data *data)
{
	if (key == 65307)
		exit_game(data);
	else if (key == 122)
		data->key.up = true;
	else if (key == 115)
		data->key.down = true;
	else if (key == 65363)
		data->key.r_right = true;
	else if (key == 65361)
		data->key.r_left = true;
	else if (key == 113)
		data->key.left = true;
	else if (key == 100)
		data->key.right = true;
	else if (key == 65505)
		data->player.move_speed = 0.08;
	else if (key == 99)
		bmp_create(data, "screenshot_c.bmp");
	else if (key == 101 && data->player.is_shooting == false)
	{
		data->key.shoot = true;
		system("ffplay Musics/gun.mp3 -nodisp -loglevel quiet & ffplay Musics/reload.mp3 -v 4 -nodisp -loglevel quiet &");
		shoot(data);
	}
	return (0);
}

int		key_released(int key, t_data *data)
{
	if (key == 122)
		data->key.up = false;
	else if (key == 115)
		data->key.down = false;
	else if (key == 65363)
		data->key.r_right = false;
	else if (key == 65361)
		data->key.r_left = false;
	else if (key == 113)
		data->key.left = false;
	else if (key == 100)
		data->key.right = false;
	else if (key == 65505)
		data->player.move_speed = 0.05;
	else if (key == 101)
		data->key.shoot = false;
	return (0);
}
