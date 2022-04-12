/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 10:31:29 by cruiz-de          #+#    #+#             */
/*   Updated: 2022/04/12 20:48:51 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_vars(t_vars *vars)
{
	vars->player.fov = 60;
	vars->player.angle = 0;
	vars->player.x = 0;
	vars->player.y = 0;
	vars->player.rotation = 3;
	vars->keys.w = 0;
	vars->keys.a = 0;
	vars->keys.d = 0;
	vars->keys.s = 0;
	vars->keys.left = 0;
	vars->keys.right = 0;
	vars->map.width = 0;
	vars->north.path = NULL;
	vars->south.path = NULL;
	vars->east.path = NULL;
	vars->west.path = NULL;
	vars->stexture.path = NULL;
	vars->parser.width = 0;
	vars->parser.height = 0;
	vars->map.start = 0;
	vars->screenshot = 0;
	init_colours(vars);
}

void	mlx_hooks(t_vars *vars)
{
	mlx_hook(vars->win, 02, 1L < 0, key_press, vars);
	mlx_hook(vars->win, 03, 1L < 0, key_release, vars);
	mlx_hook(vars->win, 17, 1L < 0, x_close, vars);
	mlx_loop_hook(vars->mlx, raycasting, vars);
	mlx_loop(vars->mlx);
}

void	take_colours(t_vars *vars)
{
	vars->floor = ft_rgbtohex(vars->texture.floor[0],
	vars->texture.floor[1], vars->texture.floor[2]);
	vars->sky = ft_rgbtohex(vars->texture.sky[0],
	vars->texture.sky[1], vars->texture.sky[2]);
}

void	arguments(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		exit_error("Error\nWrong Arguments\n");
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7))
		exit_error("Error\nExpected \"--save\" argument\n");
	if (!ft_strrchr(argv[1], '.'))
		exit_error("Error\nWrong Map");
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
		exit_error("Error\nWrong Map");
}

int		main(int argc, char **argv)
{
	t_vars vars;

	arguments(argc, argv);
	init_vars(&vars);
	vars.mlx = mlx_init();
	read_text(&vars, argv[1]);
	take_colours(&vars);
	vars.data.width = vars.parser.width;
	vars.data.height = vars.parser.height;
	if (argc < 3)
		vars.win = mlx_new_window(vars.mlx,
		vars.parser.width, vars.parser.height, "Cub3D");
	vars.data.img = mlx_new_image(vars.mlx,
	vars.parser.width, vars.parser.height);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
	{
		vars.screenshot = 1;
		ft_screenshot(&vars);
		return (0);
	}
	vars.data.addr = mlx_get_data_addr(vars.data.img,
	&vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);
	sprite_array(&vars);
	start_music(&vars);
	mlx_hooks(&vars);
}
