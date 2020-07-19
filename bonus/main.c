/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:48:05 by vdescham          #+#    #+#             */
/*   Updated: 2020/03/02 17:50:29 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cub3D.h"

void	gg(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, data->win.width / 2,
		data->win.height / 2, 0xCCCC00, "GG EZ BROOOO");
	if (data->omg == false)
	{
		data->omg = true;
		system("ffplay Musics/OMG.mp3 -nodisp -loglevel quiet &");
	}
}

void	gameover(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, data->win.width / 2,
		data->win.height / 2, 0xFF0000, "GET REKT");
	if (data->gameover == false)
	{
		system("ffplay Musics/oof.mp3 -r 0.1 -nodisp -loglevel quiet & ffplay ./Musics/nope.mp3 -nodisp -loglevel quiet &");
		system("ffplay Musics/gameover.mp3 -v 3 -nodisp -loglevel quiet &");
		data->gameover = true;
	}
}

int		game(t_data *data)
{
	if (data->player.life < 0 || data->timer > 98)
		gameover(data);
	else if (data->success)
		gg(data);
	else if (move_player(data) && data->player.life >= 0
	&& !data->success && data->timer < 99)
	{
		raycast(data);
		draw_timer(data, true);
	}
	if (data->timer < 98)
		draw_timer(data, false);
	return (0);
}

int		main(int ac, char **av)
{
	t_data		data;

	data = init_data(ac, av);
	raycast(&data);
	if (av[2] && !(ft_strcmp((av[2]), "--save")))
	{
		bmp_create(&data, "screenshots/screenshot.bmp");
		exit_game(&data);
	}
	else if (av[2])
	{
		error_msg(&data,
			"Second argument is invalid : should be --save or none", false);
	}
	system("ffplay ./Musics/undertale-megalovania.mp3 -nodisp -loglevel quiet &");
	data.t1 = time(NULL);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_pressed, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_released, &data);
	mlx_loop_hook(data.mlx_ptr, game, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
