#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*— ensure no struct padding —*/
#pragma pack(push, 1)
typedef struct
{
    uint16_t bfType;      // must be 'BM' = 0x4D42
    uint32_t bfSize;      // file size in bytes
    uint16_t bfReserved1; // =0
    uint16_t bfReserved2; // =0
    uint32_t bfOffBits;   // offset to pixel data
} BITMAPFILEHEADER;

typedef struct
{
    uint32_t biSize;         // size of this header (40)
    int32_t biWidth;         // image width
    int32_t biHeight;        // image height (positive = bottom-up)
    uint16_t biPlanes;       // must be 1
    uint16_t biBitCount;     // bits per pixel (we expect 24)
    uint32_t biCompression;  // 0 = BI_RGB (no compression)
    uint32_t biSizeImage;    // image data size (including padding)
    int32_t biXPelsPerMeter; // resolution
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed; // palette entries (0 for true color)
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

/**
 * load_bmp:
 *   filename: path to .bmp
 *   outWidth, outHeight: filled with dims
 *   returns: pointer to malloc'ed buffer [width*height*3] in RGB order,
 *            or NULL on error. Free with free().
 */
unsigned char *load_bmp(const char *filename, int *outWidth, int *outHeight)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("fopen");
        return NULL;
    }

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    if (fread(&bfh, sizeof bfh, 1, f) != 1 ||
        fread(&bih, sizeof bih, 1, f) != 1)
    {
        fprintf(stderr, "Failed to read BMP headers\n");
        fclose(f);
        return NULL;
    }

    if (bfh.bfType != 0x4D42 || bih.biBitCount != 24 || bih.biCompression != 0)
    {
        fprintf(stderr, "Unsupported BMP format (only uncompressed 24bpp)\n");
        fclose(f);
        return NULL;
    }

    int w = bih.biWidth;
    int h = abs(bih.biHeight);
    int row_bytes = ((w * 3 + 3) / 4) * 4; // padded to 4 bytes
    unsigned char *data = malloc(w * h * 3);
    if (!data)
    {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    fseek(f, bfh.bfOffBits, SEEK_SET);
    for (int y = 0; y < h; y++)
    {
        // BMP stores bottom row first if biHeight>0
        int row = (bih.biHeight > 0) ? (h - 1 - y) : y;
        unsigned char *ptr = data + (row * w * 3);
        unsigned char *scan = malloc(row_bytes);
        if (!scan)
        {
            perror("malloc");
            free(data);
            fclose(f);
            return NULL;
        }
        if (fread(scan, 1, row_bytes, f) != (size_t)row_bytes)
        {
            fprintf(stderr, "Failed to read BMP scanline\n");
            free(scan);
            free(data);
            fclose(f);
            return NULL;
        }
        // BGR -> RGB
        for (int x = 0; x < w; x++)
        {
            ptr[3 * x + 0] = scan[3 * x + 2];
            ptr[3 * x + 1] = scan[3 * x + 1];
            ptr[3 * x + 2] = scan[3 * x + 0];
        }
        free(scan);
    }

    fclose(f);
    *outWidth = w;
    *outHeight = h;
    return data;
}

/**
 * write_bmp:
 *   filename: output path
 *   data:     RGB buffer [w*h*3]
 *   w, h:     dims
 * returns 0 on success, -1 on error
 */
int write_bmp(const char *filename,
              const unsigned char *data,
              int w, int h)
{
    int row_bytes = ((w * 3 + 3) / 4) * 4;
    uint32_t imageSize = row_bytes * h;
    BITMAPFILEHEADER bfh = {
        .bfType = 0x4D42,
        .bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + imageSize,
        .bfReserved1 = 0,
        .bfReserved2 = 0,
        .bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)};
    BITMAPINFOHEADER bih = {
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = w,
        .biHeight = h, // positive = bottom-up
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = imageSize,
        .biXPelsPerMeter = 2835, // 72 DPI
        .biYPelsPerMeter = 2835,
        .biClrUsed = 0,
        .biClrImportant = 0};

    FILE *f = fopen(filename, "wb");
    if (!f)
    {
        perror("fopen");
        return -1;
    }

    if (fwrite(&bfh, sizeof bfh, 1, f) != 1 ||
        fwrite(&bih, sizeof bih, 1, f) != 1)
    {
        fprintf(stderr, "Failed to write BMP headers\n");
        fclose(f);
        return -1;
    }

    unsigned char *scan = malloc(row_bytes);
    if (!scan)
    {
        perror("malloc");
        fclose(f);
        return -1;
    }

    for (int y = 0; y < h; y++)
    {
        int row = h - 1 - y; // write bottom row first
        const unsigned char *ptr = data + (row * w * 3);
        // RGB -> BGR + padding
        for (int x = 0; x < w; x++)
        {
            scan[3 * x + 0] = ptr[3 * x + 2];
            scan[3 * x + 1] = ptr[3 * x + 1];
            scan[3 * x + 2] = ptr[3 * x + 0];
        }
        // zero pad remaining bytes
        for (int p = 3 * w; p < row_bytes; p++)
            scan[p] = 0;
        fwrite(scan, 1, row_bytes, f);
    }

    free(scan);
    fclose(f);
    return 0;
}

int main(int argc, char *argv[])
{

    int w, h;
    unsigned char *img = load_bmp("bmp_24.bmp", &w, &h);
    if (!img)
        return 1;

    /*
        Your Image Processing Goes Here 
    */

    if (write_bmp("bmp_24_copy.bmp", img, w, h) != 0)
    {
        free(img);
        return 1;
    }
    free(img);
    return 0;
}
