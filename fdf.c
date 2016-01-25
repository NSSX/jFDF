#include "struct.h"
#include "get_next_line.h"
#include <mlx.h>
#include <stdio.h>
#include "libft/libft.h"
//Const fill_rect
#define RECTX 10
#define RECTY 10
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "struct.h"
#include <math.h>
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
#define WIDTH 1500
#define HEIGTH 1500

int couleur(double t)
{
  return ((RGB(127.5 * (cos(t) + 1), 127.5 * (sin(t) + 1), 127.5 * (1 - cos(t)))));
}

char ***set_coordq(char ***coord, float i, float x, float y, float zoom);
char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate);

void draw_line_on_img(t_img *myimg,float xi, float yi, float xf, float yf, int color)
{
  int dx,dy,i,xinc,yinc,cumul,x,y ;
  x = xi ;
  y = yi ;
  dx = xf - xi ;
  dy = yf - yi ;
  xinc = ( dx > 0 ) ? 1 : -1 ;
  yinc = ( dy > 0 ) ? 1 : -1 ;
  dx = abs(dx) ;
  dy = abs(dy) ;
  my_pixel_put_to_image(myimg, x, y, color);
  if ( dx > dy ) {
    cumul = dx / 2 ;
    for ( i = 1 ; i <= dx ; i++ ) {
      x += xinc ;
      cumul += dy ;
      if ( cumul >= dx ) {
	cumul -= dx ;
	y += yinc ; }
      my_pixel_put_to_image(myimg, x, y, color); } }
  else {
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) {
      y += yinc ;
      cumul += dx ;
      if ( cumul >= dy ) {
	cumul -= dy ;
	x += xinc ; }
      my_pixel_put_to_image(myimg, x, y, color); } }
}

static char *ft_join(char const *s1, char const *s2, int len1, int len2)
{
  char *join;
  int i;
  int j;

  i = 0;
  j = 0;
  join = malloc(sizeof(char) * (len1 + len2) + 1);
  while (s1[i] != '\0')
    {
      join[i] = s1[i];
      i++;
    }
  while (s2[j] != '\0')
    {
      join[i] = s2[j];
      i++;
      j++;
    }
  join[i] = '\0';
  return (join);
}

char *ft_strjoins(char const *s1, char const *s2)
{
  int len1;
  int len2;
  char *join;

  if (!s1 || !s2)
    return (NULL);
  len1 = ft_strlen(s1);
  len2 = ft_strlen(s2);
  join = ft_join(s1, s2, len1, len2);
  return (join);
}

void place_img(t_struct *param, float xd, float yd)
{
  mlx_destroy_image(param->mlx, param->img->img_ptr);
  param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
  set_coordq(param->coord, param->i, xd, yd, param->zoom);
  draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
  mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
}


void img_move(int keycode, t_struct *param)
{
  if(keycode == 2)
    {
      param->event->xd += 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 1)
    {
      param->event->yd += 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 13)
    {
       param->event->yd -= 40;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 0)
    {
       param->event->xd -= 40;
      place_img(param, param->event->xd, param->event->yd);
    }
}

void img_zoom(int keycode, t_struct *param)
{
  if(keycode == 12)
    {
      if(param->zoom < 5)
        {
          param->zoom += 1;
        }
      else
        param->zoom += 5;
      place_img(param, param->event->xd, param->event->yd);
    }
  if(keycode == 14)
    {
      if(param->zoom >= 10)
        param->zoom -= 5;
      else
        param->zoom -= 0.5;
      place_img(param, param->event->xd, param->event->yd);
    }
}

void img_other_view(int keycode, t_struct *param)
{
  if(keycode == 124)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coord3(param->coord, param->i, 0, 0, param->zoom,45);
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
  if(keycode == 123)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coord3(param->coord, param->i, param->event->xd, param->event->yd, param->zoom,45);
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
}

void img_other(int keycode, t_struct *param)
{
  if(keycode == 17)
    {
      mlx_destroy_image(param->mlx, param->img->img_ptr);
      param->img->img_ptr = mlx_new_image(param->mlx, WIDTH, HEIGTH);
      set_coord(param->coord, param->i, param->event->xd, param->event->yd, param->zoom);
      draw_with_tab_on_img(param->coord, param->i, param->maxline, param);
      mlx_put_image_to_window(param->mlx, param->win, param->img->img_ptr, 0, 0);
    }
  if(keycode == 49)
    {
      place_img(param, param->event->xd, param->event->yd);
    }
}

int event_mlx(int keycode, t_struct *param)
{
  if(keycode == 53)
    exit(1); 
  img_move(keycode, param);
  img_zoom(keycode, param);
  img_other_view(keycode, param);
  img_other(keycode, param);
  return (0);
}

char **create_tab(char *argv, char **tab)
{
  char *line;
  char *yt;
  int fd;
  int ret;

  fd = 0;
  ret = 0;
  fd = open(argv, O_RDONLY);
  line = (char *)malloc(sizeof(char) * 2);
  while((ret = get_next_line(fd,&yt)))
    {
      line = ft_strjoins(line,yt);
      line = ft_strjoins(line, " \n ");
    }
  tab = ft_strsplit(line, ' ');
  return (tab);
}

