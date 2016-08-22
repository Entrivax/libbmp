/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 14:33:25 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/22 10:45:56 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBMP_H
# define LIBBMP_H

# define BMP_24 24
# define BMP_8 8
# define BMP_PADDING(img) (((img->width * img->type) % 4) * img->height)

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct		s_palette
{
	t_rgb			colors[256];
	int				count;
}					t_palette;

typedef struct		s_image
{
	unsigned int	width;
	unsigned int	height;
	unsigned char	type;
	unsigned char	*data;
	t_palette		*palette;
}					t_image;

int					save_to_bmp(char *file, t_image *img);
t_palette			*create_palette(int size);
t_palette			*create_safety_palette(void);
t_image				*create_image(int width, int height, int type,
									t_palette *palette);
void				set_pixel(t_image *img, int x, int y, t_rgb rgb);
void				set_pixel_p(t_image *img, int x, int y,
									unsigned char palette_index);
t_rgb				get_rgb(unsigned char r, unsigned char g, unsigned char b);
void				set_rgb(t_rgb *rgb, unsigned char r, unsigned char g,
									unsigned char b);

#endif
