/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:39:46 by descamil          #+#    #+#             */
/*   Updated: 2024/10/27 00:59:05 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// int ft_loop(t_image *image)
// {
//     ft_create_render(image->data, image); // Renderiza la imagen
//     return (0);  // Devolver 0 para continuar el bucle
// }

void update_camera_vectors(t_camera *camera)
{
    t_vec3 front;



    front.x = cosf(camera->yaw) * cosf(camera->pitch); // 

    front.y = sinf(camera->pitch);

    front.z = sinf(camera->yaw) * cosf(camera->pitch);




    camera->front = front;

    // Recalcular los vectores right y up
    camera->right.x = front.z * camera->world_up.y - front.y * camera->world_up.z;
    camera->right.y = front.x * camera->world_up.z - front.z * camera->world_up.x;
    camera->right.z = front.y * camera->world_up.x - front.x * camera->world_up.y;

    camera->up.x = camera->right.y * front.z - camera->right.z * front.y;
    camera->up.y = camera->right.z * front.x - camera->right.x * front.z;
    camera->up.z = camera->right.x * front.y - camera->right.y * front.x;
}

void init_camera(t_camera *camera, t_vec3 position, t_vec3 up, float yaw, float pitch)
{
    camera->position = position;
    camera->world_up = up;
    camera->yaw = yaw;
    camera->pitch = pitch;
    camera->front = (t_vec3){0.0f, 0.0f, -1.0f};
    update_camera_vectors(camera);
}

void    ft_process_mouse_movement(t_camera *camera, float xoffset, float yoffset, int constrain_pitch)
{
    float sensitivity = 0.001f; // Ajusta la sensibilidad según sea necesario
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->yaw += xoffset;
    camera->pitch -= yoffset;

    (void) constrain_pitch;
    if (camera->yaw > 2 * M_PI)
        camera->yaw -= 2 * M_PI;
    else if (camera->yaw < 0)
        camera->yaw += 2 * M_PI;

    if (camera->pitch > M_PI_2)
        camera->pitch = M_PI_2;
    if (camera->pitch < -M_PI_2)
        camera->pitch = -M_PI_2;

    update_camera_vectors(camera);
}

void ft_redraw_scene(t_image *image, int dx, int dy) {
    // Ajusta la posición de la cámara basándote en los valores del ratón
    float sensitivity = 0.01f; // Ajusta la sensibilidad según sea necesario
    image->camera->position.x -= dx * sensitivity;
    image->camera->position.z += dy * sensitivity;

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
int mouse_release(int button, int x, int y, t_image *image)
{
    if (button == 3) // Detecta solo el botón derecho del ratón
    {
        image->is_pressed = 0;
		mlx_mouse_show(image->mlx, image->mlx_win);	
        printf("Botón soltado en posición (%d, %d)\n", x, y);
    }
    return (0);
}

// Función para manejar el loop
int loop_hook(t_image *image)
{
    if (image->is_pressed)
    {
        int x, y;
        mlx_mouse_get_pos(image->mlx, image->mlx_win, &x, &y);
        int dx = x - image->mouse_x;
        int dy = y - image->mouse_y;

        // Actualiza la posición de la cámara basándote en dx y dy
        ft_process_mouse_movement(image->camera, dx, dy, 1);

        image->mouse_x = x;
        image->mouse_y = y;
        printf("Sosteniendo botón en posición (%d, %d)\n", x, y);

        // Redibuja la escena
        ft_redraw_scene(image, dx, dy);
    }
    return (0);
}

int	main(int argc, char **argv)
{
	t_image	image;

	(void) argc;
	(void) argv;
	ft_initialize(&image);
	ft_create_window(image.data, &image);
	ft_create_render(image.data, &image);
	mlx_key_hook(image.mlx_win, ft_key_hook, &image);

	image.is_pressed = 0;

    init_camera(image.camera, (t_vec3){0.0f, 0.0f, 2.0f}, (t_vec3){0.0f, 1.0f, 0.0f}, -M_PI_2, 0.0f);

	mlx_hook(image.mlx_win, 4, 1L<<2, mouse_press, &image);     // Evento de presionar el botón
    mlx_hook(image.mlx_win, 5, 1L<<3, mouse_release, &image);   // Evento de soltar el botón

    
    mlx_loop_hook(image.mlx, loop_hook, &image);				// Evento de loop
	
	mlx_hook(image.mlx_win, 17, 0, ft_end_program, &image);

    mlx_loop(image.mlx); 

	return (0);
}
