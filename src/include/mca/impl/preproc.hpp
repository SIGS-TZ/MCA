﻿#pragma once

#include <numbers>
#include <ranges>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <tlct/config.hpp>
#include <tlct/helper/static_math.hpp>

#include "mca/common/defines.h"
#include "mca/helper.hpp"

namespace mca {

namespace rgs = std::ranges;
namespace tcfg = tlct::cfg;

template <typename TLayout>
    requires tcfg::concepts::CLayout<TLayout>
inline void preprocess_(const TLayout& layout, const cv::Mat& src, cv::Mat& dst, const double crop_ratio)
{
    double block_width = layout.getDiameter() * crop_ratio;
    int block_width_i = static_cast<int>(ceil(block_width));

    int req_cols = tlct::_hp::align_to_2(layout.getMIMaxCols() * block_width_i);
    int req_rows = tlct::_hp::align_to_2(layout.getMIRows() * block_width_i);

    cv::Mat canvas(req_rows, req_cols, src.type());
    cv::Mat src_roi_image, dst_roi_image;

    for (const int row : rgs::views::iota(0, layout.getMIRows())) {
        for (const int col : rgs::views::iota(0, layout.getMICols(row))) {
            const cv::Point2d micenter = layout.getMICenter(row, col);
            src_roi_image = _hp::getRoiImageByCenter(src, micenter, block_width);
            dst_roi_image = _hp::getRoiImageByLeftupCorner(canvas, cv::Point(col, row) * block_width_i, block_width);
            src_roi_image.copyTo(dst_roi_image);
        }
    }

    if (layout.getRotation() != 0.0) {
        cv::transpose(canvas, dst);
    } else {
        dst = std::move(canvas);
    }
}

template void preprocess_(const tcfg::tspc::Layout& layout, const cv::Mat& src, cv::Mat& dst, const double crop_ratio);
template void preprocess_(const tcfg::raytrix::Layout& layout, const cv::Mat& src, cv::Mat& dst,
                          const double crop_ratio);

template <typename TLayout>
    requires tcfg::concepts::CLayout<TLayout>
inline cv::Mat preprocess(const TLayout& layout, const cv::Mat& src, const double crop_ratio)
{
    cv::Mat dst;
    preprocess_(layout, src, dst, crop_ratio);
    return dst;
}

template cv::Mat preprocess(const tcfg::tspc::Layout& layout, const cv::Mat& src, const double crop_ratio);
template cv::Mat preprocess(const tcfg::raytrix::Layout& layout, const cv::Mat& src, const double crop_ratio);

} // namespace mca