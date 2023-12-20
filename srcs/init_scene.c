#include "../incs/minirt.h"

void	ft_init_scene(char *file, t_scene *scene)
{
  (void)file;
  scene->num_shapes = 5;

  scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes); /* メモリ確保 */

  
  /* 物体の初期化 ... init_shape()関数を使う．第一引数は初期化するshape_t構造体のポインタ．*/
  /* 球の場合：第二引数にST_SHAPEを渡す．この場合，追加で4つの実数を渡す． */
  /*           (※ 以下のようにして必ず実数を渡すこと．間違って整数を渡すとうまく動かない．)*/
  // init_shape(&scene->shapes[2], ST_SPHERE,
	//      40.0, 1.0, -1.0, /* 球の中心位置 */
	//      1.0);          /* 球の半径 */

  init_shape(&scene->shapes[3], ST_SPHERE,
	     -10.0, 3.0, -3.0, /* 球の中心位置 */
	      7.0);          /* 球の半径 */
  
  /* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */

  init_shape(&scene->shapes[0], ST_PLANE,
	     0.0, -2.0, 0.0, //平面が通る点の位置
	     0.0, 1.0, 0.0); //平面の法線ベクトル

  init_shape(&scene->shapes[1], ST_PLANE,
	     0.0, 0.0, 10.0, //平面が通る点の位置
	     0.0, 0.0, 1.0); //平面の法線ベクトル

  // init_shape(&scene->shapes[2], ST_PLANE,
	//      -100.0, 0.0, 0.0, //平面が通る点の位置
	//      1.0, 0.0, 0.0); //平面の法線ベクトル

  /* 補足：vector_t構造体に値を設定する場合は以下のように，SET_VECTORマクロを使うことができる． */
  /* SET_VECTOR(scene->shapes[0].data.sphere.center, 0, 5, 5); */


  init_shape(&scene->shapes[4], ST_CYLINDER,
	     -3.0, 15.0, -15.0, //中心位置
	     5.0, //半径
       10.0); //高さ

  
  /* マテリアルの初期化 ... init_material()関数を使う．*/
  /* 第一引数は初期化するmaterial_t構造体のポインタ． */
  init_material(&scene->shapes[0].material,
		0.69, 0.00, 0.00,  /* 拡散反射係数(RGB) */
		20.0); /* 光沢度 */

  init_material(&scene->shapes[1].material,
		0.00, 0.69, 0.00,  /* 拡散反射係数(RGB) */
		20.0); /* 光沢度 */

  init_material(&scene->shapes[2].material,
  0.00, 0.00, 0.69,  /* 拡散反射係数(RGB) */
  20.0); /* 光沢度 */

  init_material(&scene->shapes[3].material,
  0.69, 0.69, 0.00,  /* 拡散反射係数(RGB) */
  20.0); /* 光沢度 */

  init_material(&scene->shapes[4].material,
  0.69, 0.69, 0.00,  /* 拡散反射係数(RGB) */
  20.0); /* 光沢度 */
  

  init_ambient(&scene->ambient, 0.20,/* 環境光係数(RGB)   */
              255, 255, 255); /* 環境光の強さ */


  init_light(&scene->light, -30.0, 70.0, -50.0, /* 点光源の位置 */
      0.30,/* 鏡面反射率   */
	     255, 255, 255);   /* 点光源の照度(色) */

	init_camera(&scene->camera, 50, 20, -5,//カメラ位置
							-0.92, -0.37, 0.09,//カメラの向き
							179.3);//カメラの視野角
}
