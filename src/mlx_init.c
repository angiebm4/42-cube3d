#include "../include/cub3d.h"

void    init_textures(t_cube *cube, t_parsed_data *parsed)
{
    int img_width;
    int img_height;
    int i;

    i = 0;
    while (i < TEXTURES_COUNT)
    {
        if (i == DOOR_TEXTURE && cube->grafic->textures[i] == NULL)
        {
            i++;
            continue ;
        }
        cube->grafic->textures[i] = 
            mlx_xpm_file_to_image(cube->grafic->mlx, parsed->textures_name[i],
            &img_width, &img_height);
        if (cube->grafic->textures[i] == NULL)
        {
            ft_printf("%sINVALID TEXTURE%s\n", RED, CLEAR);
            destroy_parsed(parsed);
            end_program(cube);
        }
        i++;
    }
    i = 0;
    while (i < PIXELS_COUNT)
    {
        pixel_copy(&cube->grafic->default_pixels[i], &parsed->default_pixels[i]);
        i++;
    }
}

void    init_map(t_cube *cube, t_parsed_data *parsed)
{
    int i;

    cube->map = malloc(sizeof(char*) * (map_length(parsed->map) + 1));
    if (cube->map == NULL)
        exit(1); /* TODO: exit malloc error*/

    i = 0;
    while (parsed->map[i])
    {
        cube->map[i] = ft_strdup(parsed->map[i]);
        if (cube->map[i] == NULL)
            exit (1); /* TODO: malloc exit */
        i++;
    }
    cube->map[i] = NULL;
}

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{

    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_WIDTH, WINDOW_HEIGTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/

    /* Init the image information */
    /* TODO: Check errors on init */
    cube->grafic->img = mlx_new_image(cube->grafic->mlx, WINDOW_WIDTH, WINDOW_HEIGTH);
    cube->grafic->data_addr = mlx_get_data_addr(cube->grafic->img, &cube->grafic->bpp, &cube->grafic->size_line, &cube->grafic->endian);

    ft_bzero(&cube->pj, sizeof(t_player));
    init_player(cube, parsed);

    ft_bzero(&cube->grafic->raycasting, sizeof(t_raycasting));

    ft_bzero(&cube->grafic->mouse, sizeof(t_mouse));
    cube->grafic->mouse.lastX = -1;
    cube->grafic->mouse.mouse_vision = 1;
    cube->grafic->mouse.fixed = 0;

    destroy_parsed(parsed);
}