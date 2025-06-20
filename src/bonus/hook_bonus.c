/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:13:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/06/16 16:05:31 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	free_game(game);
	if (game->is_running)
		game->is_running = false;
	if (DEBUG_MODE)
		printf("\nGame closed successfully.\n");
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	bool	pressed;

	game = (t_game *)param;
	pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT);
	if (keydata.key == MLX_KEY_ESCAPE && pressed)
		close_hook(game);
	if (keydata.key == MLX_KEY_W)
		game->keys.w = pressed;
	if (keydata.key == MLX_KEY_S)
		game->keys.s = pressed;
	if (keydata.key == MLX_KEY_A)
		game->keys.a = pressed;
	if (keydata.key == MLX_KEY_D)
		game->keys.d = pressed;
	if (keydata.key == MLX_KEY_E)
		game->keys.e = keydata.action == MLX_PRESS;
}

void	loop_hook(void *param)
{
	t_game	*game;
	t_point	prev_pos;
	double	prev_angle;

	game = (t_game *)param;
	prev_pos.x = game->player.pos.x;
	prev_pos.y = game->player.pos.y;
	prev_angle = game->player.angle;
	update_player_state(game);
	if (game->keys.e)
		key_door(game);
	if (game->player.pos.x != prev_pos.x || game->player.pos.y != prev_pos.y
		|| game->player.angle != prev_angle)
	{
		draw_frame(game);
		prev_pos.x = game->player.pos.x;
		prev_pos.y = game->player.pos.y;
		prev_angle = game->player.angle;
	}
	draw_torch(game);
	if (DEBUG_MODE)
		fps_counter(game);
}

void	fps_counter(t_game *game)
{
	static int		frame_count = 0;
	static double	last_time = 0.0;
	double			current_time;
	double			delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - last_time;
	if (delta_time >= 1.0)
	{
		printf("FPS: %d | ", frame_count);
		printf("P(%f, %f, %f)\n", game->player.pos.x, game->player.pos.y,
			game->player.angle);
		frame_count = 0;
		last_time = current_time;
	}
	frame_count++;
}
