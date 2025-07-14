#define _CRT_SECURE_NO_WARNINGS //gnuplotを使うための記述

#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <math.h>

#define GNUPLOT_PATH "C:/\"Program Files\"/gnuplot/bin/gnuplot.exe" //gnuplotの場所

typedef struct dot{
    double x;
    double y;
    double v_x;
    double v_y;
} POINT1;

int main(void)
{
    FILE *fp, *gp;
	int i, j, k, nod, count;
	double x_val, y_val, v_val, x_val2, y_val2;
	
    fp = fopen("test.txt", "w");

    POINT1 plot[10] = {{6.0, 2.0, 0, 1},
                      {12.0, 2.0, 1*cos(45*M_PI/180), 1*sin(45*M_PI/180)},
                      {18.0, 2.0, 1*cos(135*M_PI/180), 1*sin(135*M_PI/180)},
                      {2.0, 4.0, 1*cos(45*M_PI/180), 1*sin(45*M_PI/180)}, 
                      {10.0, 6.0, 1*cos(135*M_PI/180), 1*sin(135*M_PI/180)}, 
                      {4.0, 8.0, 1*cos(45*M_PI/180), 1*sin(45*M_PI/180)}, 
                      {16.0, 8.0, 1*cos(135*M_PI/180), 1*sin(135*M_PI/180)},
                      {10.0, 10.0, 0, 1},
                      {14.0, 12.0, 1*cos(45*M_PI/180), 1*sin(45*M_PI/180)}, 
                      {8.0, 14.0, 1*cos(135*M_PI/180), 1*sin(135*M_PI/180)}};       //10点目

    if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) 
    {
	printf("gnuplot open error!!\n");
	exit(EXIT_FAILURE);	// エラーの場合は通常、異常終了する
    }

    // Gnuplot操作
    fprintf(gp, "set size square \n");		// figureを円に
    fprintf(gp, "set xrange [%f:%f]\n",-10.0,30.0); // 範囲の指定
    fprintf(gp, "set yrange [%f:%f]\n",-20.0,20.0);
    fprintf(gp, "unset key\n");		// 凡例を表示しない
	fprintf(gp, "set term gif animate\n");
    fprintf(gp, "set output 'test.gif'\n");
    
    Sleep(1000);
    
    // 点の位置を動かす
    for(i=0;i<50;i++)
    {
	    fp = fopen("move_point.dat","w");	// "上書き"モードでファイルを開く。
	    fprintf(gp, "set title 't = %d'\n",i); // タイトルを設定
	    for(nod=0;nod<10;nod++)
        {	
			//10個の点の位置をファイルに保存
			fprintf(fp,"%f, %f\n",plot[nod].x, plot[nod].y);	// 点nodの位置をファイルに書き込み
		}
		
		
		//群として動かす条件
		for(j = 0; j < 10 ; j++)
		{		
			x_val = 0;
			y_val = 0;
			v_val = 0;
			x_val2 = 0;
			y_val2 = 0;
			count = 0;
			
			//分離
			for(k = 0; k < 10; k++)
			{
				if(((sqrt(pow((plot[j].x - plot[k].x), 2) + pow((plot[j].y - plot[k].y), 2))) <= 2.0) && j != k)
				{
					x_val = (-1) * plot[j].v_x;
					y_val = (-1) * plot[j].v_y;
					
					break;
				}
			}
				
			//整列
			for(k = 0; k < 10; k++)
			{
				if(((sqrt(pow((plot[j].x - plot[k].x), 2) + pow((plot[j].y - plot[k].y), 2))) <= 4.0) && j != k)
				{
					x_val += plot[k].v_x;
					y_val += plot[k].v_y;
				}
			}
								
			//団結(場所を足す)
			for(k = 0; k < 10; k++)
			{
				if(((sqrt(pow((plot[j].x - plot[k].x), 2) + pow((plot[j].y - plot[k].y), 2))) <= 7.0) && j != k)
				{
					x_val2 += plot[k].x;
					y_val2 += plot[k].y;
					
					count++;
				}
			}
				
			x_val += ((x_val2 / (double)count) - plot[j].x);
			y_val += ((y_val2 / (double)count) - plot[j].y);	
			v_val = sqrt(pow(x_val, 2) + pow(y_val, 2));
			
			if(v_val >= 1.0 || v_val <= -1.0)
			{
				plot[j].x += x_val / v_val;
				plot[j].y += y_val / v_val;
				
				plot[j].v_x = x_val / v_val;
				plot[j].v_y = y_val / v_val;
				fprintf(stderr, "%d, %f,%f,%f,%f,%f\n",j,  x_val/v_val, y_val/v_val, v_val/v_val, plot[j].x, plot[j].y);
			}
			else
			{
				plot[j].x += x_val;
				plot[j].y += y_val;
				plot[j].v_x = x_val;
				plot[j].v_y = y_val;
				fprintf(stderr, "%d, %f,%f,%f,%f,%f\n",j,  x_val, y_val, v_val, x_val2/count, y_val2/count);
			}	
		}
	    
        fprintf(gp,"plot 'move_point.dat' w p pt 7 ps 0.5\n");	// gnuplotで点を描く
	    fclose(fp);	// 位置を書いているファイルを閉じる
	    fflush(gp);	// バッファに格納されているデータを吐き出す（必須）
	    Sleep(1000);	// なくてもよい。
	}

    return 0;
}