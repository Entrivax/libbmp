/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:40:30 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/22 10:47:44 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <stdlib.h>

t_palette	*create_palette(int size)
{
	t_palette	*pal;

	if (!(pal = (t_palette *)malloc(sizeof(t_palette))))
		return (NULL);
	pal->count = size;
	return (pal);
}

t_palette	*create_safety_palette(void)
{
	t_palette	*pal;
	int			i;
	int			rgb[3];

	if (!(pal = create_palette(256)))
		return (NULL);
	rgb[0] = -51;
	i = 20;
	pal->colors[0] = get_rgb(0, 0, 0);
	pal->colors[1] = get_rgb(255, 255, 255);
	while ((rgb[0] += 51) <= 255)
	{
		rgb[1] = -51;
		while ((rgb[1] += 51) <= 255)
		{
			rgb[2] = -51;
			while ((rgb[2] += 51) <= 255)
			{
				pal->colors[i] = get_rgb(rgb[0], rgb[1], rgb[2]);
				i++;
			}
		}
	}
	return (pal);
}

t_image		*create_image(int width, int height, int type, t_palette *palette)
{
	t_image		*img;

	if ((img = (t_image *)malloc(sizeof(t_image))) == NULL)
		return (NULL);
	img->type = type;
	img->width = width;
	img->height = height;
	if ((img->data = malloc(img->height * (img->width + BMP_PADDING(img))
				* BMP_24 / 8)) == NULL)
	{
		free(img);
		return (NULL);
	}
	img->palette = palette;
	return (img);
}
