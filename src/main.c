#include <cglm/cglm.h>
#include <config.h>
#include <render/camera/camera.h>
#include <render/render.h>
#include <stdio.h>
#include <utils.h>
#include <window/window.h>

#define randomf() (((float)random()) / (float)RAND_MAX)
int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char **argv)
{
    Render render = {};

    Window curr_window = {};
    Camera cam = {};

    Scene scene = {};

    scene_init(&scene);

    scene_push_circle(&scene, vec3$(0, -1000, -1), 1000., scene_push_lambertian(&scene, vec3$(0.5, 0.5, 0.5)));

    for (int i = -11; i < 11; i++)
    {
        for (int j = -11; j < 11; j++)
        {
            float v = randomf();

            Vec3 center = vec3$(i + 0.9 * randomf(), 0.2, j + 0.9 * randomf());
            if ((vec3_length(vec3_sub(center, vec3$(4, 0.2, 0)))) < 0.9)
            {
                continue;
            }

            if (v < 0.8)
            {
                scene_push_circle(&scene, center, 0.2, scene_push_lambertian(&scene, vec3$(randomf(), randomf(), randomf())));
            }
            else if (v < 0.95)
            {
                float fuzz = randomf() * 0.5;

                scene_push_circle(&scene, center, 0.2, scene_push_metal(&scene, vec3$(randomf(), randomf(), randomf()), fuzz));
            }
            else
            {
                scene_push_circle(&scene, center, 0.2, scene_push_dieletric(&scene, 1.5));
            }
        }
    }

    scene_push_circle(&scene, vec3$(0, 1, 0), 1, scene_push_dieletric(&scene, 1.5));
    scene_push_circle(&scene, vec3$(-4, 1, 0), 1, scene_push_lambertian(&scene, vec3$(0.4, 0.2, 0.1)));
    scene_push_circle(&scene, vec3$(4, 1, 0), 1, scene_push_metal(&scene, vec3$(0.7, 0.6, 0.5), 0));

    window_engine_init();
    window_init(&curr_window);

    render_engine_init(&curr_window, &scene);
    render_init(&render);

    camera_init(&cam, (void *)window_raw_handle(&curr_window), CAMERA_CONTROLLABLE);
    cam.aperture = 8.0;
    cam.focus_disc = (2.0f);
    cam.pos = vec3$(13, 2, 3);
    cam.front = vec3_unit(vec3_sub(vec3$(0, 0, 0), cam.pos));
    while (!window_should_close(&curr_window))
    {

        window_update(&curr_window);
        camera_update(&cam, (void *)window_raw_handle(&curr_window));
        render_engine_update_cam(&render, &cam);
        render_engine_frame(&render);
    }

    render_deinit(&render);
    render_engine_deinit();
    window_deinit(&curr_window);
    window_engine_deinit();
    return 0;
}