char ***create_coord_tab(char **tab, char ***coord, int i)
{
  int index;
  
  index = 0;
  coord = (char ***)malloc(sizeof(char **) * i + 1);
  while(index < i)
    {
      coord[index] = (char **)malloc(sizeof(char *) * 5);
      index++;
    }
  index = 0;
  while(index < i)
    {
      coord[index][0] = (char *)malloc(sizeof(char) * 5);
      coord[index][1] = (char *)malloc(sizeof(char) * 5);
      coord[index][2] = tab[index];
      index++;
    }
  return (coord);
}

char ***set_coord3(char ***coord, int i, int x, int y, int zoom, int rotate)
{
  int index;
  int xdep;
  int ydep;
  int xtemp;
  int ytemp;
  int j;
  int v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x + v;
	      ytemp =  y - ((v * 2)  + 1);
	      j++;
	    }
	}
      index++;
    }
  return (coord);
}

char ***set_coord(char ***coord, float i, float x, float y, float zoom)
{
  int index;
  float xdep;
  float ydep;
  float xtemp;
  float ytemp;
  float j;
  float v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= zoom;
	  y += zoom;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom;
	  y += zoom;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp = x;
	      ytemp = y - ((v * 2)  + 1);
	      j++;
	    }
	}
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      index++;
    }
  return (coord);
}

char ***set_coordq(char ***coord, float i, float x, float y, float zoom)
{
  int index;
  float xdep;
  float ydep;
  float xtemp;
  float ytemp;
  float j;
  float v;

  v = 0;
  j = 0;
  index = 0;
  xdep = x;
  ydep = y;
  while(index < i)
    {
      if(coord[index][2][0] == '\n')
	{
	  x = xdep;
	  y = ydep;
	  x -= zoom * 0.86;
	  y += zoom* 0.5;
	  xdep = x;
	  ydep = y;
	}
      else
	{
	  x += zoom * 0.86;
	  y += zoom * 0.5;
	  if(coord[index][2][0] != '0')
	    {
	      v = ft_atoi(coord[index][2]);
	      xtemp  = x;
	      ytemp = y - (v * zoom);
	      j++;
	    }
	}
      if(j == 0)
	{
	  coord[index][0] = ft_itoa(x);
	  coord[index][1] = ft_itoa(y);
	}
      else
	{
	  coord[index][0] = ft_itoa(xtemp);
	  coord[index][1] = ft_itoa(ytemp);
	  j = 0;
	}
      index++;
    }
  return (coord);
}

int testa(x1,y1,x2,y2)
{
  if((x1 >= WIDTH) || (x2 >= WIDTH) || (y1 >= WIDTH) || (y2 >= WIDTH) || (y1 <= 0) || (y2 <= 0) || (x1 <= 0) || (x2 <= 0))
    return (0);
  return (1);
}

int color2(int val1, int val2, int color)
{
  if(val1 + val2 >= 30 && val1 + val2 <= 60)
    color = 0x167341;
  else if(val1 + val2 >= 61 && val1 + val2 <= 90)
    color = 0xDE5A39;
  else if(val1 + val2 >= 91 && val1 + val2 <= 130)
    color = 0x5D6ADC;
  else if(val1 + val2 >= 131 && val1 + val2 <= 200)
    color = 0xFF99CC;
  else if(val1 + val2 >= 201 && val1 + val2 <= 350)
    color = 0x161D5F;
  else
    color = 0xFFFFFF;
  return (color);
}

int give_color(int val1, int val2)
{
  int color;

  color = 0;
  if(val1 + val2 < 0)
    color = 255 + (val1 + val2);
  else if(val1 + val2 >= 0 && val1 + val2 <= 3)
    color = 0xCCCC00;
  else if(val1 + val2 >= 4 && val1 + val2 <= 8)
    color = 0x4C9900;
  else if(val1 + val2 >= 9 && val1 + val2 <= 13)
    color = 0xFF8000;
  else if(val1 + val2 >= 14 && val1 + val2 <= 21)
    color = 0xFF6666;
  else if(val1 + val2 >= 22 && val1 + val2 <= 29)
    color = 0x6600CC;
   else
     color = color2(val1, val2, color);
  return (color);
}

void first_part(char ***coord, int index, t_struct *param)
{
  t_temp *temp;

  temp = (t_temp *)malloc(sizeof(t_temp) * 12);
  temp->x1 = ft_atoi(coord[index][0]);
  temp->y1 = ft_atoi(coord[index][1]);
  temp->x2 = ft_atoi(coord[index + 1][0]);
  temp->y2 = ft_atoi(coord[index + 1][1]);
  temp->val1 = ft_atoi(coord[index][2]);
  temp->val2 = ft_atoi(coord[index + 1][2]);
  temp->color = give_color(temp->val1, temp->val2);
  if(testa(temp->x1,temp->y1,temp->x2,temp->y2))
    draw_line_on_img(param->img,temp->x1, temp->y1, temp->x2, temp->y2, temp->color);
  free(temp);
}


