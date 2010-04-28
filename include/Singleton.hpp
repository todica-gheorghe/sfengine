#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace eng
{
    template<typename T>
    class Singleton
    {
        public:

            static T*   Get()
            {
                if (!myInstance)
                    myInstance = new T();
                return myInstance;
            }

            static void Kill()
            {
                delete myInstance;
                myInstance = 0;
            }

        protected:
            Singleton() {}
            virtual ~Singleton() {}

        private:
            static T*   myInstance;
    };
}

#endif // SINGLETON_HPP
