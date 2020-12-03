/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 12:16:31 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/12/03 14:16:40 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_int_to_bytes(unsigned char *header, int n)
{
	header[0] = (unsigned char)n;
	header[1] = (unsigned char)(n >> 8);
	header[2] = (unsigned char)(n >> 16);
	header[3] = (unsigned char)(n >> 24);
}

int     ft_screenshot(t_vars *vars)
{
    unsigned    char    header[54];
    int         fd;
    int         i;

    i = 0;
    fd = open("./screenshot.bmp", O_WRONLY | O_CREAT, 0777);
    vars->data.addr = mlx_get_data_addr(vars->data.img,
	&vars->data.bits_per_pixel, &vars->data.line_length, &vars->data.endian);
    sprite_array(vars);
    raycasting(vars);
    ft_bzero(header, 54);
    header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
    ft_int_to_bytes(header + 2, 54 + (3 * vars->parser.width * vars->parser.height) + ((4 - (vars->parser.width * 3) % 4) % 4 * vars->parser.height));
    header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
    ft_int_to_bytes(header + 18, vars->parser.width);
	ft_int_to_bytes(header + 22, vars->parser.height);
    header[26] = (unsigned char)1;
    header[26] = (unsigned char)1;
    write(fd, header, 54);
    i = vars->parser.width * vars->parser.height - 1;
	while (i > 0)
	{
		write(fd, &vars->data.addr[i], 3);
		i--;
	}
}
