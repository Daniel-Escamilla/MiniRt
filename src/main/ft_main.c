/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2024/10/30 18:20:22 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void ft_redraw_scene(t_image *image, int dx, int dy)
{
	// Ajusta la posición de la cámara basándote en los valores del ratón
	float sensitivity = 0.01f; // Ajusta la sensibilidad según sea necesario
	image->sphere->position.x += dx * sensitivity;
	image->sphere->position.y -= dy * sensitivity;

	// Llama a ft_create_render para redibujar la escena con los nuevos valores de la cámara
	ft_create_render(image->data, image);
}

int mouse_press(int button, int x, int y, t_image *image)
{
    if (button == 3) // Detecta solo el botón derecho del ratón
    {
        image->is_pressed = 1;
        image->mouse_x = x;
        image->mouse_y = y;
        mlx_mouse_hide(image->mlx, image->mlx_win);
        printf("Botón presionado en posición (%d, %d)\n", x, y);
    }
    return (0);
}

// Función para manejar el evento de soltar el botón del ratón
int mouse_release_scroll(int button, int x, int y, t_image *image)
{
    float sensitivity = 0.1f; // Ajusta la sensibilidad según sea necesario

    if (button == 3) // Detecta solo el botón derecho del ratón
    {
        image->is_pressed = 0;
        mlx_mouse_show(image->mlx, image->mlx_win);	
        printf("Botón soltado en posición (%d, %d)\n", x, y);
    }
    else if (button == 4) // Rueda del ratón hacia adelante
    {
        image->sphere->position.z -= sensitivity;
        printf("Rueda del ratón hacia adelante en posición (%d, %d)\n", x, y);
    }
    else if (button == 5) // Rueda del ratón hacia atrás
    {
        image->sphere->position.z += sensitivity;
        printf("Rueda del ratón hacia atrás en posición (%d, %d)\n", x, y);
    }

    // Llama a ft_create_render para redibujar la escena con los nuevos valores de la posición de la esfera
    ft_create_render(image->data, image);

    return (0);
}

int loop_hook(t_image *image)
{
    if (image->is_pressed)
    {
        int x;
		int	y;
        mlx_mouse_get_pos(image->mlx, image->mlx_win, &x, &y);
        int dx = x - image->mouse_x;
        int dy = y - image->mouse_y;

        image->mouse_x = x;
        image->mouse_y = y;
        printf("Sosteniendo botón en posición (%d, %d)\n", x, y);

        ft_redraw_scene(image, dx, dy);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_image image;

    (void) argc;
    (void) argv;
    ft_initialize(&image);
    ft_create_window(image.data, &image);
    ft_create_render(image.data, &image);
    mlx_key_hook(image.mlx_win, ft_key_hook, &image);

    image.is_pressed = 0;

    mlx_hook(image.mlx_win, 4, 1L<<2, mouse_press, &image);     // Evento de presionar el botón
    mlx_hook(image.mlx_win, 5, 1L<<3, mouse_release_scroll, &image);   // Evento de soltar el botón y desplazamiento de la rueda del ratón

    mlx_loop_hook(image.mlx, loop_hook, &image);                // Evento de loop
    
    mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);
    
    mlx_loop(image.mlx); 

    return (0);
}
