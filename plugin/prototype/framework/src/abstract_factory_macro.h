

#ifndef ABSTRACT_FACTORY_MACRO_H
#define ABSTRACT_FACTORY_MACRO_H

//#include "extra2.h"

#define FACTORY_EXPORT(_ObjectToExport)                                 \
{ m_creator[( #_ObjectToExport )] = [](){ return std::make_shared<_ObjectToExport>(); }; }

#define FACTORY_BEGIN(_FactoryName)                                     \
class _FactoryName : public AbstractObjectFactory {                     \
public:                                                                 \
std::map<std::string, std::function<AbstractObjectPtr()> > m_creator;   \
                                                                        \
virtual std::vector<std::string> getSupportTypes(){                     \
    std::vector<std::string> r;                                         \
    for (const auto& iter : m_creator) {                                \
        r.push_back(iter.first);                                        \
    }                                                                   \
    return r;                                                           \
}                                                                       \
                                                                        \
_FactoryName(){                                                         \



#define FACTORY_END(_FactoryName, _Ver)                                 \
}                                                                       \
                                                                        \
virtual ~_FactoryName(){                                                \
    LOG(INFO) << "Destructor " << typeid(this).name();                  \
}                                                                       \
virtual std::string getFactoryType() {                                  \
    return #_FactoryName ", Ver " _Ver;                                 \
}                                                                       \
                                                                        \
virtual std::shared_ptr <AbstractObject> createObject(const std::string& type) {\
    auto iter = m_creator.find(type);                                   \
    if (iter != m_creator.end()) {                                      \
        if (iter->second) {                                             \
            return iter->second();                                      \
        }                                                               \
    }                                                                   \
    return std::shared_ptr<AbstractObject>();                           \
}                                                                       \
};                                                                      \
                                                                        \
static std::shared_ptr<_FactoryName> localFactory;                      \
                                                                        \
extern "C" void* getAbstractObjectFactoryInstance() {                   \
    if (localFactory == nullptr) {                                      \
        localFactory = std::make_shared<_FactoryName>();                \
    }                                                                   \
    return localFactory.get();                                          \
};

#endif
