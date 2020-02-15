#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3

void swap(BYTE *a, BYTE *b) {
	BYTE temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	RGBQUAD	hRGB[256];
	FILE *fp;
	fp = fopen("LENNA.bmp", "rb");
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
	fread(hRGB, sizeof(RGBQUAD), 256, fp);
	int ImgSize = hInfo.biWidth * hInfo.biHeight;
	BYTE * Image = (BYTE *)malloc(ImgSize);
	BYTE * Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);
	int W = hInfo.biWidth;
	int H = hInfo.biHeight;
	fclose(fp);

	/*for (int i = 0; i < H / 2; i++) {
		for (int j = 0; j < W; j++) {
			swap(&Output[i*W + j], &Output[(H - i - 1)*W + j]);
		}
	}*/
	
	//순방향 이동 ,Translation
	/*int Tx = 30;
	int Ty = 20;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (i + Ty >= 0 && i + Ty<H && j + Tx >= 0 && j + Tx < W)
				Output[(i + Ty)*W + (j + Tx)] = Image[i*W + j];
		}
	}*///역방향계산을 하거나, 이렇게하고싶으면 클리핑처리 해줘야함 . 근데 이건 그냥 단순히 더해주면 되기 때문에 홀은 생기지 않을 것임
	

	/*
	//역방향 이동 ,Translation
	int Tx = 30;
	int Ty = 20;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
		if (i + Ty >= 0 && i + Ty<H && j + Tx >= 0 && j + Tx < W)
			Output[i*W +j] = Image[(i + Ty)*W + (j + Tx)];
		}
	}//역방향계산을 하거나, 이렇게하고싶으면 클리핑처리 해줘야함
	*/




	
	//스케일 -> 순방향 
	//int TmpX, TmpY;
	//double Sx = 1.5;//이때 벗어날 수 있음
	//double Sy = 1.5;//가로방향 확대, 세로방향 축소.
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		TmpX = j * Sx;							
	//		TmpY = i * Sy;							
	//		if (TmpY<H && TmpX < W)      //얘는 0보다 작아지는 일은 없으니까 이렇게만 클리핑처리
	//			Output[TmpY*W + TmpX] = Image[i*W + j];              
	//		}
	//}   //결과로 홀이생김. 가로방향으로 확대가 되면서 홀이 생기는거임. 홀이생기는패턴은 거의 일정함 -> 역방향 사상이 필요하다.
	//역방향으로하면 30도 반시계반향의 인버스 연산인 시계방향 30도 돌리면 된다
	


	//스케일 -> 역방향
	int TmpX, TmpY;
	double Sx = 1.5;//이때 벗어날 수 있음
	double Sy = 1.5;//가로방향 확대, 세로방향 축소.
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			TmpX = j / Sx;
			TmpY = i / Sy;							
			if (TmpY < H && TmpX < W)      
				Output[i*W + j] = Image[TmpY*W + TmpX];
		}
	}
	

	//회전  -> 순방향
	//int angle = 30;
	//double Theta = angle * 3.141592 / 180.0;           //degree 를 radian 으로변화한거임
	//int TmpX, TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {  //엑스좌표가 j 인거임
	//		TmpX = j * cos(Theta) - i * sin(Theta);
	//		TmpY = j * sin(Theta) + i * cos(Theta);
	//		if (TmpX >= 0 && TmpX < H && TmpY >= 0 && TmpY < W)
	//			Output[TmpY*W + TmpX] = Image[i*W + j];
	//		}
	//}   //이렇게하면 30도만큼 회전 . 0.0가 붙어이음. 위아래 뒤집혀있다는게 맞는가봄
	//땡땡이 홀이 생겨서 역방향사상으로 해야한다. 결국 이동한 결과인 X' Y'에 코싸인행렬의 인버스 행렬을 곱해주면 원래 좌표가 나옴
	//즉, 30도만큼 반시계시키는 행렬의 역행렬을 구해서 곱하면 원래 행렬을 만들어 준다. 원상복귀 시키는 역할인거

	
	//영상의 위아래를 뒤집을게 . 이렇게 하면 밑이 붙어있는게 아니라 위에가 붙어있게 된다.
	for (int i = 0; i < H / 2; i++) {
		for (int j = 0; j < W; j++) {
			swap(&Output[i*W + j], &Output[(H - i - 1)*W + j]);
		}
	}

	/*for (int i = 0; i < W; i++) {
		for (int j = 0; j < H/2; j++) {
			swap(&Output[i*W + j], &Output[(W*i)-1-j]);
		}
	}*/


	//회전  -> 역방향
	/*int angle = 180;
	double Theta = angle * 3.141592 / 180.0;
	int TmpX, TmpY;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			TmpX = j * cos(Theta) + i * sin(Theta);
			TmpY = -j * sin(Theta) + i * cos(Theta);
			if (TmpX >= 0 &&  TmpY < H && TmpY >= 0 && TmpX < W)
				Output[i*W +j] = Image[TmpY*W + TmpX];
		}
	} */  
	//이렇게하면 30도만큼 회전 . 0.0가 붙어이음. 위아래 뒤집혀있다는게 맞는가봄
	//땡땡이 홀이 생겨서 역방향사상으로 해야한다. 결국 이동한 결과인 X' Y'에 코싸인행렬의 인버스 행렬을 곱해주면 원래 좌표가 나옴
	//즉, 30도만큼 반시계시키는 행렬의 역행렬을 구해서 곱하면 원래 행렬을 만들어 준다. 원상복귀 시키는 역할인거
	//이게 역방향 사상임

	//원점이 중심이 아닌, 센터의 중심으로 한거임 Cx,Cy값이 회전의 중심축이 된다. 
	//int angle = 30;
	//double Theta = angle * 3.141592 / 180.0;
	//int Cx =  50;
	//int Cy = 50;    //이게 회전축의 중심이다.
	//int TmpX;
	//int TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j = 0; j < W; j++) {
	//		TmpX = cos(Theta)*(j - Cx) + sin(Theta)*(i - Cy) + Cx;
	//		TmpY = -sin(Theta)*(j - Cx) + cos(Theta)*(i - Cy) + Cy;
	//		if (TmpX >= 0 && TmpY < H && TmpY >= 0 && TmpX < W)
	//			Output[i*W + j] = Image[TmpY*W + TmpX];
	//	}
	//}

	//쉬어링  -> 순방향  . 근데 이건 홀문제 생기지 않았지만 또해줘.
	//double Shx = 0;
	//double Shy = 0.3;  //좌우에 마주보고 있는 변들이 뒤틀어진다. 
	//int TmpX, TmpY;
	//for (int i = 0; i < H; i++) {
	//	for (int j =0; j < W; j++) {
	//		TmpX = j + Shx*i ;
	//		TmpY = Shy*j + i;
	//		if (TmpX >= 0 && TmpY < H && TmpY >= 0 && TmpX < W)
	//			Output[TmpY*W + TmpX] = Image[i*W + j];
	//		}
	//}
	
	//네가지기하변환중, 회전이나 스케일링 업은 홀때문에 역방향 사상으로 구현했자나
	//순방향으로 스케일링 업이나 회전하는 경우에 해결방법이 두가지있음. 하나는 역방향사상. 하나는 보간법으로채움. 가까운화소값을 채우거나 리니어하게
	//보간법은 따로 구현 안했다 수업시간에 충분히 할 수 있음. 하지만 시험범위임 ㅠ

	
	
	
	
	
	
	
	
	
	//직사각형 모양이였던 레나영상이 위아래가 디틀어져서 평행사변형이된다.
	//Shy가 0.3이고, 앞에께 0이면 좌우가 마주보던 변들이 비틀어진다.
	//이거 역방향으로 해봐
	//앞에꺼(스케일링업, 로테이션)들은 홀문제때문에 역방향사상으로 했는데 이건 큰 문제없어서 안해본거임
	//홀이생기면 보간법으로 채우거나(가까운거로 채우기, 리니어) 역방향으로 구현
	//시험범위 7-2까지



	

	

	fp = fopen("ghghghghmoving1.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
	fwrite(Output, sizeof(BYTE), ImgSize, fp);
	fclose(fp);
	free(Image);
	free(Output);

	return 0;
}




