#include "VideoFrame.h"

VideoFrame::VideoFrame()
{
    mYuv420Buffer = nullptr;//存储 YUV 格式的视频数据的指针，亮度（Y）和色度（U、V）
}

VideoFrame::~VideoFrame()
{
    if (mYuv420Buffer != nullptr)
    {
        free(mYuv420Buffer);
        mYuv420Buffer = nullptr;
    }
}

void VideoFrame::initBuffer(const int &width, const int &height)
{
    if (mYuv420Buffer != nullptr)
    {
        free(mYuv420Buffer);
        mYuv420Buffer = nullptr;
    }

    mWidth  = width;
    mHegiht = height;

    mYuv420Buffer = (uint8_t*)malloc(width * height * 3 / 2);

}

void VideoFrame::setYUVbuf(const uint8_t *buf)
{
    int Ysize = mWidth * mHegiht;
    memcpy(mYuv420Buffer, buf, Ysize * 3 / 2);//memcpy 函数用于将 buf 中的数据复制到 mYuv420Buffer 指向的内存空间中，
    //复制的大小为 Ysize * 3 / 2 字节，因为 YUV 格式中 Y 分量占据一半大小，U 和 V 分量各占据 1/4 大小。
}

void VideoFrame::setYbuf(const uint8_t *buf)
{
    int Ysize = mWidth * mHegiht;
    memcpy(mYuv420Buffer, buf, Ysize);
}

void VideoFrame::setUbuf(const uint8_t *buf)
{
    int Ysize = mWidth * mHegiht;
    memcpy(mYuv420Buffer + Ysize, buf, Ysize / 4);
}

void VideoFrame::setVbuf(const uint8_t *buf)
{
    int Ysize = mWidth * mHegiht;
    memcpy(mYuv420Buffer + Ysize + Ysize / 4, buf, Ysize / 4);
}

