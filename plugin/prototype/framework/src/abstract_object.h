#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include <memory>
#include <QString>


/**
 * @brief 所有动态对象的根对象
 *
 * AbstractObject 是这个软件框架的最上层的类对象，只有一个 setup() 函数，而且还是虚函数。
 */
class AbstractObject : public std::enable_shared_from_this<AbstractObject> {
public:
    AbstractObject();
    virtual ~ AbstractObject();

    /**
     * 如果对象有初始化的配置文件，那么在通过创建配置文件的时候，文件的路径地址会通过setup参数传入。
     * 同时，正常情况下。如果配置文件不对，无法满足设置要求，直接返回false就好。
     *
     * 正常情况下，配置文件是JSON格式的。
     * @param configFilePath 当前对象所需要的配置文件的路径
     * @retval true 当前对像成功的加载了配置
     * @retval false 配置加载失败。原因看log
     *    一般可能的原因是配置文件不存在，或者是配置不正确，这个要看具体的实现
     *    的类是怎么搞的。
     */
    virtual bool setup(const QString& configFilePath) = 0;

    /**
     * 删除所以通过观察模式 attach() 函数添加的对象，如果有的话。
     */
    virtual void clearAttachedObject();
};

/**
 * @defgroup framework
 * @{
 */
typedef std::shared_ptr<AbstractObject> AbstractObjectPtr;

/**
 * @}
 */

template<class T>
void detachSharedObject(T& t) {
    if (t) {
        t->clearAttachedObject();
    }
}

#endif
