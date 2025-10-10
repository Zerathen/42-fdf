/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:18:40 by jenlee            #+#    #+#             */
/*   Updated: 2025/08/14 10:41:15 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	mouse_handler(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 4)
		vars->cam.zoom *= 1.1;
	else if (button == 5)
		vars->cam.zoom /= 1.1;
	mlx_clear_window(vars->mlx, vars->window);
	render_map(vars, -1);
	return (0);
}

int	close_window(void *param)
{
	cleanup_and_exit((t_vars *)param);
	return (0);
}

double	calculate_initial_zoom(t_map *map, int win_w, int win_h)
{
	double	margin;
	double	zoom_x;
	double	zoom_y;

	margin = 0.8;
	zoom_x = (win_w * margin) / map->width;
	zoom_y = (win_h * margin) / map->height;
	if (zoom_x < zoom_y)
		return (zoom_x / TILE_SIZE);
	else
		return (zoom_y / TILE_SIZE);
}

void	cleanup_and_exit(t_vars *vars)
{
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->window)
		mlx_destroy_window(vars->mlx, vars->window);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->map)
		free_map(vars->map);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (ft_putstr("Usage: ./fdf <map>\n"), 1);
	vars.map = parse_map(open_file(argv[1]));
	if (!vars.map)
		return (ft_putstr("Error parsing, opening or not found\n"), 1);
	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FdF");
	reset_camera(&vars);
	init_image(&vars);
	render_map(&vars, -1);
	mlx_key_hook(vars.window, loop_handler, &vars);
	mlx_hook(vars.window, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.window, 3, 1L << 1, key_release, &vars);
	mlx_mouse_hook(vars.window, mouse_handler, &vars);
	mlx_hook(vars.window, 4, 1L << 2, mouse_press, &vars);
	mlx_hook(vars.window, 5, 1L << 3, mouse_release, &vars);
	mlx_hook(vars.window, 6, 1L << 6, mouse_move, &vars);
	mlx_hook(vars.window, 17, 0, close_window, &vars);
	mlx_loop_hook(vars.mlx, loop_handler, &vars);
	mlx_loop(vars.mlx);
	cleanup_and_exit(&vars);
	return (0);
}
