//#include <stdio.h>
//#include <Math.h>
//#include <stdlib.h>       
//#include <Windows.h>       
//#pragma warning (disable:4996) 
//#define SIZE 3
//
//void Erosion(BYTE *Img, BYTE *Out, int W, int H) {
//	전경화소이면 검사. 주변화소들이 모두 전경이면 놔두고 ,하나라도 배경이면 전경을 배경으로 바꾼다,
//	for (int i = 1; i < H ; i++) {
//		for (int j = 1; j < W ; j++) {  //전경이라면
//			if (Img[i*W + j] == 255) {
//				if (!(Img[(i - 1)*W + j] == 255 && Img[(i + 1)*W + j] == 255 && Img[i*W + (j + 1)] == 255 && Img[i*W + (j - 1)] == 255))
//				{
//					Out[i*W + j] = 0;
//				}
//				else {
//					Out[i*W + j] = 255;
//				}
//			}
//			else {
//				Out[i*W + j] = 0;
//			}
//
//
//		}
//	}
//
//}
//void Dilation(BYTE *Img, BYTE *Out, int W, int H) {  //이거 팽창
//	전경화소이면 검사. 주변화소들이 모두 전경이면 놔두고 ,하나라도 배경이면 전경을 배경으로 바꾼다,
//	for (int i = 1; i < H ; i++) {
//		for (int j = 1; j < W ; j++) {  //배경인데, 주변화소들 중 적어도 하나가 전경이면 배경을 전경으로 바꾼다 ㅇㅇ
//			if (Img[i*W + j] == 0) {
//				if (Img[(i - 1)*W + j] == 255 || Img[(i + 1)*W + j] == 255 || Img[i*W + (j + 1)] == 255 || Img[i*W + (j - 1)] == 255)
//				{
//				Out[i*W + j] = 255;
//				}
//				else { //전경이라면
//					Out[i*W + j] = 0;
//				}
//			}
//			else
//				Out[i*W + j] = 255;
//
//		}
//	}
//
//}
//int main() {
//	BITMAPFILEHEADER hf;
//	BITMAPINFOHEADER hInfo;
//	RGBQUAD	hRGB[256];
//	FILE *fp;
//	fp = fopen("dilation.bmp", "rb");
//	if (fp == NULL) return 0;
//	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);
//	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);
//	int ImgSize = hInfo.biWidth * hInfo.biHeight;
//	BYTE *Image;
//	BYTE * Output;
//	if (hInfo.biBitCount == 8) {  //8이면 인덱스컬러
//		fread(hRGB, sizeof(RGBQUAD), 256, fp);	//팔레트는 그레이 영상일 떄만 있음
//		Image = (BYTE *)malloc(ImgSize);
//		Output = (BYTE *)malloc(ImgSize);
//		fread(Image, sizeof(BYTE), ImgSize, fp);
//	}
//	else {   //24이면 트루컬러
//		Image = (BYTE *)malloc(ImgSize * 3);
//		Output = (BYTE *)malloc(ImgSize * 3);
//		fread(Image, sizeof(BYTE), ImgSize * 3, fp);
//	}
//	int W = hInfo.biWidth;
//	int H = hInfo.biHeight;
//	fclose(fp);
//
//	
//
//
//
//
//
//
//
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++)Image[i] = Output[i];
//	Erosion(Image, Output, W, H);
//
//	Dilation(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++) Image[i] = Output[i];
//	Dilation(Image, Output, W, H);
//	for (int i = 0; i < ImgSize; i++) Image[i] = Output[i];
//	Erosion(Image, Output, W, H);  // 팽창(떨어져 있던걸 붙여주고)후 침식 -> 클로징
//	Erosion(Image, Output, W, H);
//
//	2번 파일을 침식 두번 팽창 두번 하면 부분이 매끄러워진다 하지만 점같은게 생겨버림
//
//	
//
//
//
//
//	트루컬러 영상은 그레이와 다르게 팔레트 정보가없고, bgr로 역순으로 들어간다. 
//
//	fp = fopen("190614_Dilation.bmp", "wb");
//	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);
//	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
//	if (hInfo.biBitCount == 8) {
//		fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);
//		fwrite(Output, sizeof(BYTE), ImgSize, fp);
//	}
//	else {
//		fwrite(Output, sizeof(BYTE), ImgSize * 3, fp);
//	}
//	fclose(fp);
//	free(Image);
//	free(Output);
//
//
//	int a;
//	scanf_s("%s", &a);
//
//	return 0;
//}
//
//물 ,, 과학적인 상식에 관한 이슈들에 대한 의견 
//찬반토론에 관한 자료 올라와있음
//찬반토론했던거 주제의 의미 어캐 원자력 발전을 하는지?
//자신이 하지않은 찬반토론에 관해 나의 의견
//9시 시험
//**기말고사를 위한 피드백
//
//1. 강의자료(ppt file)를 위주로 준비
//
//- 생활 속에 필요한 물을 포함한 과학적인 상식(이론)
//
//- 수업시간에 같이 생각해본 사회적인 이슈들에 대한 본인의 의견
//
//
//
//2. E - campus에 공람될 조별 찬반토론자료
//
//- 찬반토론 주제에 대한 발표된 과학적 상식
//
//- 본인이 참여하지 않은 찬반토론의 주제에 대한 본인의 타당한 의견
//
//
//
//
