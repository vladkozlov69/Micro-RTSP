
#include "OV2640Streamer.h"
#include <assert.h>



OV2640Streamer::OV2640Streamer(SOCKET aClient, OV2640 &cam) : CStreamer(aClient, cam.getWidth(), cam.getHeight()), m_cam(cam)
{
    DEBUG_PRINT("Created streamer width=%d, height=%d\n", cam.getWidth(), cam.getHeight());
}

void OV2640Streamer::streamImage(uint32_t curMsec)
{
    m_cam.run();// queue up a read for next time

    BufPtr bytes = m_cam.getfb();
    streamFrame(bytes, m_cam.getSize(), curMsec);
    m_cam.done();
}

/*
    FRAMESIZE_96X96,    // 96x96
    FRAMESIZE_QQVGA,    // 160x120
    FRAMESIZE_QCIF,     // 176x144
    FRAMESIZE_HQVGA,    // 240x176
    FRAMESIZE_240X240,  // 240x240
    FRAMESIZE_QVGA,     // 320x240
    FRAMESIZE_CIF,      // 400x296
    FRAMESIZE_HVGA,     // 480x320
    FRAMESIZE_VGA,      // 640x480
    FRAMESIZE_SVGA,     // 800x600
    FRAMESIZE_XGA,      // 1024x768
    FRAMESIZE_HD,       // 1280x720
    FRAMESIZE_SXGA,     // 1280x1024
    FRAMESIZE_UXGA,     // 1600x1200

*/
static u_short heights[] = {96,120,144,176,240,240,296,320,480,600,768,720,1024,1200};
static u_short widths[] = {96,160,176,240,240,320,400,480,640,800,1024,1280,1280,1600};

void OV2640Streamer::setURIStream(const char * uriStream)
{
    int resolution = atoi(uriStream);
    m_URIStream = uriStream;
    if (resolution < 4) resolution = 4;
    if (resolution > 13) resolution = 13;
    m_cam.updateFrameSize((framesize_t) resolution);
    
    m_height = heights[resolution];
    m_width = widths[resolution];
}
