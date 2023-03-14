/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <sstream>

template <typename T>
class DLLoader {
    class Error : public std::exception {
        public:
            Error(std::string val) noexcept : msg(val) {};
            const char *what() const noexcept override {return msg.c_str();}
        private:
            std::string msg;
    };
    public:
        DLLoader(std::string name){
            const char *val = name.c_str();
            lib = (void **) dlopen(val, RTLD_LAZY);
            char *error = dlerror();
            if (error != NULL) {
                throw Error(error);
            }
            T *(*func)(void);
            func = (T * (*) ()) dlsym(lib, "create");
            error = dlerror();
            if (error != NULL) {
                throw Error(error);
            }
            instance = func();
        };
        ~DLLoader(){
            void (*func)(IDisplayModule  *);
            func = (void (*) (T *)) dlsym(lib, "destroy");
            char *error = dlerror();
            func(instance);
            dlclose(lib);
            error = dlerror();
        };
        T *getInstance(void) {
            return instance;
        };
        std::string getInstanceType() const {
            T *(*func)(void);
            func = (T * (*) ()) dlsym(lib, "getType");
            char *error = dlerror();
            if (error != NULL) {
                throw Error(error);
            }
            return func();
        };
    protected:
    private:
        std::string instanceType;
        void **lib;
        T *instance;
};

#endif /* !DLLOADER_HPP_ */
