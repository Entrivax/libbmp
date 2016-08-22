/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 10:32:55 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/22 16:10:30 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <unistd.h>

void	set_pixel_p(t_image *img, int x, int y, unsigned char palette_index)
{
	if (img->type == BMP_8)
	{
		if (palette_index > img->palette->count)
			palette_index = img->palette->count - 1;
		*((unsigned char *)(img->data + x + y * (img->width
			+ BMP_PADDING(img)))) = palette_index;
	}
	else
		write(2, "Type not supported! Use set_pixel instead!\n", 43);
}

void	set_pixel(t_image *img, int x, int y, t_rgb rgb)
{
	if (img->type == BMP_24)
	{
		*((unsigned char *)(img->data + (x + y * (img->width
			+ BMP_PADDING(img))) * BMP_24 / 8)) = rgb.b;
		*((unsigned char *)(img->data + (x + y * (img->width
			+ BMP_PADDING(img))) * BMP_24 / 8 + 1)) = rgb.g;
		*((unsigned char *)(img->data + (x + y * (img->width
			+ BMP_PADDING(img))) * BMP_24 / 8 + 2)) = rgb.r;
	}
	else
		write(2, "Type not supported! Use set_pixel_p instead!\n", 45);
}
