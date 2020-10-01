/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:47:46 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/10/01 13:20:50 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./minilibx/mlx.h"
#define WIDTH 15
#define HEIGHT 10
#define SCREEN_HEIGHT 1200
#define SCREEN_WIDTH 1600

typedef struct s_player
{   
    float x;
    float y;
    float fov;
    float angle;
    float cos;
    float sin;
    float speed;
    float rotation;
    
}              t_player;

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct s_walls
{
    int wall;
    float distance;
    float height;
}               t_walls;

typedef struct s_textdata {
    void *img;
    char *addr;
    int   bits_per_pixel;
    int   line_length;
    int   endian;
    int width;
    int height;
    int texture;
    int texturepositionx;
    int color;

}               t_textdata;

typedef struct  s_vars {
        void    *mlx;
        void    *win;
        float      x;
        float      y;
        int raycount;
        float ray;
        t_player    player;
        t_walls     walls;
        t_img       data;
        t_textdata  text;
}               t_vars;


extern int map[HEIGHT][WIDTH];
extern int bitmap[8][8];

void    ch_mlx_pixel_put(t_img *data, int x, int y, int color);
void dda_algorithm(t_img *data, int x0, int y0, int x1, int y1, int color);
int raycasting(t_vars *vars);
int move(int keycode, t_vars *vars);

#endif
