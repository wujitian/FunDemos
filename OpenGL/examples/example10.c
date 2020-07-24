/*
 * This example comes from 《OpenGL编程精粹》8.4 
 * Created Time: 2020-07-15 16:24:53
 * Last modified: 
 * @author: fabiokong@zhaoxin.com 
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void init();
void display();

/*------------- 
 类型定义
 --------------*/
// 纹理图像结构
typedef struct 
{
    int imgWidth; // 纹理宽度
    int imgHeight; // 纹理高度
    unsigned int rgbType; // 每个象素对应的字节数，3：24位图，4：带alpha通道的24位图
    unsigned char *data; // 纹理数据
} TEXTUREIMAGE;
 
// BMP文件头
typedef struct {
    unsigned short bfType; // 文件类型
    unsigned int bfSize; // 文件大小
    unsigned short bfReserved1; // 保留位
    unsigned short bfReserved2; // 保留位
    unsigned int bfOffBits; // 数据偏移位置
} __attribute__((packed)) BMPFILEHEADER;
 
// BMP信息头
typedef struct {
    unsigned int biSize; // 此结构大小
    int biWidth; // 图像宽度
    int biHeight; // 图像高度
    unsigned short biPlanes; // 调色板数量
    unsigned short biBitCount; // 每个象素对应的位数，24：24位图，32：带alpha通道的24位图
    unsigned int biCompression; // 压缩
    unsigned int biSizeImage; // 图像大小
    int biXPelsPerMeter; // 横向分辨率
    int biYPelsPerMeter; // 纵向分辨率
    unsigned int biClrUsed; // 颜色使用数
    unsigned int biClrImportant; // 重要颜色数
} __attribute__((packed)) BMPINFOHEADER;
 
// 读取BMP文件创建纹理
int LoadBmp(char *filename, TEXTUREIMAGE *textureImg) {
    int i, j;
    FILE *file;
    BMPFILEHEADER bmpFile;
    BMPINFOHEADER bmpInfo;
    int pixel_size;
	
    // 初始化纹理数据
    textureImg->imgWidth = 0;
    textureImg->imgHeight = 0;
    textureImg->rgbType = 0;
    //if (textureImg->data != NULL) {
    //    //delete []textureImg->data;
	//	free(textureImg->data);
    //}
 
    // 打开文件
    file = fopen(filename, "rb");
    if (file == NULL) {
		printf("Open File Error\n");
        return 0;
    }

    // 获取文件头
    rewind(file);
    fread(&bmpFile, sizeof(BMPFILEHEADER), 1, file);
    // 验证文件类型
    if (bmpFile.bfType != 0x4D42) {
		printf("File Type Error\n");
       	fclose(file);
        return 0;
    }
	
    //因为Ｃ语言对结构按四位对齐，所以不能直接用sizeof(BMPFILEHEADER)
    fread(&bmpInfo, sizeof(BMPINFOHEADER), 1, file);
	
    // 获取图像色彩数
    pixel_size = bmpInfo.biBitCount >> 3;
    // 读取文件数据
    //textureImg->data = new unsigned char[bmpInfo.biWidth * bmpInfo.biHeight * pixel_size];
    textureImg->data = (unsigned char *)malloc(bmpInfo.biWidth * bmpInfo.biHeight * pixel_size * sizeof(unsigned char));
    if (textureImg->data == NULL) {
        fclose(file);
        return 0;
    }

    rewind(file);
    fseek(file, 54L, 0);
    for (i = 0; i < bmpInfo.biHeight; i++) {
        for (j = 0; j < bmpInfo.biWidth; j++) {
            // 红色分量
            fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 2,
                      sizeof(unsigned char), 1, file);
            // 绿色分量
            fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 1,
                      sizeof(unsigned char), 1, file);
            // 蓝色分量
            fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 0,
                    sizeof(unsigned char), 1, file);
            // Alpha分量
            if (pixel_size == 4) {
                     fread(textureImg->data + (i * bmpInfo.biWidth + j) * pixel_size + 3,
                     sizeof(unsigned char), 1, file);
            }
        }
    }
    // 记录图像相关参数
    textureImg->imgWidth = bmpInfo.biWidth;
    textureImg->imgHeight = bmpInfo.biHeight;
    textureImg->rgbType = pixel_size;
    fclose(file);
    return 1;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("OpenGL 3D View");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.5);
    glClearDepth(1.0f);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        
    char strFileName[50] = "../example10_feature.bmp";
	TEXTUREIMAGE tImage;

    if (!LoadBmp(strFileName, &tImage))
	{
		printf("LoadBmp failed!\n");
	}

	printf("imgWidth = %d, imgHeight = %d, rgbType = %d\n", tImage.imgWidth, tImage.imgHeight, tImage.rgbType);

	int textureID;
	glGenTextures(1, &textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
    int textureType = GL_RGB;
    if (tImage.rgbType == 4)
        textureType = GL_RGBA;

    gluBuild2DMipmaps(GL_TEXTURE_2D, tImage.rgbType, tImage.imgWidth, tImage.imgHeight, textureType, GL_UNSIGNED_BYTE, tImage.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTranslatef(-2.0f, 0, -8.0f);
    glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
        // front
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        
        // back
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        
        // top
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
        
        // bottom
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        
        // right
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
        
        // left
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    if (tImage.data)
    {
        free(tImage.data);
    }

    glFlush();
}



