//#include <stdio.h>
//#include <Math.h>
//#include <stdlib.h>       
//#include <Windows.h>       
//#pragma warning (disable:4996) 
//#define SIZE 3
//
//void swap(BYTE *a, BYTE *b) {   
//	BYTE temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//void Sorting(BYTE * Arr) {
//	for (int i = 0; i < 8; i++) {
//		for (int j = i + 1; j < 9; j++) {
//			if (Arr[i] > Arr[j]) swap(&Arr[i], &Arr[j]);
//		}
//	}
//}
//BYTE Median(BYTE * arr) {
//	Sorting(arr);
//	return arr[4];
//}
//void Binarization(BYTE * Input, BYTE * Output, int Th, int W, int H){
//	int Size = W * H;
//	for (int i = 0; i < Size; i++)
//	{
//		if (Input[i] > Th) Output[i] = 255;
//		else Output[i] = 0;
//	}
//}
//int push(short *stackx, short *stacky, int arr_size, short vx, short vy, int *top){
//	if (*top >= arr_size) return(-1);
//	(*top)++;
//	stackx[*top] = vx;
//	stacky[*top] = vy;
//	return(1);
//}
//int pop(short *stackx, short *stacky, short *vx, short *vy, int *top){
//	if (*top == 0) return(-1);
//	*vx = stackx[*top];
//	*vy = stacky[*top];
//	(*top)--;
//	return(1);
//}
//void m_BlobColoring(BYTE* CutImage, int height, int width)
//{// GlassFire 알고리즘을 이용한 라벨링 함수
//	int cnt = 0;
//	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
//	long k;
//	short curColor = 0, r, c;
//	//	BYTE** CutImage2;
//	Out_Area = 1;
//
//	// 스택으로 사용할 메모리 할당
//	short* stackx = new short[height*width];
//	short* stacky = new short[height*width];
//	short* coloring = new short[height*width];
//
//	int arr_size = height * width;
//
//	// 라벨링된 픽셀을 저장하기 위해 메모리 할당
//
//	for (k = 0; k<height*width; k++) coloring[k] = 0;  // 메모리 초기화
//	for (i = 0; i<height; i++)
//	{
//		index = i * width;
//		for (j = 0; j<width; j++)
//		{
//			// 이미 방문한 점이거나 픽셀값이 255가 아니라면 처리 안함
//			if (coloring[index + j] != 0 || CutImage[index + j] != 255) continue;
//			r = i; c = j; top = 0; area = 1;
//			curColor++;
//			while (1)
//			{
//			GRASSFIRE:
//				for (m = r - 1; m <= r + 1; m++)
//				{
//					index = m * width;
//					for (n = c - 1; n <= c + 1; n++)
//					{
//						//관심 픽셀이 영상경계를 벗어나면 처리 안함
//						if (m<0 || m >= height || n<0 || n >= width) continue;
//
//						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
//						{
//							coloring[index + n] = curColor; // 현재 라벨로 마크
//							if (push(stackx, stacky, arr_size, (short)m, (short)n, &top) == -1) continue;
//							r = m; c = n; area++;
//							goto GRASSFIRE;
//						}
//					}
//				}
//				if (pop(stackx, stacky, &r, &c, &top) == -1) break;
//			}
//			if (curColor<1000) BlobArea[curColor] = area;
//		}
//	}
//	float grayGap = 255.0f / (float)curColor;
//
//	// 덩어리의 화소값들이 저장되어있는데, 그중 가장 면적이 넓은 영역을 찾아내기 위함  !!!!!
//	for (i = 1; i <= curColor; i++){
//		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
//	}
//	// CutImage 배열 클리어~
//	for (k = 0; k < width*height; k++) CutImage[k] = 255;
//
//	// coloring에 저장된 라벨링 결과중 (Out_Area에 저장된) 영역이 가장 큰 것만 CutImage에 저장
//	for (k = 0; k < width*height; k++){
//		if (coloring[k] == Out_Area) {
//			CutImage[k] = 0;  // 가장 큰 것만 저장
//		}
//	}
//	delete[] coloring;
//	delete[] stackx;
//	delete[] stacky;
//	
//}// 라벨링 후 가장 넓은 영역에 대해서만 뽑아내는 코드 포함
//
//int main() {
//	BITMAPFILEHEADER hf;
//	BITMAPINFOHEADER hInfo;
//	RGBQUAD	hRGB[256];
//	FILE *fp;
//	fp = fopen("pupil1.bmp", "rb");
//	if (fp == NULL) return 0;
//	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
//	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
//	fread(hRGB, sizeof(RGBQUAD), 256, fp);
//	int ImgSize = hInfo.biWidth * hInfo.biHeight;
//	BYTE * Image = (BYTE *)malloc(ImgSize);
//	BYTE * Output = (BYTE *)malloc(ImgSize);
//	BYTE * newOutput = (BYTE *)malloc(ImgSize);
//	BYTE * Y_witch = (BYTE *)malloc(ImgSize);
//	BYTE * X_witch = (BYTE *)malloc(ImgSize);
//	fread(Image, sizeof(BYTE), ImgSize, fp);
//	int W = hInfo.biWidth;
//	int H = hInfo.biHeight;
//	fclose(fp);
//
//	//처리
//	int cnt = 0;
//	int X_sum = 0;
//	int Y_sum = 0;
//	int middleX = 0;
//	int middleY = 0;
//
//	Binarization(Image, Output, 50, W, H);
//	for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   
//	m_BlobColoring(Output, H, W);          //이걸해야지 영상의 영역이 가장 넓은 걸 볼수 가 있게 되는거임    
//	//아웃풋에는 이진연산이 들어간다. 그래서 이것만 출력할 때 input을 바꿔줘야 결과를 볼 수 있다.
//	
//	//CutImage[k] 여기에 검정색 동그라미의 위치값이 저장되어있음. 우리는 그 동그라미에 해당되는 화소들의 좌표값을 받아야해
//	//무게중심을 구하기 위해 좌표값끼리 다 더해서 평균을 낸다.
//
//	for (int i = 0; i < H*W; i++) {
//		if (Output[i] == 0) {
//			X_witch[i] = i % W;
//			X_sum += X_witch[i];
//
//			Y_witch[i] = i / W;
//			Y_sum += Y_witch[i];
//			cnt++;
//		}
//	}
//
//	middleX = X_sum / cnt;
//	middleY = Y_sum / cnt;
//
//	for (int i = 0; i < H*W; i++) {
//		newOutput[i] = Image[i];
//	}
//
//	for (int i = 0; i < W*H; i++) {
//		if (i % W == middleX || i / W == middleY)
//			newOutput[i] = 255;
//
//	}
//
//	//출력부분
//	fp = fopen("완성pupli경계검출영상1.bmp", "wb");
//	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
//	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
//	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
//	fwrite(newOutput, sizeof(BYTE), ImgSize, fp);    
//	fclose(fp);
//	free(Image);
//	free(Output);
//	free(newOutput);
//	free(Y_witch);
//	free(X_witch);
//	return 0;
//}
//
//
////과제
////이진화해서 동공을 구했는데, 그 동그라미의 무게중심을 구해서 까만색 으로 나온 애의 영역에 있는 화소중 x는 x 좌표끼리 
////다 더하고, y는 y 좌표끼리 다더해서 그걸 개수로 나누면 무게중심임
////무게중심 정수로 강제 형변환 시켜서 나오게 
////눈 원래 영상에 하얀색 크로스 표시를 해
////동전영상로 할때는 이렇게 이진영상을 인버트 시킨다음에 라벨링해야함
////for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   //배경보다 전경이 어두울 때 사용함
////라벨링 함수는 전경이 255, 배경이 0일때 제대로 동작하는거임
////동전은 전경인동전이 배경보다 밝아서 제대로 작동했는데, 눈동자 영상은 뒤집어야한다. 눈동자가 어둡거든