/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 15:12:15 by lpilotto          #+#    #+#             */
/*   Updated: 2016/08/22 15:30:55 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <fcntl.h>
#include <unistd.h>

static int		write_header(int fd, t_image *img, int palette)
{
	char	header[54];

	*((short *)(header + 0x0)) = 0x4d42;
	*((int *)(header + 0x2)) = img->width * img->height * img->type + 54;
	*((int *)(header + 0x6)) = 0x0;
	*((int *)(header + 0xA)) = 54;
	*((int *)(header + 0xE)) = 40;
	*((int *)(header + 0x12)) = img->width;
	*((int *)(header + 0x16)) = img->height;
	*((short *)(header + 0x1A)) = 0x1;
	*((short *)(header + 0x1C)) = img->type;
	*((int *)(header + 0x1E)) = 0x0;
	*((int *)(header + 0x22)) = img->width * img->height * img->type
		+ BMP_PADDING(img);
	*((int *)(header + 0x26)) = 0x0b13;
	*((int *)(header + 0x2A)) = 0x0b13;
	*((int *)(header + 0x2E)) = palette;
	*((int *)(header + 0x32)) = 0;
	if (write(fd, header, 54) <= 0)
		return (-1);
	return (0);
}

static int		my_pow(int a, int pow)
{
	int		r;
	int		i;

	r = pow > 0 ? a : 1;
	i = 0;
	while (++i < pow)
		r *= a;
	return (r);
}

static int		write_palette(int fd, t_palette *palette)
{
	int		i;
	int		b;

	i = -1;
	while (++i < palette->count)
	{
		b = 0 | palette->colors[i].b | (palette->colors[i].g << 8)
			| (palette->colors[i].b << 16);
		if (write(fd, &b, 4) <= 0)
			return (-1);
	}
	return (0);
}

int				save_to_bmp(char *file, t_image *img)
{
	int		fd;
	int		palette;

	if ((fd = open(file, O_WRONLY | O_CREAT, 0666)) < 0)
		return (-1);
	palette = img->palette && img->type == BMP_8 && img->palette->count
		< my_pow(2, img->type) ? img->palette->count : 0;
	if ((write_header(fd, img, palette) == -1)
		|| (palette != 0 && write_palette(fd, img->palette) == -1))
	{
		close(fd);
		return (-1);
	}
	write(fd, img->data, img->width * img->height * img->type
		+ BMP_PADDING(img));
	close(fd);
	return (0);
}
