#ifndef STRUCT_H
# define STRUCT_H


typedef struct          s_img
{
  void *mlx;
  void *win;
  unsigned long img_color;
  char *data;
  void *img_ptr;
  int sizeline;
  int bpp;
  int x;
  int y;
  int endian;
  void *mlx_ptr;
}                                       t_img;

typedef struct          s_event
{
  float xd;
  float yd;
}                                       t_event;

typedef struct          s_struct
{
  void *mlx;
  void *win;
  char ***coord;
  int i;
  int maxline;
  int zoom;
  t_img *img;
  t_event *event;  
  struct s_struct   *next;
  struct s_struct   *before;
}                                       t_struct;

typedef struct          s_temp
{
  int x1;
  int x2;
  int y1;
  int y2;
  int val1;
  int val2;
  int color;
}                                       t_temp;

void draw_with_tab_on_img(char ***coord, int i, int maxline, t_struct *param);
void    my_pixel_put_to_image(t_img *myimg,int x, int y, int color);
void draw_with_tab(char ***coord, int i, int maxline, t_struct *param);
char ***set_coord(char ***coord, float i, float x, float y, float zoom);
char ***create_coord_tab(char **tab, char ***coord, int i);
char **create_tab(char *argv, char **tab);
void fill_iso_rect(void *mlx, void *win, int x, int y, int t,int color);
char *ft_strjoins(char const *s1, char const *s2);
static char *ft_join(char const *s1, char const *s2, int len1, int len2);
void draw_line2(void *mlx, void *win, float xi, float yi, float xf, float yf, int color);

#endif
