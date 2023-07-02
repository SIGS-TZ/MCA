#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "LVC/common/config.hpp"
#include "LVC/common/defines.h"
#include "LVC/common/helper.hpp"

#include "LVC/preprocess/debug.hpp"

namespace lvc {

static LVC_FORCE_INLINE void dbgDrawCircle(cv::Mat& dst, cv::Point2d center, double diameter)
{
    cv::circle(dst, static_cast<cv::Point2i>(center), static_cast<int>(diameter / 2.0), cv::Scalar(0, 255, 0), 1,
               cv::LineTypes::LINE_AA);
}

static LVC_FORCE_INLINE void dbgDrawSoildCircle(cv::Mat& dst, cv::Point2d center, double diameter)
{
    cv::circle(dst, static_cast<cv::Point2i>(center), static_cast<int>(diameter / 2.0), cv::Scalar::all(255.0),
               cv::LineTypes::FILLED, cv::LineTypes::LINE_AA);
}

void dbgDrawMicroImageEdges(const Config& cfg, const cv::Mat& src, cv::Mat& dst)
{
    dst = src.clone();

    MicroImageRanges mis = MicroImageRanges::fromConfig(cfg);

    for (const auto& mi : mis) {
        dbgDrawCircle(dst, mi.getCenter(), cfg.getDiameter());
    }
}

void dbgDrawUsedArea(const Config& cfg, const cv::Mat& patch_size_map, int view_num, cv::Mat& dst)
{
    dst = cv::Mat::zeros(cfg.getHeight(), cfg.getWidth(), CV_8UC1);

    MicroImageRanges mis = MicroImageRanges::fromConfig(cfg);

    for (const auto& mi : mis) {
        auto idx = mi.getIndex();
        double patch_size = static_cast<double>(patch_size_map.at<uchar>(idx.y, idx.x) + view_num);
        if (patch_size > cfg.getDiameter()) {
            patch_size = cfg.getDiameter();
        }
        dbgDrawSoildCircle(dst, mi.getCenter(), patch_size);
    }
}

} // namespace lvc
