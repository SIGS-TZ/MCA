#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "LVC/config/parser.h"
#include "LVC/preprocess/debug.h"

using namespace std;

int main()
{
    auto cfg = fromRaytrixCfgFilePath(R"(D:\Code\SIGS\230818_VVC\dataset\videos\NagoyaFujita\param.cfg)");
    auto src = cv::imread("src_square.png");
    cv::Mat dst;
    lvc::dbgDrawMicroImageEdges(cfg, src, dst);
    cv::imwrite("dbg_circles_square.png", dst);
    return 0;
}
