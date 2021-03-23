#ifndef _ATOMIC_VAR_H_
#define _ATOMIC_VAR_H_

template <class T> class AtomicVar
{
    public:
        AtomicVar()
        {

        }

        AtomicVar(AtomicVar &other)
        {
            copy(other);
        }

        AtomicVar(const AtomicVar &other)
        {
            copy(other);
        }

        AtomicVar& operator =(AtomicVar &other)
        {
            copy(other);
            return *this;
        }

        AtomicVar& operator =(const AtomicVar &other)
        {
            copy(other);
            return *this;
        }

        AtomicVar(T &new_value)
        {
            set(new_value);
        }

        AtomicVar(const T &new_value)
        {
            set(new_value);
        }



    public:
        T get()
        {
            T result;
            __disable_irq();
            result = this->value;
            __enable_irq();

            return result;
        }

        void set(const T& new_value)
        {
            __disable_irq();
            this->value = new_value;
            __enable_irq();
        }

        void set(T& new_value)
        {
            __disable_irq();
            this->value = new_value;
            __enable_irq();
        }

    private:
        void copy(T &other)
        {
            set(other);
        }

        void copy(const T &other)
        {
            set(other);
        }

    private:
        T value;
};

#endif
