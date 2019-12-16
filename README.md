# fractol
#### my 42 nickname - chermist
> Code written in norminette code style(github.com/sabrusrin/norme)

Fractals visualisation using time-escape algorithm and parallel computing  
Визуализация фракталов при помощи алгоритма time-escape и параллельных вычислений

##### For visualisation I used a minilibx(ecole42 graphic library) that gives a functions to create/destroy/clear window, to put a pixel to the window I created and to work with keyboard/mouse events.

Use make to build project on macos.  

#### If you want to build project on linux machine, follow these steps:
```
1) Update/upgrade your system:
  apt-get update
  apt-get upgrade

2) Install the following packages:
  apt-get install libx11-dev
  apt-get install libxext-dev

3) ./configure
4) Use make command: make linux
Hope it will work :)
```
### Usage:	
```
./fractol [option]  
	mandelbrot  
	julia  
	multi_julia  
	perpendicular_burning_ship  
	burning_ship  
	compass  
	mandelbar  
	orth_mandl  
```
![mandelbrot](https://raw.githubusercontent.com/sabrusrin/fractol/master/images/mandelbrot.png)
![julia1](https://raw.githubusercontent.com/sabrusrin/fractol/master/images/julia1.png)
![julia2](https://raw.githubusercontent.com/sabrusrin/fractol/master/images/julia2.png)
![usage](https://raw.githubusercontent.com/sabrusrin/fractol/master/images/usage.png)
