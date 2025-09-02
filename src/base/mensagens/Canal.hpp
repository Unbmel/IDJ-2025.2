#ifndef H_BASE_MENSAGENS_CANAL
#define H_BASE_MENSAGENS_CANAL

namespace IDJ::MENSAGENS
{
    template <class T>
    class Canal
    {
        void* ref_obj;
        void (*rec)(void* ref_obj, T valor) = 0;
        public:
        void receber(T valor)
        {
            this->rec(this->ref_obj, valor);
        }
        Canal(
            void* ref_obj,
            void (*rec)(void*, T)
        ):ref_obj(ref_obj), rec(rec){};
    };
};

#endif