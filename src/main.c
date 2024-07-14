#include "mlx.h"

int main()
{
	void *mlx;
	void *window;

	mlx = mlx_init();
	if (!mlx)
	{
		//
		return 1;
	}

	window = mlx_new_window(mlx, 240, 160, "Whisked by the Wind");

	mlx_loop(mlx);
	return 0;
}