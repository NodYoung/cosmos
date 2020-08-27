/*
 * registerer.h
 *
 *      Registerer is a factory register mechanism that make class registration at
 *      compile time and allow generating an object by giving the name. Example:
 *
 *      class BaseClass {  // base class
 *      ...
 *      };
 *      REGISTER_REGISTERER(BaseClass);
 *      #define REGISTER_BASECLASS(name) REGISTER_CLASS(BaseClass, name)
 *
 *      class Sub1 : public BaseClass {
 *      ...
 *      };
 *      REGISTER_BASECLASS(Sub1);
 *
 *      class Sub2 : public BaseClass {
 *      ...
 *      };
 *      REGISTER_BASECLASS(Sub2);
 *
 *      Note that REGISTER_BASE(sub1) should be put in cc file instead of h file,
 *      to avoid multi-declaration error when compile.
 *
 *      Then you could get a new object of the sub class by:
 *      Base *obj = BaseClassRegisterer::get_instance_by_name("Sub1");
 *
 *      This is convenient when you need decide the class at runtime or by flag:
 *      string name = "Sub1";
 *      if (...)
 *          name = "Sub2";
 *      Base *obj = BaseClassRegisterer::get_instance_by_name(name);
 *
 *      If there should be only one instance in the program by desgin,
 *      get_uniq_instance could be used:
 *      Base *obj = BaseClassRegisterer::get_uniq_instance();
 *
 *      If multi sub classes are registered, this method will cause a CHECK fail.
 */

#include <string>
#include <map>
#include "perception_macros.h"


class Any {
public:
    Any() : _content(NULL) {}

    template<typename ValueType>
    Any(const ValueType &value)  // NOLINT
            : _content(new Holder<ValueType>(value)) {}

    Any(const Any &other)
        : _content(other._content ? other._content->clone() : NULL) {}

    ~Any() {
        delete _content;
    }

    template<typename ValueType>
    ValueType *any_cast() {
        return _content ?
            &static_cast<Holder<ValueType> *>(_content)->_held : NULL;  // NOLINT
    }

private:
    class PlaceHolder {
    public:
        virtual ~PlaceHolder() {}
        virtual PlaceHolder *clone() const = 0;
    };

    template<typename ValueType>
    class Holder : public PlaceHolder {
    public:
        explicit Holder(const ValueType &value) : _held(value) {}
        virtual ~Holder() {}
        virtual PlaceHolder *clone() const {
            return new Holder(_held);
        }

        ValueType _held;
    };

    PlaceHolder *_content;
};

class ObjectFactory {
public:
    ObjectFactory() {}
    virtual ~ObjectFactory() {}
    virtual Any new_instance() {
        return Any();
    }
private:
    DISALLOW_COPY_AND_ASSIGN(ObjectFactory)
};

typedef std::map<std::string, ObjectFactory*> FactoryMap;
typedef std::map<std::string, FactoryMap> BaseClassMap;
BaseClassMap& global_factory_map();

bool get_registered_classes(
        const std::string& base_class_name,
        std::vector<std::string>* registered_derived_classes_names);

#define REGISTER_REGISTERER(base_class) \
class base_class ## Registerer { \
public: \
    static base_class *get_instance_by_name(const ::std::string &name) { \
        FactoryMap &map = global_factory_map()[#base_class]; \
        FactoryMap::iterator iter = map.find(name); \
        if (iter == map.end()) { \
            for (auto c : map) { \
                LOG(ERROR) << "Instance:" << c.first; \
            } \
            LOG(ERROR) << "Get instance " << name << " failed."; \
            return NULL; \
        } \
        Any object = iter->second->new_instance(); \
        return *(object.any_cast<base_class*>()); \
    } \
    static std::vector<base_class*> get_all_instances() { \
        std::vector<base_class*> instances; \
        FactoryMap &map = global_factory_map()[#base_class]; \
        instances.reserve(map.size()); \
        for (auto item : map) { \
            Any object = item.second->new_instance(); \
            instances.push_back(*(object.any_cast<base_class*>())); \
        } \
        return instances; \
    } \
    static const ::std::string get_uniq_instance_name() { \
        FactoryMap &map = global_factory_map()[#base_class]; \
        CHECK_EQ(map.size(), 1) << map.size(); \
        return map.begin()->first; \
    } \
    static base_class *get_uniq_instance() { \
        FactoryMap &map = global_factory_map()[#base_class]; \
        CHECK_EQ(map.size(), 1) << map.size(); \
        Any object = map.begin()->second->new_instance(); \
        return *(object.any_cast<base_class*>()); \
    } \
    static bool is_valid(const ::std::string &name) { \
        FactoryMap &map = global_factory_map()[#base_class]; \
        return map.find(name) != map.end(); \
    } \
};

#define REGISTER_CLASS(clazz, name) \
class ObjectFactory##name : public ObjectFactory { \
public: \
    virtual ~ObjectFactory##name() {} \
    virtual Any new_instance() { \
        return Any(new name()); \
    } \
}; \
__attribute__((constructor)) void register_factory_##name() { \
    LOG(INFO) << "register_"<<#name<<"_factory is called."; \
    FactoryMap &map = \
    global_factory_map()[#clazz]; \
    if (map.find(#name) == map.end()) \
        map[#name] = new ObjectFactory##name(); \
} \


