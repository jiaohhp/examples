#include <iostream>
#include "jcrtspserver.h"
int main()
{
    JCRtspServer rtspServer(8554);
    rtspServer.Run();

    return 0;
}
