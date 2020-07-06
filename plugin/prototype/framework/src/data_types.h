//
// Created by 潘绪洋 on 17-4-5.
// Copyright (c) 2017 Wuhan Collaborative Robot Technology Co.,Ltd. All rights reserved.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <chrono>

/**
 * @brief 几种图像的固定格式
 */
enum class ImageType {
    Color, ///< 彩色BGR图像
    Depth, ///< 深度图像， float, 单位mm
    Ir, ///< 红外图像（Kinect2???
    Mono ///< 单色图像, 灰度图
};

std::string toString(ImageType imageType);

/**
 * @brief 由相机驱动产生捕获的图像
 */
struct ImageFrame {
    ImageType type; ///< 图像数据帧的类型
    const cv::Mat& data; ///< 指向原始数据
};

/**
 * @brief 相机驱动一次捕获操作所获得的图像
 */
struct CameraFrame {
    std::chrono::high_resolution_clock::time_point capture_time; ///< 捕获时间
    std::vector<ImageFrame> frames;/// 捕获的图像
};

/**
* @brief 六维力数据
*/
struct Wrench {
    cv::Point3d force;
    cv::Point3d torque;
};


#endif
