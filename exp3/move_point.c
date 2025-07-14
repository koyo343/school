#include <stdio.h>
#include <windows.h>	// for Sleep
#include <winbase.h>

#define _CRT_SECURE_NO_WARNINGS
#define GNUPLOT_PATH "C:/gnuplot/bin/gnuplot.exe"	// gnuplot.exeの場所

void main(){
	FILE *gp, *fp;
	int i,nod;
	// 初期配置
	double X[9][2] = {{0.0,0.0},{0.1,0.0},{0.2,0.0},
			{0.0,0.1},{0.1,0.1},{0.2,0.1},
			{0.0,0.2},{0.1,0.2},{0.2,0.2}};

	// Animation settings
	// gnuplotを動かすためのコマンド
	if ((gp = _popen(GNUPLOT_PATH, "w")) == NULL) {
		printf("gnuplot open error!!\n");
		exit(EXIT_FAILURE);	// エラーの場合は通常、異常終了する
	}

	// Gnuplot操作
	fprintf(gp, "set term gif animate\n");	// 出力ターミナルをgif, animateオプションを付ける
 	fprintf(gp, "set output 'test.gif'\n");	// 出力ファイル名。


	fprintf(gp, "set size square\n");		// figureを正方形に
	fprintf(gp, "set xrange [%f:%f]\n",0.0,3.0); // 範囲の指定
	fprintf(gp, "set yrange [%f:%f]\n",0.0,3.0);
	fprintf(gp, "unset key\n");		// 凡例を表示しない

	// 点の位置を動かす
	for(i=0;i<30;i++){
		fp = fopen("move_point.dat", "w");	// "上書き"モードでファイルを開く。
		fprintf(gp, "set title 't = %d'\n",i); // タイトルを設定
		for(nod=0;nod<9;nod++){			// 9個の点の位置をファイルに保存
			fprintf(fp,"%f %f\n",X[nod][0],X[nod][1]);	// 点nodの位置をファイルに書き込み
			X[nod][0] += 0.1; X[nod][1] += 0.1;		// 点nodの位置を0.1ずつずらす
		}
		fprintf(gp,"plot 'move_point.dat' w p pt 7 ps 0.5\n");	// gnuplotで点を描く
		fclose(fp);	// 位置を書いているファイルを閉じる
		fflush(gp);	// バッファに格納されているデータを吐き出す（必須）
		Sleep(100);	// なくてもよい。
	}
	system("pause");
	
	fprintf(gp, "exit\n"); // gnuplotの終了
	fflush(gp); // バッファに格納されているデータを吐き出す（必須）
	_pclose(gp);
}