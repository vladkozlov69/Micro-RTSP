
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

void OV2640Streamer::setURIStream(const char * uriStream)
{
    int resolution = atoi(uriStream);
    m_URIStream = uriStream;
    if (resolution < 0) resolution = 0;
    if (resolution > 13) resolution = 13;
    m_cam.updateFrameSize((framesize_t) resolution);
    
    m_height = m_cam.getHeight();
    m_width = m_cam.getWidth();
}
