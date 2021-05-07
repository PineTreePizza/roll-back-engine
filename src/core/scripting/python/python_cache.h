#ifndef PYTHON_CACHE_H
#define PYTHON_CACHE_H

#include <map>

#include "pyhelper.hpp"

struct CachedPythonModule {
    CPyObject module;
    std::map<std::string, CPyObject> classes;
};

class PythonCache {
  private:
    std::map<std::string, CachedPythonModule> cache;
    std::map<Entity, CPyObject> activeClassInstances;
  public:
    CPyObject GetClass(const std::string &classPath, const std::string &className) {
        if (cache.count(classPath) <= 0) {
            CPyObject pName = PyUnicode_FromString(classPath.c_str());
            CPyObject pModule = PyImport_Import(pName);
            assert(pModule != nullptr && "Python module is NULL!");
            std::map<std::string, CPyObject> pClasses;
            cache.emplace(classPath, CachedPythonModule{
                .module = pModule,
                .classes = pClasses
            });
        }
        cache[classPath].module.AddRef();
        if (cache[classPath].classes.count(className) <= 0) {
            CPyObject pModuleDict = PyModule_GetDict(cache[classPath].module);
            CPyObject pClass = PyDict_GetItemString(pModuleDict, className.c_str());
            assert(pClass != nullptr && "Python class is NULL!");
            cache[classPath].classes.emplace(className, pClass);
        }
        cache[classPath].classes[className].AddRef();
        return cache[classPath].classes[className];
    }

    CPyObject CreateClassInstance(const std::string &classPath, const std::string &className, Entity entity) {
        assert(HasActiveInstance(entity) && "Entity not active!");
        CPyObject argList = Py_BuildValue("(i)", entity);
        CPyObject pClassInstance = PyObject_CallObject(GetClass(classPath, className), argList);
        assert(pClassInstance != nullptr && "Python class instance is NULL on creation!");
        activeClassInstances.emplace(entity, pClassInstance);
        activeClassInstances[entity].AddRef();
        return activeClassInstances[entity];
    }

    CPyObject GetClassInstance(Entity entity) {
        assert(HasActiveInstance(entity) && "Entity not active!");
        return activeClassInstances[entity];
    }

    bool HasActiveInstance(Entity entity) {
        return activeClassInstances.count(entity) > 0;
    }

    void RemoveClassInstance(Entity entity) {
        activeClassInstances[entity].Release();
        activeClassInstances.erase(entity);
    }
};

#endif //PYTHON_CACHE_H
