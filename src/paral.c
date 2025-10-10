/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paral.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@studnet.42kl.edu.fr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:22:13 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/03 15:22:49 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../headers/fdf.h"

int	key_press2(int keycode, t_vars *vars)
{
	if (keycode == '1')
		set_top_view(vars);
	else if (keycode == '2')
		set_front_view(vars);
	else if (keycode == '3')
		set_side_view(vars);
	else if (keycode == '4')
		set_isometric_view(vars);
	else
		return (0);
	return (1);
}

void	set_top_view(t_vars *vars)
{
	vars->view = TOP_VIEW;
	vars->cam.rotation_x = 0;
	vars->cam.rotation_y = 0;
	vars->cam.rotation_z = 0;
	vars->cam.angle = 0;
}

void	set_front_view(t_vars *vars)
{
	vars->view = FRONT_VIEW;
	vars->cam.rotation_x = -M_PI_2;
	vars->cam.rotation_y = 0;
	vars->cam.rotation_z = 0;
	vars->cam.angle = 0;
}

void	set_side_view(t_vars *vars)
{
	vars->view = SIDE_VIEW;
	vars->cam.rotation_x = -M_PI_2;
	vars->cam.rotation_y = M_PI_2;
	vars->cam.rotation_z = 0;
	vars->cam.angle = 0;
}

void	set_isometric_view(t_vars *vars)
{
	vars->view = ISO_VIEW;
	reset_camera(vars);
}
