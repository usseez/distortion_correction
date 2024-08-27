/*
광각 이미지에 대하여 왜곡 보정을 한다
*/

#include "../include/distortioncorrection.h"
#include <stdio.h>

//brown model
//parameter obtained by calibration
double k1 = -0.366, k2 = 0.215, k3 = 0.080;
double fx = 357.57, fy = 357.00;
double cx = 320.29, cy = 223.87;
double p1 = 0.0016, p2 = 0.0004;

void normalize(double x , double y , double *x_n, double *y_n);
void denormalize(double x , double y, int *x_p, int *y_p);
void distort_normal(double x, double y, double *x_d, double *y_d);
void create_image(unsigned char* inputimage, unsigned char* outimage,
                         int x, int y, int x_pd, int y_pd);

void distortion_correction(unsigned char* inputimage, unsigned char* outimage)
{
    
    double y_nu, x_nu;      //_nu : 왜곡x파라미터x
    double y_pu, x_pu;      //_pu : 왜곡x파라미터o
    double x_nd, y_nd;      //_nd : 왜곡o파라미터x
    int x_pd, y_pd;      //_pd : 왜곡o파라미터o


    #if 1
    for (int y = 0; y < IMAGEHEIGHT; y++) 
    {
        for (int x = 0; x < IMAGEWIDTH; x++) 
        {
        

            normalize(x, y, &x_nu, &y_nu);

            distort_normal(x_nu, y_nu, &x_nd, &y_nd);

            denormalize(x_nd, y_nd, &x_pd, &y_pd);
            create_image(inputimage, outimage,
                         x, y, x_pd, y_pd);

        
            
            #if 0
            if(y == 0)
                printf("x: %f, y: %f \t x_pd : %f, y_pd : %f\tx_nd : %d, y_nd : %d\tx_nu : %d, y_nu : %d\n", x, y, x_pd, y_pd, x_nd, y_nd, x_nu, y_nu);
            //int pixel = x_pu + y_pu * IMAGEHEIGHT;

            #endif

 
        }
    }

    #endif



}

void normalize(double x , double y , double *x_nu, double *y_nu)
{

    *y_nu = (y - cy) / fy;
    *x_nu = (x - cx) / fx;
}
void denormalize(double x , double y, int *x_p, int *y_p)
{
    *x_p = (int)(fx * x + cx);//skew_c 생략
    *y_p = (int)(fy * y + cy);//최종적으로 왜곡된 영상에서의 좌표를 구할 수 있음

}

void distort_normal(double x , double y, double *x_d, double *y_d)
{

    double ru2 = x * x + y * y; //ru2 = ru * ru, ru : 왜곡이 없을 때 중심까지 거리
    double radial_d = 1 + k1 * ru2 + k2 * ru2 * ru2 + k3 * ru2 * ru2 * ru2;
    
    //double radial_d = 1 + k1 * ru2 + k2 * ru2 * ru2 + k3 * ru2 * ru2 * ru2;
    *x_d = radial_d * x + 2 * p1 * x * y + p2 * (ru2 + 2 * x * x);
    *y_d = radial_d * y + p1*(ru2 + 2 * y * y) + 2 * p2 * x * y;

    
}

void create_image(unsigned char* inputimage, unsigned char* outimage,
                         int x, int y, int x_pd, int y_pd)
{
    if (x_pd >= 0 && x_pd < IMAGEWIDTH && y_pd >= 0 && y_pd < IMAGEHEIGHT) 
        {
           outimage[y * IMAGEWIDTH + x] = inputimage[y_pd * IMAGEWIDTH + x_pd];
        } 
        else 
        {
            outimage[y * IMAGEWIDTH + x] = 0; // 경계 밖의 값은 검정색으로 설정
        }
}