void second_part(char ***coord, int index, int maxline, t_struct *param)
{
  t_temp *temp;
  
  temp = (t_temp *)malloc(sizeof(t_temp) * 12);
  temp->x1 = ft_atoi(coord[index][0]);
  temp->y1 = ft_atoi(coord[index][1]);
  temp->x2 = ft_atoi(coord[index + maxline + 1][0]);
  temp->y2 = ft_atoi(coord[index + maxline + 1][1]);
  temp->val1 = ft_atoi(coord[index][2]);
  temp->val2 = ft_atoi(coord[index + maxline + 1][2]);
  temp->color = give_color(temp->val1, temp->val2);
  if(testa(temp->x1,temp->y1,temp->x2,temp->y2))
    draw_line_on_img(param->img,temp->x1, temp->y1, temp->x2, temp->y2, temp->color);
  free(temp);
}


int new_index(int index, int futurindex)
{
  if(futurindex > 0)
    {
      index += 2;
      futurindex = 0;
    }
  else
    index++;
  return (index);
}

int new_futurindex(int index, int futurindex)
{
  if(futurindex > 0)
    {
      index += 2;
      futurindex = 0;
    }
  else
    index++;
  return (futurindex);
}

void draw_with_tab_on_img(char ***coord, int i, int maxline, t_struct *param)
{
  int index;
  int futurindex;

  futurindex = 0;
  index = 0;
  while(index + 1 < i)
    {
      if(index + 1 < i)
	{
	  if(coord[index + 1][2][0] != '\n')
	    first_part(coord, index, param);
	  else
	    futurindex++;	 
	}
      if(index + maxline + 1 < i)
	{
	  if(coord[index + maxline + 1][2][0] != '\n')
	    second_part(coord, index, maxline, param);
	  else
	    futurindex++;
	}
      index = new_index(index, futurindex);
      futurindex = new_futurindex(index, futurindex);
    }
}  

void    my_pixel_put_to_image(t_img *myimg,int x, int y, int color)
{

  int i;
  unsigned char color1;
  unsigned char color2;
  unsigned char color3;
  myimg->data = mlx_get_data_addr(myimg->img_ptr, &myimg->bpp, &myimg->sizeline, &myimg->endian);

  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 ] = color % 256;
  color /= 256;
  myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 1] = color % 256;
  color /= 256;
  myimg->  data[y * myimg->sizeline + x * myimg->bpp / 8 + 2] = color % 256;
}

t_struct *give(t_struct *mystruct, void *mlx, void *win)
{
  mystruct = (t_struct *)malloc(sizeof(t_struct) * 20);
  mystruct->mlx = mlx;
  mystruct->win = win;
  mystruct->zoom = 20;
  return (mystruct);
}

int give_maxline(char **tab)
{
  int maxline;
  int index;

  maxline = 0;
  index = 0;
  while(tab[index][0] != '\n')
    {
      if(tab[index][0] != ' ')
        maxline++;
      index++;
    }
  return (maxline);
}


t_struct *give2(t_struct *mystruct, int i, int maxline, char ***coord)
{
  mystruct->i = i;
  mystruct->maxline = maxline;
  mystruct->coord = coord;
  return (mystruct);
}



t_img *give_img(t_img *myimg, void *mlx)
{
  myimg = (t_img *)malloc(sizeof(t_img) * 10);
  myimg->img_ptr = mlx_new_image(mlx, WIDTH, HEIGTH);
  myimg->mlx_ptr = mlx;
  return (myimg);
}

int main(int argc, char **argv)
{ 
  void *mlx;
  void *win;
  char *line;
  int i;
  int maxline;  
  t_struct *mystruct;
  char ***coord;
  char **tab;
  t_img *myimg;
  t_event *myevent;

  myevent = (t_event *)malloc(sizeof(t_event) * 4);
  myevent->xd = 300;
  myevent->yd = 60;
  maxline = 0;
  i = 0;
  if(argc != 2)
    {
      printf("Bug arg");
      return (0);
    }
  mlx = mlx_init();
  win = mlx_new_window(mlx, WIDTH, HEIGTH, "42");
  mystruct = give(mystruct, mlx, win);
  tab = create_tab(argv[1], tab);
  while(tab[i])
    i++;
  coord = create_coord_tab(tab, coord, i);
  coord = set_coordq(coord, i, 300, 60, mystruct->zoom);
  maxline = give_maxline(tab);
  mystruct = give2(mystruct, i,maxline, coord);
  myimg = give_img(myimg, mlx);
  mystruct->img = myimg;
  mystruct->event = myevent;
  draw_with_tab_on_img(coord, i, maxline, mystruct);
  place_img(mystruct, 300, 60);
  mlx_key_hook(mystruct->win, event_mlx, mystruct);
  mlx_loop(mlx);
  return(0);

}
