/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:08:21 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/09/01 13:07:55 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./minilibx/mlx.h"
#define WIDTH 10
#define HEIGHT 10

typedef struct  s_vars {
        void    *mlx;
        void    *win;
        int      x;
        int      y;
       // t_player    player;
}               t_vars;

int map [WIDTH][HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,5,0,0,0,0,0,0,1},
    {1,0,0,1,1,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
}; 

void print_big(t_vars vars, int x, int y)
{
 	int i;
	int j;
    unsigned int color;

    if(x == vars.x * 40 && y == vars.y * 40)
        color = 0xffffff;
    else
        color = 0x0000ff;
    
    printf("x: %d, y: %d\npx: %d py: %d\n", x, y, vars.x * 40, 40 * vars.y);
    
    i = 0;
	while (i <= 40)
	{
		j = 0;
		while(j <= 40)
		{
			mlx_pixel_put(vars.mlx, vars.win, j + x, i + y, color);
			j++; 
		}
		i++;
	}
}

void print_map(t_vars vars)
{
    int i;
    int j;

    j = 0;
    while (j < HEIGHT)
    {
        i = 0;
        while (i < WIDTH)
        {
            if (map[j][i] == 1)
            {
                print_big(vars, i*40, j*40);
            }
            if (map[j][i] == 5)
               print_big(vars, i*40, j*40);
            i++;
        }
        j++;
    }
}

/*
typedef struct s_player
{   
    int x;
    int y;
    int fov;
    int angle;
    
};              t_player;
*/

int             close_win(int keycode, t_vars *vars)
{
    
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return(0);
}

int move(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    if(keycode == 123)
        vars->x = vars->x-1; 
    if(keycode == 124)
        vars->x = vars->x+1;
    if(keycode == 126)
        vars->y = vars->y-1;
    if(keycode == 125)
        vars->y = vars->y+1;

    print_map(*vars);
}

int main()
{
    
    t_vars    vars;
    int x;
    int y;

    y = 0;
    x = 0;
    vars.x = 1;
    vars.y = 1;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1280, 1000, "Hello World");
    print_map(vars);
    /*
    while(x < 800)
    {
        mlx_pixel_put(vars.mlx, vars.win, x, 0, 0xff0000);
        mlx_pixel_put(vars.mlx, vars.win, x, 800, 0xff0000);
        x++;
    }
    while(y < 800)
    {
        mlx_pixel_put(vars.mlx, vars.win, 0, y, 0xff0000);
        mlx_pixel_put(vars.mlx, vars.win, 800, y, 0xff0000);
        y++;
    }
    */
    mlx_hook(vars.win, 2, 1L<<0, move, &vars);
    mlx_loop_hook(vars.mlx, print_map, &vars);
    mlx_loop(vars.mlx);
    return(0);
}