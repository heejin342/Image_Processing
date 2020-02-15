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
//{// GlassFire �˰����� �̿��� �󺧸� �Լ�
//	int cnt = 0;
//	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
//	long k;
//	short curColor = 0, r, c;
//	//	BYTE** CutImage2;
//	Out_Area = 1;
//
//	// �������� ����� �޸� �Ҵ�
//	short* stackx = new short[height*width];
//	short* stacky = new short[height*width];
//	short* coloring = new short[height*width];
//
//	int arr_size = height * width;
//
//	// �󺧸��� �ȼ��� �����ϱ� ���� �޸� �Ҵ�
//
//	for (k = 0; k<height*width; k++) coloring[k] = 0;  // �޸� �ʱ�ȭ
//	for (i = 0; i<height; i++)
//	{
//		index = i * width;
//		for (j = 0; j<width; j++)
//		{
//			// �̹� �湮�� ���̰ų� �ȼ����� 255�� �ƴ϶�� ó�� ����
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
//						//���� �ȼ��� �����踦 ����� ó�� ����
//						if (m<0 || m >= height || n<0 || n >= width) continue;
//
//						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
//						{
//							coloring[index + n] = curColor; // ���� �󺧷� ��ũ
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
//	// ����� ȭ�Ұ����� ����Ǿ��ִµ�, ���� ���� ������ ���� ������ ã�Ƴ��� ����  !!!!!
//	for (i = 1; i <= curColor; i++){
//		if (BlobArea[i] >= BlobArea[Out_Area]) Out_Area = i;
//	}
//	// CutImage �迭 Ŭ����~
//	for (k = 0; k < width*height; k++) CutImage[k] = 255;
//
//	// coloring�� ����� �󺧸� ����� (Out_Area�� �����) ������ ���� ū �͸� CutImage�� ����
//	for (k = 0; k < width*height; k++){
//		if (coloring[k] == Out_Area) {
//			CutImage[k] = 0;  // ���� ū �͸� ����
//		}
//	}
//	delete[] coloring;
//	delete[] stackx;
//	delete[] stacky;
//	
//}// �󺧸� �� ���� ���� ������ ���ؼ��� �̾Ƴ��� �ڵ� ����
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
//	//ó��
//	int cnt = 0;
//	int X_sum = 0;
//	int Y_sum = 0;
//	int middleX = 0;
//	int middleY = 0;
//
//	Binarization(Image, Output, 50, W, H);
//	for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   
//	m_BlobColoring(Output, H, W);          //�̰��ؾ��� ������ ������ ���� ���� �� ���� �� �ְ� �Ǵ°���    
//	//�ƿ�ǲ���� ���������� ����. �׷��� �̰͸� ����� �� input�� �ٲ���� ����� �� �� �ִ�.
//	
//	//CutImage[k] ���⿡ ������ ���׶���� ��ġ���� ����Ǿ�����. �츮�� �� ���׶�̿� �ش�Ǵ� ȭ�ҵ��� ��ǥ���� �޾ƾ���
//	//�����߽��� ���ϱ� ���� ��ǥ������ �� ���ؼ� ����� ����.
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
//	//��ºκ�
//	fp = fopen("�ϼ�pupli�����⿵��1.bmp", "wb");
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
////����
////����ȭ�ؼ� ������ ���ߴµ�, �� ���׶���� �����߽��� ���ؼ� ��� ���� ���� ���� ������ �ִ� ȭ���� x�� x ��ǥ���� 
////�� ���ϰ�, y�� y ��ǥ���� �ٴ��ؼ� �װ� ������ ������ �����߽���
////�����߽� ������ ���� ����ȯ ���Ѽ� ������ 
////�� ���� ���� �Ͼ�� ũ�ν� ǥ�ø� ��
////��������� �Ҷ��� �̷��� ���������� �ι�Ʈ ��Ų������ �󺧸��ؾ���
////for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   //��溸�� ������ ��ο� �� �����
////�󺧸� �Լ��� ������ 255, ����� 0�϶� ����� �����ϴ°���
////������ �����ε����� ��溸�� ��Ƽ� ����� �۵��ߴµ�, ������ ������ ��������Ѵ�. �����ڰ� ��Ӱŵ