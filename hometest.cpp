//이거 출력해야해 !!!!!!!!!!!!!!!!!!!


#include <stdio.h>
#include <Math.h>
#include <stdlib.h>       
#include <Windows.h>       
#pragma warning (disable:4996) 
#define SIZE 3

void swap(BYTE *a, BYTE *b) {   //스왑만해주는 함수
	BYTE temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
//소팅을 내림차순해도된다. 새까만 페퍼노이즈는 미디엄필터보다 맥스필터를 이용하는게 좋고, 솔트노이즈만 있다면 민필터를 써서 많은 노이즈중에 제일작은 하얀색만 걸러낼 수 있게끔하면 노이즈가 많이 사라진것처럼 느낄 수있음 
void Sorting(BYTE * Arr) { 
	for (int i = 0; i < 8; i++) {  
		//피봇의 인덱스. 한개남으면 비교할게 없어서 종료.
		for (int j = i + 1; j < 9; j++) { 
			//비교대상 인덱스 . 비벗기준으로 그거부터 끝까지
			if (Arr[i] > Arr[j]) swap(&Arr[i], &Arr[j]);   
			//피벗보다 클때는 값을 스왑해줘야함 . 
			//앞인 i가 뒤인 j보다  크면 배열의 값(&)을 스왑해줘야 한다. 오름차순이니까 ! 
			//이때 &로 레퍼런스값으로 넘겨야함
		}
	}
}//버블소팅해주는함수. 메디안메쏘드에서 소팅함수를 호출할거임
BYTE Median(BYTE * arr) {
	Sorting(arr);
	return arr[4];    //중간 값이 4번째 인덱스여서, 소팅 함수 호출한후 ,4번째 값만 리턴해주면 된다.
}//중간값 반환 함수
void Binarization(BYTE * Input, BYTE * Output, int Th, int W, int H)
{
	int Size = W * H;
	for (int i = 0; i < Size; i++)
	{
		if (Input[i] > Th) Output[i] = 255;
		else Output[i] = 0;
	}
}
int push(short *stackx, short *stacky, int arr_size, short vx, short vy, int *top)
{
	if (*top >= arr_size) return(-1);
	(*top)++;
	stackx[*top] = vx;
	stacky[*top] = vy;
	return(1);
}
int pop(short *stackx, short *stacky, short *vx, short *vy, int *top)
{
	if (*top == 0) return(-1);
	*vx = stackx[*top];
	*vy = stacky[*top];
	(*top)--;
	return(1);
}

// GlassFire 알고리즘을 이용한 라벨링 함수
void m_BlobColoring(BYTE* CutImage, int height, int width)
{
	int i, j, m, n, top, area, Out_Area, index, BlobArea[1000];
	long k;
	short curColor = 0, r, c;
	//	BYTE** CutImage2;
	Out_Area = 1;


	// 스택으로 사용할 메모리 할당
	short* stackx = new short[height*width];
	short* stacky = new short[height*width];
	short* coloring = new short[height*width];

	int arr_size = height * width;

	// 라벨링된 픽셀을 저장하기 위해 메모리 할당

	for (k = 0; k<height*width; k++) coloring[k] = 0;  // 메모리 초기화

	for (i = 0; i<height; i++)
	{
		index = i * width;
		for (j = 0; j<width; j++)
		{
			// 이미 방문한 점이거나 픽셀값이 255가 아니라면 처리 안함
			if (coloring[index + j] != 0 || CutImage[index + j] != 255) continue;
			r = i; c = j; top = 0; area = 1;
			curColor++;

			while (1)
			{
			GRASSFIRE:
				for (m = r - 1; m <= r + 1; m++)
				{
					index = m * width;
					for (n = c - 1; n <= c + 1; n++)
					{
						//관심 픽셀이 영상경계를 벗어나면 처리 안함
						if (m<0 || m >= height || n<0 || n >= width) continue;

						if ((int)CutImage[index + n] == 255 && coloring[index + n] == 0)
						{
							coloring[index + n] = curColor; // 현재 라벨로 마크
							if (push(stackx, stacky, arr_size, (short)m, (short)n, &top) == -1) continue;
							r = m; c = n; area++;
							goto GRASSFIRE;
						}
					}
				}
				if (pop(stackx, stacky, &r, &c, &top) == -1) break;
			}
			if (curColor<1000) BlobArea[curColor] = area;
		}
	}

	float grayGap = 255.0f / (float)curColor;

	// 덩어리의 화소값들이 저장되어있는데, 그중 가장 면적이 넓은 영역을 찾아내기 위함  !!!!!!!!!!!!
	for(i=1; i<=curColor; i++)
	{
		if(BlobArea[i]>=BlobArea[Out_Area]) Out_Area = i;
	}
 	// CutImage 배열 클리어~
	for (k = 0; k < width*height; k++) CutImage[k] = 255;

	// coloring에 저장된 라벨링 결과중 (Out_Area에 저장된) 영역이 가장 큰 것만 CutImage에 저장
	for (k = 0; k < width*height; k++)
	{
		if(coloring[k] == Out_Area) CutImage[k] = 0;  // 가장 큰 것만 저장
		//CutImage[k] = (unsigned char)(coloring[k] * grayGap);     //라벨링된 전체를 출력하는게 아니라 젤 큰것만 출력하게끔 주석해줌
	}

	delete[] coloring;
	delete[] stackx;
	delete[] stacky;
}
// 라벨링 후 가장 넓은 영역에 대해서만 뽑아내는 코드 포함



int main() {
	BITMAPFILEHEADER hf;       
	BITMAPINFOHEADER hInfo;     
	RGBQUAD	hRGB[256];			
	FILE *fp;
//	fp = fopen("lenna_noise.bmp", "rb");          
	fp = fopen("coin.bmp", "rb");          
	if (fp == NULL) return 0;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp);      
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp);	   
	fread(hRGB, sizeof(RGBQUAD), 256, fp);				
	int ImgSize = hInfo.biWidth * hInfo.biHeight;		
	BYTE * Image = (BYTE *)malloc(ImgSize);
	BYTE * Output = (BYTE *)malloc(ImgSize);
	fread(Image, sizeof(BYTE), ImgSize, fp);       
	fclose(fp);                
	
	//처리
	int W = hInfo.biWidth, H = hInfo.biHeight;
	
	Binarization(Image, Output, 100, W, H);
	
	m_BlobColoring(Output, H, W);    //m 어쩌고 함수는 가로세로가 거꾸로 들어가게 만들어진 함수임 .이건 그래스 파이어 라벨링 함수임 . 이걸하면 전경과 후경이 분리가 되고, 출력하는건 전경중에 제일 큰거임


	//----------> 이진 영상의 경계검출 함수 . 이거하면 아까 주석처리해줬으므로 동전들중에 가장 큰놈만 출력해준다. 이거 th 값은 100으로 설정해줬음
	for (int i = 0; i < H - 1; i++) {   // 아웃풋에는 이진 연산이 들어간다. 이거할때 출력에input으로 바꿔준다
		for (int j = 1; j < W; j++) {
			if (Output[i*W + j] == 255) {    // 이진화된게 255 면 전경화소라는 의미임 -> 그때만 이프문 검사  . 
				if (!(Output[(i - 1)*W + j] == 255 &&
					Output[(i + 1)*W + j] == 255 &&
					Output[i*W + (j + 1)] == 255 &&        
					Output[i*W + (j - 1)] == 255)) {  //이거 다 아니면 경계가 아닌거임. 다 255라는 조건은 경계가 아닌 조건임. 그래서 낫!을 써서 바꿔줘야함
					Image[i*W + j] = 255;           //이코드는  m함수 호출 후에 일어난다. 저기서 리턴값이 젤 넓은 원이므로, 그 작업을 안해주면 모든원의 경계가 하얘짐
					//이거 동전영상의 경계부분만 255로 하얗게 해준다는거임 . 현재 아웃풋에는 이진영상이 들어갔는데, 이미지에 오버랩시킬거여서 출력을 Image로 출력해야함 ㅇㅇㅇ
				}   // 실제 동전의 경계가 안나올수도있음.동전 녹슨부분 . 경계인줄알아서 같이 하얗게 처리한거임. 이진화만 깔끔하게되면 컨볼루션 마스크 쓰는거보다 이렇게 이진영상을 이용하는게 더 깔끔하긴함.
			}
		}
	}  //경계검출을  4neiborhood로 한거임.    


 /*   //->>>>>>중간값 필터링으로 레나 노이즈영상의 노이즈를 없애는 함수
	BYTE temp[9];  //화소값이 저장될 거니까 바이트 타입으로 
	int Margin = SIZE / 2;
	for(int i = 0; i < H - Margin; i++) {
	for (int j = Margin; j < W - Margin ; j++) {    //9개의 영역에 원래영상의 화소값을 저장한다.
		    temp[0] = Image[(i-1)*W + j-1];   
			temp[1] = Image[(i - 1)*W + j];
			temp[2] = Image[(i - 1)*W + j+1];  
			temp[3] = Image[i*W + j-1];
			temp[4] = Image[i*W + j];   //센터
			temp[5] = Image[i*W + j+1];
			temp[6] = Image[(i+1)*W + j-1];
			temp[7] = Image[(i+1)*W + j];
			temp[8] = Image[(i+1)*W + j+1];
			Output[i*W+j] = Median(temp); //temp 는 정렬 후 미디엄 값을 반환해주는 함수
		}
	}
	//이결과 수채화같은 그림이 나온다. 노이즈가 없어지긴했지만 쫌 남아있는 경우는 정렬을 해도 미디엄
	//값이였던게 노이즈였음. 9개중에 4개 이상이 노이즈였어서 정리해도 노이즈가 미디엄으로 선택되는거임
	//노이즈가 많이껴있다는건 원래영상의 화소정보가 많이 손실되어잇다는 말임
*/



	//출력부분
	fp = fopen("1ㅂ경계검출영상.bmp", "wb");               
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp);		
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp);
	fwrite(&hRGB, sizeof(RGBQUAD), 256, fp);		
//	fwrite(Image, sizeof(BYTE), ImgSize, fp);
	fwrite(Image, sizeof(BYTE), ImgSize, fp);    //레나 노이즈 뭉갤때 이거이용
	fclose(fp);					
	free(Image);				
	free(Output);
	return 0;
}



//과제
//이진화해서 동공을 구했는데, 그 동그라미의 무게중심을 구해서 까만색 으로 나온 애의 영역에 있는 화소중 x는 x 좌표끼리 
//다 더하고, y는 y 좌표끼리 다더해서 그걸 개수로 나누면 무게중심임
//무게중심 정수로 강제 형변환 시켜서 나오게 
//눈 원래 영상에 하얀색 크로스 표시를 해
    //동전영상로 할때는 이렇게 이진영상을 인버트 시킨다음에 라벨링해야함
    //for (int i = 0; i < ImgSize; i++) Output[i] = 255 - Output[i];   //배경보다 전경이 어두울 때 사용함

