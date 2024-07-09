#include "mlx.h"
#include "game.h"
#include "boss.h"

void init_boss(Boss *boss);
void update_boss(Boss *boss, float delta_time);
void render_boss(const Boss *boss, void *mlx, void *window, void *boss_img);
void cleanup_boss(Boss *boss);
