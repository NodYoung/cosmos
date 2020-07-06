#ifndef ABSTRACT_CAMERA_H
#define ABSTRACT_CAMERA_H

#include "botsys.h"
#include "abstract_object.h"
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "data_types.h"


class AbstractCamera;
/**
 * @addtogroup framework
 * @{
 */

/**
 * @defgroup camera
 * @brief 相机API接口
 * @{
 */

class CameraStreamObserver {
public:
    CameraStreamObserver();
    virtual ~CameraStreamObserver();
    virtual void onCameraStreamUpdate(const CameraFrame& cameraFrame, AbstractCamera* camera) = 0;
};


/**
 * @note 凡是有 attach() 方法的类，最好都实现 clearAttachedObject() 方法。
 *       对象在释放的时候，如果不主动的通过 clearAttachedObject() ，指针的智能释放会失败。
 *       因为互相引用。
 */
class AbstractCamera : public AbstractObject {
public:
    AbstractCamera();
    virtual ~AbstractCamera();

    virtual bool isOpened() const = 0; ///< 获取当前相机的状态
    virtual bool open(int deviceId = 0) = 0;
    virtual void close() = 0;
    virtual void attach(const std::shared_ptr<CameraStreamObserver>& observer) = 0;
    virtual bool capture(int waitMs = -1) = 0; /// @note 控制相机进行一次图像捕获

    virtual std::string getManufacturer() const = 0;
    virtual std::string getFullDescription() const = 0;
    virtual std::string getSerialNumber() const = 0;

    virtual int getImageWidth(int imageIdx = 0) const = 0;
    virtual int getImageHeight(int imageIdx = 0) const = 0;
    virtual ImageType getImageType(int imageIdx = 0) const = 0;
    virtual int getImageCount() const = 0;
};


#endif
