#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "../incs/vector_utils.h"
#include "../incs/raytracing.h"

void scene_setting(scene_t *scene)
{
  /* ************************************************** */
  /* 物体の設定                                         */
  /* ************************************************** */
  scene->num_shapes_capacity = 16; /* 物体リストの最大格納数(自由に変更して良い) */
  
  scene->shapes = malloc(sizeof(shape_t) * scene->num_shapes_capacity); /* メモリ確保 */

  
  /* 物体の初期化 ... init_shape()関数を使う．第一引数は初期化するshape_t構造体のポインタ．*/
  /* 球の場合：第二引数にST_SHAPEを渡す．この場合，追加で4つの実数を渡す． */
  /*           (※ 以下のようにして必ず実数を渡すこと．間違って整数を渡すとうまく動かない．)*/
  init_shape(&scene->shapes[0], ST_SPHERE,
	     -0.25, -0.5, 3.0, /* 球の中心位置 */
	     0.5);          /* 球の半径 */
  
  /* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */
  
  init_shape(&scene->shapes[1], ST_PLANE,
	     0.0, -1.0, 0.0, //平面が通る点の位置
	     0.0, 1.0, 0.0); //平面の法線ベクトル
  init_shape(&scene->shapes[2], ST_PLANE,
	     0.0, 1.0, 0.0, //平面が通る点の位置
	     0.0, -1.0, 0.0); //平面の法線ベクトル 
  init_shape(&scene->shapes[3], ST_PLANE,
	     1.0, 0.0, 0.0, //平面が通る点の位置
	     -1.0, 0.0, 0.0); //平面の法線ベクトル
  init_shape(&scene->shapes[4], ST_PLANE,
	     -1.0, 0.0, 0.0, //平面が通る点の位置
	     1.0, 0.0, 0.0); //平面の法線ベクトル
  init_shape(&scene->shapes[5], ST_PLANE,
	     0.0, 0.0, 5.0, //平面が通る点の位置
	     0.0, 0.0, -1.0); //平面の法線ベクトル
  /* 補足：vector_t構造体に値を設定する場合は以下のように，SET_VECTORマクロを使うことができる． */
  /* SET_VECTOR(scene->shapes[0].data.sphere.center, 0, 5, 5); */


  
  /* マテリアルの初期化 ... init_material()関数を使う．*/
  /* 第一引数は初期化するmaterial_t構造体のポインタ． */
  init_material(&scene->shapes[0].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		0.0, 0.0, 0.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		8.0,               /* 光沢度 */
    MT_PERFECT_REF,    /*質感*/
    1.0, 1.0, 1.0);     /*鏡面反射係数*/

    init_material(&scene->shapes[1].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		1.0, 1.0, 1.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		0.0,               /* 光沢度 */
    MT_DEFAULT,    /*質感*/
    0, 0, 0);     /*鏡面反射係数*/

    init_material(&scene->shapes[2].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		1.0, 1.0, 1.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		0.0,               /* 光沢度 */
    MT_DEFAULT,    /*質感*/
    0, 0, 0);     /*鏡面反射係数*/

    init_material(&scene->shapes[3].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		0.0, 1.0, 0.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		0.0,               /* 光沢度 */
    MT_DEFAULT,    /*質感*/
    0, 0, 0);     /*鏡面反射係数*/

    init_material(&scene->shapes[4].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		1.0, 0.0, 0.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		0.0,               /* 光沢度 */
    MT_DEFAULT,    /*質感*/
    0, 0, 0);     /*鏡面反射係数*/

    init_material(&scene->shapes[5].material,
		0.0, 0.0, 0.0,  /* 環境光係数(RGB)   */
		1.0, 1.0, 1.0,  /* 拡散反射係数(RGB) */
		0.0, 0.0, 0.0,  /* 鏡面反射率(RGB)   */
		0.0,               /* 光沢度 */
    MT_DEFAULT,    /*質感*/
    0, 0, 0);     /*鏡面反射係数*/
  scene->num_shapes = 6; /* 物体リストに，実際に格納した物体の数 */
                         /* 物体数を変えた場合はそれに合わせて書き換えること． */
                         /* 物体リストの先頭 num_shapes 個は初期化されている必要がある． */
  /* ************************************************** */
  
  /* ************************************************** */
  /* 光源の設定                                         */
  /* ************************************************** */
  /* 環境光の強さ */
  /* colorf_t構造体に値を設定する場合は，このように SET_COLORマクロを使うことができる． */
  SET_COLOR(scene->ambient_illuminance, 0.1, 0.1, 0.1);
  
  scene->num_lights_capacity = 16; /* 光源リストの最大格納数(自由に変更して良い) */
  scene->lights = malloc(sizeof(light_t) * scene->num_lights_capacity); /* メモリ確保 */

  /* 光源の初期化 ... init_light()関数を使う． 第一引数は初期化するlight_t構造体のポインタ．*/

  /* 点光源の場合 */
  init_light(&scene->lights[0], LT_POINT,
	     0.0, 0.9, 2.5, /* 点光源の位置 */
	     1.0, 1.0, 1.0);   /* 点光源の照度(色) */

  /* 平行光源の場合 */
  /*
  init_light(&scene->lights[0], LT_DIRECTIONAL,
	     0.0, -1.0, 0.0,  平行光源の方向ベクトル
	     1.0, 1.0, 1.0);  平行光源の照度(色)
  */
  
  scene->num_lights = 1; /* 光源リストに，実際に格納した光源の数 */
                         /* 光源数を変えた場合はそれに合わせて書き換えること． */
                         /* 光源リストの先頭 num_lights 個は初期化されている必要がある． */
  /* ************************************************** */
}

