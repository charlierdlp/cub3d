/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:03:15 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/07 12:49:07 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ch_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char *dst;

    //recorrer el string de datos en forma de array
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color)
{
    int x;
    int y;
    int dx;
    int dy;
    int steps;
    float xinc;
    float yinc;
    int i;

    i = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    xinc = dx / (float)steps;
    yinc = dy / (float)steps;
    x = x0;
    y = y0;
    while (i <= steps)
    {
        ch_mlx_pixel_put(data, x, y, color);
        x += xinc;
        y += yinc;
        i++;
    }
}

int raycasting(t_vars *vars)
{
    float raycos;
    float raysin;
    float rayangle;
        
    rayangle = vars->player.angle - vars->player.fov/2;

    vars->raycount = 0;
    while (vars->raycount < SCREEN_WIDTH) //bucle para recorrer la pantalla y ver la posicion
    {
        vars->x = vars->player.x;
        vars->y = vars->player.y;

        //degreetoradians = * M_PI / 180;

        raycos = cos(rayangle * M_PI / 180) / 128;
        raysin = sin(rayangle * M_PI / 180) / 128;

        //wall check
        vars->walls.wall = 0;
        while (vars->walls.wall == 0)
        {
            vars->x += raycos;
            if (map[(int)vars->y][(int)vars->x] == 1)
            {
                vars->dir = raycos < 0 ? 'W' : 'E';
                if(vars->dir == 'W')
                    vars->texture = vars->west;
                else
                    vars->texture = vars->east;
                break ;
            }
            vars->y += raysin;
            if (map[(int)vars->y][(int)vars->x] == 1)
            {
                vars->dir = raysin < 0 ? 'N' : 'S';
                if(vars->dir == 'N')
                    vars->texture = vars->north;
                else
                    vars->texture = vars->south;
            }
            vars->walls.wall = map[(int)vars->y][(int)vars->x];
        }

        //pythagoras
        vars->walls.distance = sqrt(pow(vars->player.x - vars->x, 2) + pow(vars->player.y - vars->y, 2));
        //fish eye fix
        vars->walls.distance = vars->walls.distance * cos((rayangle - vars->player.angle) * M_PI / 180);
        //wall height
        vars->walls.height = (int)((SCREEN_HEIGHT/2) / vars->walls.distance);
        //texture position
        vars->texture.texturepositionx = floor(fmod( vars->texture.width * (vars->x + vars->y), vars->texture.width)); //texturewidth = 8

        //print_screen
        dda_algorithm(&vars->data, vars->raycount, 0, vars->raycount, SCREEN_HEIGHT / 2 - vars->walls.height, 0x00A1DD);
        //dda_algorithm(&vars->data, vars->raycount, SCREEN_HEIGHT / 2 - vars->walls.height, vars->raycount, SCREEN_HEIGHT/2 + vars->walls.height, 0xBB0000);
        drawtexture(vars, vars->raycount);
        dda_algorithm(&vars->data, vars->raycount, SCREEN_HEIGHT / 2 + vars->walls.height, vars->raycount, SCREEN_HEIGHT, 0xA0A0A0);

        //incrementangle = Player FOV / Screen width;
        rayangle += vars->player.fov/SCREEN_WIDTH;
        vars->raycount++;
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);        
    return(0);
}

